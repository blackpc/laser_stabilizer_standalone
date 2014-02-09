/*
 * MaestroController.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: lamplight
 */

#include "MaestroController.h"

MaestroController::MaestroController(string device) {
	initDevice(device);
}

MaestroController::~MaestroController() {
	close(deviceFileDescriptor);
}

void MaestroController::setParameters(int channel, int center, double degreeStep) {
	ChannelSettings settings;
	settings.center = center;
	settings.degreeStep = degreeStep;

	_settings[channel] = settings;
}

void MaestroController::setAngle(int channel, double angle) {
	ChannelSettings settings = _settings[channel];
	setTarget(channel, settings.center + settings.degreeStep * angle);
}

float MaestroController::getAngle(int channel) {
	unsigned char command[] = { 0x90, channel };
	if (write(deviceFileDescriptor, command, sizeof(command)) == -1) {
		perror("error writing");
		return -1;
	}

	unsigned char response[2];
	if (read(deviceFileDescriptor, response, 2) != 2) {
		perror("error reading");
		return -1;
	}

	float pulseValue = (response[0] + 256 * response[1]) / 4.0;
	float angle = (pulseValue - _settings[channel].center) / _settings[channel].degreeStep;

	return angle;
}

void MaestroController::initDevice(string device) {

	deviceFileDescriptor = open(device.c_str(), O_RDWR | O_NOCTTY);
	if (deviceFileDescriptor == -1)
	{
		perror(device.c_str());
	}

	#ifndef _WIN32
		struct termios options;
		tcgetattr(deviceFileDescriptor, &options);
		options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
		options.c_oflag &= ~(ONLCR | OCRNL);
		tcsetattr(deviceFileDescriptor, TCSANOW, &options);
	#endif

}

void MaestroController::setTarget(int channel, int target) {
	target = target * 4;
	unsigned char command[] = {0x84, channel, target & 0x7F, target >> 7 & 0x7F};
	if (write(deviceFileDescriptor, command, sizeof(command)) == -1)
	{
		perror("error writing");
	}
}
