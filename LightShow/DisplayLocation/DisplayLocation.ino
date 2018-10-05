#include <SPI.h>
//#include <EEPROM.h>
#include "RF24.h"
//#include "RF24Network.h"
//#include "RF24Mesh.h"
#include "LedStrip.h"
#include "PaletteDefinitions.h"

/*
DisplayLocation.ino

Created: 9/14/2018 7:37:05 AM
Author: jason.higinbotham
*/

//#define NODE_ID 5
#define NODE_ID 0xE8E8F0F0B5LL
#define RADIO_CHANNEL 113

#define LED_PIN_CIRCLE 3
#define LED_PIN_HORIZONTAL 5
#define LED_PIN_VERTICAL 6

#define NUM_LEDS_CIRCLE 120
#define NUM_LEDS_HORIZONTAL 60
#define NUM_LEDS_VERTICAL 60

LedStrip circleStrip(NUM_LEDS_CIRCLE, LED_PIN_CIRCLE);
LedStrip horizontalStrip(NUM_LEDS_HORIZONTAL, LED_PIN_HORIZONTAL);
LedStrip verticalStrip(NUM_LEDS_VERTICAL, LED_PIN_VERTICAL);

RF24 radio(9, 10);


//RF24Network network(radio);
//RF24Mesh mesh(radio, network);

const uint64_t NODE_1 = 0xE8E8F0F0F1LL;
const uint64_t NODE_2 = 0xE8E8F0F0E2LL;
const uint64_t NODE_3 = 0xE8E8F0F0D3LL;
const uint64_t NODE_4 = 0xE8E8F0F0C4LL;
const uint64_t NODE_5 = 0xE8E8F0F0B5LL;
const uint64_t NODE_6 = 0xE8E8F0F0A6LL;

byte currentPatternId = 1;
//uint32_t sleepTimer;

void setup()
{
	delay(3000);

	Serial.begin(115200);

	radio.begin();
	radio.setPALevel(RF24_PA_LOW);
	radio.setChannel(RADIO_CHANNEL);
	radio.setDataRate(RF24_250KBPS);
	radio.setRetries(5, 15);

	radio.enableDynamicPayloads();

	radio.openReadingPipe(1, NODE_ID);

	radio.startListening();

	radio.printDetails();

	//mesh.setNodeID(NODE_ID);
	//mesh.begin(RADIO_CHANNEL, RF24_250KBPS);
	//radio.setPALevel(RF24_PA_LOW);
}

void loop()
{
	//mesh.update();
	//
	//if (millis() - sleepTimer >= 1000)
	//{
	//sleepTimer = millis();
	//
	//if (!mesh.checkConnection())
	//{
	//mesh.renewAddress();
	//}
	//}
	//
	//while (network.available())
	//{
	//RF24NetworkHeader header;
	//byte patternId;
	//network.read(header, &patternId, sizeof(patternId));
	//
	//currentPatternId = patternId;
	//}
	//
	RXData();
	RunCurrentPattern();
}

void RXData()
{
	if(radio.available())
	{
		radio.read(&currentPatternId, sizeof(byte));
		Serial.print("RX PatternId: ");
		Serial.println(currentPatternId);
	}
}

void RunCurrentPattern()
{
	switch (currentPatternId)
	{
		case 0: Stop(); break;
		case 1: Pattern1(); break;
		case 2: Pattern2(); break;
		case 3: Pattern3(); break;
		case 4: Pattern4(); break;
		case 5: Pattern5(); break;
		case 6: Pattern6(); break;
		case 7: Pattern7(); break;
		case 8: Pattern8(); break;
		case 9: Pattern9(); break;
		case 10: Pattern10(); break;
		case 11: Pattern11(); break;
		case 12: Pattern12(); break;
		case 13: Pattern13(); break;
		default: Stop(); break;
	}
}

void Stop()
{
	circleStrip.Off();
	horizontalStrip.Off();
	verticalStrip.Off();
}

void Pattern1()
{
	circleStrip.RainbowWithGlitter();
	horizontalStrip.RainbowWithGlitter();
	verticalStrip.RainbowWithGlitter();
}

void Pattern2()
{
	circleStrip.Confetti();
	horizontalStrip.Confetti();
	verticalStrip.Confetti();
}

uint8_t theaterHue = 0;
void Pattern3()
{
	if (theaterHue > 255)
	{
		theaterHue = 0;
	}
	TheaterChase(theaterHue, 50);
	theaterHue++;
}

