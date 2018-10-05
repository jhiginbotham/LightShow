#include "Keypad.h"

/*
* TestKeypadController.ino
*
* Created: 9/17/2018 12:03:57 PM
* Author: Jason.Higinbotham
*/

#define ROWS 4
#define COLS 4

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



void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(115200);
}

void loop()
{
	char key = keypad.getKey();
	if (key != NO_KEY)
	{
		Serial.write(key);
		switch (key) {
			case '1': BlinkNTimes(1); break;
			case '2': BlinkNTimes(2); break;
			case '3': BlinkNTimes(3); break;
			case '4': BlinkNTimes(4); break;
			case '5': BlinkNTimes(5); break;
			case '6': BlinkNTimes(6); break;
			case '7': BlinkNTimes(7); break;
			case '8': BlinkNTimes(8); break;
			case '9': BlinkNTimes(9); break;
			case 'A': BlinkNTimes(10); break;
			case 'B': BlinkNTimes(11); break;
			case 'C': BlinkNTimes(12); break;
			case 'D': BlinkNTimes(13); break;
			case 'E': BlinkNTimes(14); break;
			case 'F': BlinkNTimes(15); break;
			case 'G': BlinkNTimes(16); break;
		}
	}
}


void BlinkNTimes(int timesToBlink)
{
		for (int i = 0; i < timesToBlink; i++)
		{
			digitalWrite(LED_BUILTIN, HIGH);
			digitalWrite(LED_BUILTIN, LOW);
		}
}
