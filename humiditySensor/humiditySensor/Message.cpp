#include "Message.h"
#include "RF24.h"
#include "RF24_config.h"
#include "printf.h"
#include "sensorID.h"


#ifdef WITHOUT_RELAY
const uint64_t rxPipe = 0xE8E8E8E8E8LL;
const uint64_t txPipe = (DEV_NUMBER <6 ? 0xF0F0F0F000LL | (DEV_NUMBER & 0xff) :
	0xF6F6F6F6F6LL);
#else
const uint64_t rxPipe = 0xE8E8E8E8E8LL;
const uint64_t txPipe = (DEV_NUMBER <6 ? 0xF0F0F0F000LL |
(DEV_NUMBER & 0xff) :
	0x4545454500LL | (DEV_NUMBER & 0xff));
#endif

RF24 transmitter(RF24_CEPIN, RF24_CSPIN);
char payload[32 + 1] = { 0 };
Message::Message()
{
	printf_begin();
}

void Message::transmitterInit()
{
	transmitter.begin();
	//                                 Default radio settings
	transmitter.enableDynamicPayloads();
	transmitter.setDataRate(RF24_2MBPS);
	transmitter.setPALevel(RF24_PA_MAX);
	transmitter.setChannel(0x2A);
	// delay 1ms, 3 retries
	// 0 ­ 250us, 15 ­ 4000us
	transmitter.setRetries(1, 3);
	transmitter.openWritingPipe(txPipe);
	transmitter.openReadingPipe(1, rxPipe);
	transmitter.setAutoAck(true);
	transmitter.startListening();
	transmitter.printDetails();
}

void Message::encodeAndSendOneMessage(const char type,int sensorID, double data)
{
	if(type == 'v')
	{
		char payload[32];
		sprintf(payload, "%s/%02d;%d", HUMIDITY_SENSOR, sensorID, data);
		// verify if channel is free
		if (!transmitter.testCarrier()) {
			// send payload
			transmitter.stopListening();
			transmitter.write((void *)payload, strlen(payload) + 1);
			transmitter.startListening();
		}
	}
	else if(type == 'c')
	{
		char payload[32];
		sprintf(payload, "%s/%02d;%d", BOARD_TEMP, sensorID, data);
	}

}

