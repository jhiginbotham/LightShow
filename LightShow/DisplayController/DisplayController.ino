#include <SPI.h>
//#include <EEPROM.h>
#include "RF24.h"
//#include "RF24Network.h"
//#include "RF24Mesh.h"
#include "Keypad.h"
//#include "printf.h"

/*
* DisplayController.ino
*
* Created: 9/14/2018 7:37:22 AM
* Author: jason.higinbotham
*/

#define ROWS 4
#define COLS 4

//#define NODE_MASTER 0
#define RADIO_CHANNEL 113

//#define NODE_1 1
//#define NODE_2 2
//#define NODE_3 3
//#define NODE_4 4
//#define NODE_5 5
//#define NODE_6 6

char keys[ROWS][COLS] = {
	{
		'1','2','3','4'
	},
	{
		'5','6','7','8'
	},
	{
		'9','A','B','C'
	},
	{
		'D','E','F','G'
	}
};

byte rowPins[ROWS] = {0,8,2,3};
byte colPins[COLS] = {4,5,6,7};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

RF24 radio(9, 10);


//RF24Network network(radio);
//RF24Mesh mesh(radio, network);


const uint64_t NODE_1 = 0xE8E8F0F0F1LL;
const uint64_t NODE_2 = 0xE8E8F0F0E2LL;
const uint64_t NODE_3 = 0xE8E8F0F0D3LL;
const uint64_t NODE_4 = 0xE8E8F0F0C4LL;
const uint64_t NODE_5 = 0xE8E8F0F0B5LL;
const uint64_t NODE_6 = 0xE8E8F0F0A6LL;


void setup()
{
	//mesh.setNodeID(NODE_MASTER);
	//mesh.begin(RADIO_CHANNEL, RF24_1MBPS);
	Serial.begin(115200);

	radio.begin();
	radio.setPALevel(RF24_PA_LOW);
	radio.setChannel(RADIO_CHANNEL);
	radio.setDataRate(RF24_250KBPS);
	radio.setRetries(5, 15);

	radio.enableDynamicPayloads();

	radio.stopListening();

	//radio.printDetails();
}

void loop()
{
	//mesh.update();
	//mesh.DHCP();
	//
	//if (network.available())
	//{
	//RF24NetworkHeader header;
	//network.peek(header);
	//}

	ReadKey();
}

void ReadKey()
{
	char key = keypad.getKey();
	if (key != NO_KEY)
	{
		Serial.print("Key Pressed: ");
		Serial.println(key);
		switch (key)
		{
			case '1': Scene1(); break;
			case '2': Scene2(); break;
			case '3': Scene3(); break;
			case '4': Scene4(); break;
			case '5': Scene5(); break;
			case '6': Scene6(); break;
			case '7': Scene7(); break;
			case '8': Scene8(); break;
			case '9': Scene9(); break;
			case 'A': Scene10(); break;
			case 'B': Scene11(); break;
			case 'C': Scene12(); break;
			case 'D': Scene13(); break;
			case 'E': Scene14(); break;
			case 'F': Scene15(); break;
			case 'G': StopScene(); break;
		}
	}
}

void StopScene()
{
	TransmitStopToAllLocations();
}

void Scene1()
{
	TransmitPatternToAllLocations(1);
}

void Scene2()
{
	TransmitPatternToAllLocations(2);
}

void Scene3() {
	TransmitPatternToAllLocations(3);
}

void Scene4()
{
	TransmitPatternToAllLocations(4);
}

void Scene5()
{
	TransmitPatternToAllLocations(5);
}

void Scene6()
{
	TransmitPatternToAllLocations(6);
}

void Scene7()
{
	TransmitPatternToAllLocations(7);
}

void Scene8()
{
	TransmitPatternToAllLocations(8);
}

void Scene9()
{
	TransmitPatternToAllLocations(9);
}

void Scene10()
{
	TransmitPatternToAllLocations(10);
}

void Scene11()
{
	TransmitPatternToAllLocations(11);
}

void Scene12()
{
	TransmitPatternToAllLocations(12);
}

void Scene13()
{
	TransmitPatternToAllLocations(13);
}

void Scene14()
{
	TransmitPatternToWonderWheel(1);
}

void Scene15()
{
	TransmitPatternToWonderWheel(2);
}

void TransmitPatternToAllLocations(byte patternId)
{
	TransmitPatternToLocation(NODE_1, patternId);
	TransmitPatternToLocation(NODE_2, patternId);
	TransmitPatternToLocation(NODE_3, patternId);
	TransmitPatternToLocation(NODE_4, patternId);
	TransmitPatternToLocation(NODE_5, patternId);
	//for (int i = 0; i < mesh.addrListTop; i++)
	//{
	//if (mesh.addrList[i].nodeID != 6)
	//{
	//RF24NetworkHeader header(mesh.addrList[i].address, OCT);
	//network.write(header, &patternId, sizeof(patternId));
	//}
	//}
}

void TransmitStopToAllLocations()
{
	TransmitPatternToLocation(NODE_1, 0);
	TransmitPatternToLocation(NODE_2, 0);
	TransmitPatternToLocation(NODE_3, 0);
	TransmitPatternToLocation(NODE_4, 0);
	TransmitPatternToLocation(NODE_5, 0);
	TransmitPatternToLocation(NODE_6, 0);
	//byte patternId = 0;
	//for (int i = 0; i < mesh.addrListTop; i++)
	//{
	//RF24NetworkHeader header(mesh.addrList[i].address, OCT);
	//network.write(header, &patternId, sizeof(patternId));
	//}
}

void TransmitPatternToWonderWheel(byte patternId)
{
	TransmitPatternToLocation(NODE_6, patternId);

	//TransmitPatternToLocation(6, patternId);
}

void TransmitPatternToLocation(uint64_t nodeId, byte patternId)
{
	Serial.print("TX Sent to: ");
	PrintNodeId(nodeId);
	Serial.print(" PatterId: ");
	Serial.println(patternId);

	radio.stopListening();
	radio.openWritingPipe(nodeId);
	bool rslt = radio.write(&patternId, sizeof(byte));

	if (rslt)
	{
		Serial.print("ACK RX from ");
		PrintNodeId(nodeId);
		} else {
		Serial.print("TX Failed for ");
		PrintNodeId(nodeId);
	}
	Serial.println();
	//for (int i = 0; i < mesh.addrListTop; i++)
	//{
	//if (mesh.addrList[i].nodeID == nodeId)
	//{
	//RF24NetworkHeader header(mesh.addrList[i].address, OCT);
	//network.write(header, &patternId, sizeof(patternId));
	//}
	//}
}

void PrintNodeId(uint64_t nodeId)
{
	switch (nodeId)
	{
		case NODE_1: Serial.println(" NODE 1 "); break;
		case NODE_2: Serial.println(" NODE 2 "); break;
		case NODE_3: Serial.println(" NODE 3 "); break;
		case NODE_4: Serial.println(" NODE 4 "); break;
		case NODE_5: Serial.println(" NODE 5 "); break;
		case NODE_6: Serial.println(" NODE 6 "); break;
		default: Serial.println(" Unrecognized Node "); break;
	}
}