/*
 * PidController.h
 *
 *  Created on: Feb 8, 2014
 *      Author: blackpc
 */

#ifndef PIDCONTROLLER_H_
#define PIDCONTROLLER_H_

#include <iostream>
#include <boost/date_time.hpp>

using namespace std;
using namespace boost::posix_time;

class PidController {
public:
	PidController(float kP, float kI, float kD);

	float compute(float setPoint, float processValue);

private:
	float _kP;
	float _kI;
	float _kD;
	float _previousError;
	float _integral;

	ptime _lastMeasurementTime;
	ptime now();
};

#endif /* PIDCONTROLLER_H_ */
