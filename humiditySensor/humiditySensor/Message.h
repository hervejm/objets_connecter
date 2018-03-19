#pragma once

class Message
{
public:
	Message();
	void encodeAndSendMessage(int value, int idExt);
	int calculatePayloadLenght(int value);
	void choseTxAndRxPipe(void);
}; 

