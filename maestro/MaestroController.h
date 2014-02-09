/*
 * MaestroController.h
 *
 *  Created on: Feb 6, 2014
 *      Author: lamplight
 */

#ifndef MAESTROCONTROLLER_H_
#define MAESTROCONTROLLER_H_

#include <iostream>
#include <map>

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#ifdef _WIN32
#define O_NOCTTY 0
#else
#include <termios.h>
#endif

using namespace std;

struct ChannelSettings {
	int center;
	double degreeStep;
};

class MaestroController {

public:

	MaestroController(string device = "/dev/ttyACM0");
	virtual ~MaestroController();

	void setParameters(int channel, int center, double degreeStep);
	void setAngle(int channel, double angle);
	float getAngle(int channel);

private:

	int deviceFileDescriptor;
	map<int, ChannelSettings> _settings;

	void initDevice(string device);
	void setTarget(int channel, int target);
};

#endif /* MAESTROCONTROLLER_H_ */
