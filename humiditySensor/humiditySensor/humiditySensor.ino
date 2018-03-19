/*
 Name:		humiditySensor.ino
 Created:	15/03/2018 09:34:25
 Author:	j-m83
*/
#include "Hl69.h"
#include "CoreTemp.h"
#include <Arduino.h>
#include "Message.h"
#include "MsTimer2.h"
#include "sensorID.h"

boolean initVerify;
Hl69 mySensor;
Message msg;
int cmptSeconde = 0;
int oldResult = 0;
// the setup function runs once when you press reset or power the board
void setup() {
	mySensor = Hl69();
	initVerify = mySensor.initSensor();
	msg = Message();
	msg.transmitterInit();
	MsTimer2::set(1000, Interrupt);
	MsTimer2::start();
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (initVerify = true) {
	}
	
}

void Interrupt()
{
	cmptSeconde++;
	if (cmptSeconde == 60) {
		cmptSeconde = 0;
		CoreTemp coreDegree = CoreTemp();
		double Coretemperature;
		Coretemperature = coreDegree.GetTemp();
		Message msg = Message();
		msg.encodeAndSendOneMessage('c', DEV_NUMBER, Coretemperature);
		Serial.println("Core temperature send");
	}
	
	int result = mySensor.sensorValue();
	int percent = mySensor.calculatePercentageOfValue(result);
	if (percent < oldResult-3 || percent > oldResult+3) {
		oldResult = percent;
		Message msg = Message();
		msg.encodeAndSendOneMessage('v', DEV_NUMBER, percent);
		Serial.print("Value of sensor send :");
		Serial.println(percent);
	}
}

