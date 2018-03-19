#include "Message.h"
#define DEV_NUMBER 1
#ifdef DEV_NUMBER < 6
	const uint64_t rxPipe = 0xE8E8E8E8E8LL;
	const uint64_t txPipe = (DEV_NUMBER <6 ? 0xF0F0F0F000LL | (DEV_NUMBER & 0xff) :
		0xF6F6F6F6F6LL);
#else
	const uint64_t rxPipe = 0xE8E8E8E8E8LL;
	const uint64_t txPipe = (DEV_NUMBER <6 ? 0xF0F0F0F000LL |
	(DEV_NUMBER & 0xff) :
		0x4545454500LL | (DEV_NUMBER & 0xff));
#endif

Message::Message()
{
}

void Message::encodeAndSendMessage(int value, int idExt)
{
	int taillePayload;
	calculatePayloadLenght(value);
	char payload[50];
	payload[0] = 0xFE;
	payload[1] = 0x01;
	payload[2] = 0x00;
	//payload[4] = 

}

int Message::calculatePayloadLenght(int value)
{
	int payloadLenght;

}

void Message::choseTxAndRxPipe(void)
{


}
