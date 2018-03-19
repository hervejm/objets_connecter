/*
 Name:		humiditySensor.ino
 Created:	15/03/2018 09:34:25
 Author:	j-m83
*/
#include "Hl69.h"
#include "CoreTemp.h"
#include <Arduino.h>
#include "Message.h"

boolean initVerify;
Hl69 mySensor;
CoreTemp coreDegree;
// the setup function runs once when you press reset or power the board
void setup() {
	mySensor = Hl69();
	coreDegree = CoreTemp();
	initVerify = mySensor.initSensor();
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (initVerify = true) {
		int result = mySensor.sensorValue();
		Serial.print("Value is : ");
		Serial.println(result);
		double Coretemperature;
		Coretemperature = coreDegree.GetTemp();
		
		//Serial.print("Core temp : ");
		//Serial.println(Coretemperature);
	}
	
}
