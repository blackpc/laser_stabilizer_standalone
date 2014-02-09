#include <iostream>
#include <iomanip>
#include <math.h>
#include <boost/bind.hpp>

#include "maestro/MaestroController.h"
#include "imu/RazorAHRS.h"

using namespace std;

#define Pitch 1
#define Roll  2
#define rad2deg (M_PI / 180.0)

MaestroController* maestro;
RazorAHRS* imu;

void on_error(const string &msg)
{
	cerr << "  " << "ERROR: " << msg << endl;
}

void on_data(const float data[])
{
	// !!! Degrees

	float pitch = data[1];
	float roll = data[2];
	maestro->setAngle(Pitch, -pitch);
	maestro->setAngle(Roll, -roll);
}

int main(int argc, char **argv) {

	maestro = new MaestroController("/dev/ttyACM0");

	maestro->setParameters(Pitch, 1450, 9);
	maestro->setParameters(Roll, 1530, 9);

	maestro->setAngle(Pitch, 10);
	maestro->setAngle(Roll, 10);


	while (true) {
		cout << "Pitch process value = " << maestro->getAngle(Pitch) << endl;
		cout << "Roll  process value = " << maestro->getAngle(Roll) << endl;
		usleep(100);
	}
	return 0;

	imu = new RazorAHRS("/dev/ttyUSB0", on_data, on_error, RazorAHRS::YAW_PITCH_ROLL);
	getchar();  // wait for RETURN key

	return 0;
}
