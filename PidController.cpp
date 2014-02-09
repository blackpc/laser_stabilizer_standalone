/*
 * PidController.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: blackpc
 */

#include "PidController.h"

PidController::PidController(float kP, float kI, float kD)
	: _kP(kP), _kI(kI), _kD(kD)
{
	_lastMeasurementTime = now();
	_previousError = 0;
	_integral = 0;
}

float PidController::compute(float setPoint, float processValue) {
	time_duration dt = now() - _lastMeasurementTime;

	float error = setPoint - processValue;
	_integral += error * dt.total_seconds();
	float derivative = (error - _previousError) / dt.total_seconds();
	float output = _kP * error + _kI * _integral + _kD * derivative;
	_previousError = error;

	return output;
}

ptime PidController::now() {
	return microsec_clock::local_time();
}
