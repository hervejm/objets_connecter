#pragma once
#include <Arduino.h>

#define VAL_MAX_SENSOR 700
class Hl69
{
public:
	Hl69();
	boolean initSensor();
	int sensorValue();
	double calculatePercentageOfValue(int val);
};
