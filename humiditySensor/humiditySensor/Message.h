#pragma once

class Message
{
public:
	Message();
	void encodeAndSendOneMessage(const char type, int sensorID, int data);
	int calculatePayloadLenght(int value);
	void choseTxAndRxPipe(void);
	void transmitterInit();
}; 