void Pattern4()
{
	CRGB color;
	int cIndex = random(4);
	switch (cIndex)
	{
		case 1:color = CRGB::RoyalBlue; break;
		case 2:color = CRGB::Purple; break;
		case 3:color = CRGB::Gold; break;
	}
	
	for (int i = 0; i < 3; i++)
	{
		circleStrip.SetAllPixels(color);
		horizontalStrip.SetAllPixels(color);
		verticalStrip.SetAllPixels(color);
		circleStrip.Show();
		horizontalStrip.Show();
		verticalStrip.Show();

		EVERY_N_MILLISECONDS(100)
		{
			circleStrip.SetAllPixels(CRGB::Black);
			horizontalStrip.SetAllPixels(CRGB::Black);
			verticalStrip.SetAllPixels(CRGB::Black);
			circleStrip.Show();
			horizontalStrip.Show();
			verticalStrip.Show();
		}
	}
}

void Pattern5()
{
	circleStrip.ShowPalette(fairygarden_gp);
	horizontalStrip.ShowPalette(fairygarden_gp);
	verticalStrip.ShowPalette(fairygarden_gp);
	
}

void Pattern6()
{
	circleStrip.ShowPalette(hangonfatboy_gp);
	horizontalStrip.ShowPalette(hangonfatboy_gp);
	verticalStrip.ShowPalette(hangonfatboy_gp);
}

void Pattern7()
{
	circleStrip.ShowPalette(carousel_gp);
	horizontalStrip.ShowPalette(carousel_gp);
	verticalStrip.ShowPalette(carousel_gp);
}

void Pattern8()
{
	circleStrip.ShowPalette(Blue_Cyan_Yellow_gp);
	horizontalStrip.ShowPalette(Blue_Cyan_Yellow_gp);
	verticalStrip.ShowPalette(Blue_Cyan_Yellow_gp);
}

void Pattern9()
{
	circleStrip.ShowPalette(spellbound_gp);
	horizontalStrip.ShowPalette(spellbound_gp);
	verticalStrip.ShowPalette(spellbound_gp);
}

void Pattern10()
{
	circleStrip.Fill(CRGB::Purple);
	horizontalStrip.Fill(CRGB::Purple);
	verticalStrip.Fill(CRGB::Purple);
}

void Pattern11()
{
	circleStrip.Fill(CRGB::RoyalBlue);
	horizontalStrip.Fill(CRGB::RoyalBlue);
	verticalStrip.Fill(CRGB::RoyalBlue);
}

void Pattern12()
{
	circleStrip.Fill(CRGB::Gold);
	horizontalStrip.Fill(CRGB::Gold);
	verticalStrip.Fill(CRGB::Gold);
}

void Pattern13()
{
	circleStrip.SetAllPixels(CRGB::RoyalBlue);
	horizontalStrip.SetAllPixels(CRGB::RoyalBlue);
	verticalStrip.SetAllPixels(CRGB::RoyalBlue);
	circleStrip.Show();
	horizontalStrip.Show();
	verticalStrip.Show();

	EVERY_N_MILLISECONDS(100)
	{
		circleStrip.SetAllPixels(CRGB::Black);
		horizontalStrip.SetAllPixels(CRGB::Black);
		verticalStrip.SetAllPixels(CRGB::Black);
		circleStrip.Show();
		horizontalStrip.Show();
		verticalStrip.Show();
	}
}

void TheaterChase(int hue, int speedDelay)
{
	int longStripNum = 120;
	int shortStripNum = 60;
	
	for (int i = 0; i < 3; i++)
	{
		EVERY_N_MILLISECONDS(speedDelay)
		{
			for (int j = 0; j < longStripNum; j = j + 3)
			{
				circleStrip.SetPixel(i + j, hue);
			}
			for (int k = 0; k < shortStripNum; k = k + 3)
			{
				horizontalStrip.SetPixel(i + k, hue);
				verticalStrip.SetPixel(i + k, hue);
			}

			circleStrip.Show();
			horizontalStrip.Show();
			verticalStrip.Show();
		}
		
		for (int l = 0; l < longStripNum; l = l + 3)
		{
			circleStrip.SetPixel(i + l, 0, 0, 0);
		}
		for (int m = 0; m < shortStripNum; m = m + 3)
		{
			horizontalStrip.SetPixel(i + m, 0, 0, 0);
			verticalStrip.SetPixel(i + m, 0, 0, 0);
		}
	}
}