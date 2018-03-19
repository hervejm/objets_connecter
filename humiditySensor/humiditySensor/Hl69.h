#pragma once
#include <Arduino.h>

class Hl69
{
public:
	Hl69();
	boolean initSensor();
	int sensorValue();
};
