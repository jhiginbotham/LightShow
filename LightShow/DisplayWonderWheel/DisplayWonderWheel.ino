#include <SPI.h>
#include "RF24.h"
#include "LedStrip.h"
#include "PaletteDefinitions.h"

/*
* DisplayWonderWheel.ino
*
* Created: 9/19/2018 8:49:07 AM
* Author: Jason.Higinbotham
*/

#define NODE_ID 0xE8E8F0F0A6LL

#define RADIO_CHANNEL 113

#define LED_PIN_TOP 5
#define LED_PIN_BOTTOM 3

#define NUM_LEDS_TOP 210
#define NUM_LEDS_BOTTOM 210

const uint64_t NODE_1 = 0xE8E8F0F0F1LL;
const uint64_t NODE_2 = 0xE8E8F0F0E2LL;
const uint64_t NODE_3 = 0xE8E8F0F0D3LL;
const uint64_t NODE_4 = 0xE8E8F0F0C4LL;
const uint64_t NODE_5 = 0xE8E8F0F0B5LL;
const uint64_t NODE_6 = 0xE8E8F0F0A6LL;

LedStrip topStrip(NUM_LEDS_TOP, LED_PIN_TOP);
LedStrip bottomStrip(NUM_LEDS_BOTTOM, LED_PIN_BOTTOM);

RF24 radio(9, 10);

byte currentPatternId = 3;

void setup()
{
	delay(3000);

	Serial.begin(115200);

	radio.begin();
	radio.setPALevel(RF24_PA_LOW);
	radio.setChannel(RADIO_CHANNEL);
	radio.setDataRate(RF24_250KBPS);
	radio.setRetries(5, 15);

	radio.openReadingPipe(1, NODE_ID);

	radio.enableDynamicPayloads();

	radio.startListening();

	radio.printDetails();
}

void loop()
{
	RXData();
	RunCurrentPattern();
}

void RXData()
{
	while(radio.available())
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
		case 1: RunTopScene(); break;
		case 2: RunBottomScene(); break;
		case 3: InitOn(); break;
		default: Stop(); break;
	}
}

void RunTopScene(){
	TopScene();
}

void RunBottomScene(){
	BottomScene();
}

void Stop()
{
	topStrip.Off();
	bottomStrip.Off();
}


void InitOn()
{
	topStrip.RainbowWithGlitter();
	bottomStrip.RainbowWithGlitter();
}



void BottomScene()
{
	static byte initialHue = 0;
	initialHue = initialHue + 1;
	byte changeInHue = 255 / bottomStrip.NumberOfLeds();
	bottomStrip.RainbowWithGlitter(initialHue, changeInHue);
}

void TopScene()
{
	static byte initialHue = 0;
	initialHue = initialHue + 2;
	byte changeInHue = 255 / bottomStrip.NumberOfLeds();
	topStrip.RainbowWithGlitter(initialHue, changeInHue);
}

void TopSceneMeteor()
{
	uint8_t numberOfLeds = topStrip.NumberOfLeds();
	byte meteorSize = 75;
	byte meteorTrailDecay = 64;
	boolean meteorRandomDecay = true;
	CRGB color = CRGB::Purple;

	topStrip.SetAllPixels(0 , 0 , 0);

	for (int j = 0; j < 3; j++)
	{
		switch (j)
		{
			case 0: color = CRGB::Purple; break;
			case 1: color = CRGB::RoyalBlue; break;
			case 2: color = CRGB::Gold; break;
		}

		for (int i = 0; i < numberOfLeds + meteorSize; i++)
		{
			FadeBrightnessOfAllLedsOneStep(numberOfLeds, meteorRandomDecay, meteorTrailDecay);
			DrawMeteor(i, color, meteorSize, numberOfLeds);
			topStrip.Show();
			RXData();
			if (currentPatternId == 0){
				Stop();
				return;
			}
		}
	}
}

void FadeBrightnessOfAllLedsOneStep(uint8_t numberOfLeds, boolean meteorRandomDecay, byte meteorTrailDecay)
{
	for (int i = 0; i < numberOfLeds; i++)
	{
		if ((!meteorRandomDecay) || (random(10) > 5))
		{
			topStrip.FadeToBlack(i, meteorTrailDecay);
		}
	}
}

void DrawMeteor(int ledIndex, CRGB color, byte meteorSize, uint8_t numberOfLeds)
{
	for (int i = 0; i < meteorSize; i++)
	{
		if ((ledIndex - i < numberOfLeds) && (ledIndex - i >= 0))
		{
			topStrip.SetPixel(ledIndex - i, color);
		}
	}
}
