#include "Hl69.h"
#include <Arduino.h>

	byte humidity_sensor_pin = A7;
	byte humidity_sensor_vcc = 2;

	Hl69::Hl69()
	{
	}

	boolean Hl69::initSensor()
	{
		// Init the humidity sensor board
		pinMode(humidity_sensor_vcc, OUTPUT);
		digitalWrite(humidity_sensor_vcc, LOW);

		// Setup Serial
		while (!Serial);
		delay(1000);
		Serial.begin(115200);
		return true;
	}

	int Hl69::sensorValue()
	{
		digitalWrite(humidity_sensor_vcc, HIGH);
		delay(50);
		int value = analogRead(humidity_sensor_pin);
		digitalWrite(humidity_sensor_vcc, LOW);
		return (int)1023 - value;
	}

	double Hl69::calculatePercentageOfValue(int val)
	{
		double percentValue = (val * 100) / VAL_MAX_SENSOR;
		if(percentValue > 100) //Plafond car marge erreur capeur....
		{
			percentValue = 100;
		}
		return percentValue;
	}


