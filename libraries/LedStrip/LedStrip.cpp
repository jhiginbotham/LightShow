/*
* LedStrip.cpp
*
* Created: 9/27/2018 12:34:28 PM
* Author: jason.higinbotham
*/

#include "LedStrip.h"

#define COLOR_ORDER GRB
#define LED_TYPE    WS2812B
#define BRIGHTNESS  255

#define MAX_INT_VALUE 65536

LedStrip::LedStrip(uint8_t numberOfLeds, uint8_t ledPin)
{
	_numberOfLeds = numberOfLeds;
	_leds = new CRGB[_numberOfLeds];

	switch (ledPin)
	{
		case 3:
		FastLED.addLeds<LED_TYPE, 3, COLOR_ORDER>(_leds, _numberOfLeds);
		break;
		case 5:
		FastLED.addLeds<LED_TYPE, 5, COLOR_ORDER>(_leds, _numberOfLeds);
		break;
		case 6:
		FastLED.addLeds<LED_TYPE, 6, COLOR_ORDER>(_leds, _numberOfLeds);
		break;
		default:
		FastLED.addLeds<LED_TYPE, 3, COLOR_ORDER>(_leds, _numberOfLeds);
		break;
	}

	FastLED.setBrightness(BRIGHTNESS);
	FastLED.clear();
}

LedStrip::~LedStrip()
{
	delete[] _leds;
}

//Public Action Methods
void LedStrip::ColorWaves(CRGBPalette16& palette)
{
	static uint16_t sPseudotime = 0;
	static uint16_t sLastMillis = 0;
	static uint16_t sHue16 = 0;
	
	uint8_t sat8 = beatsin88( 87, 220, 250);
	uint8_t brightdepth = beatsin88( 341, 96, 224);
	uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
	uint8_t msmultiplier = beatsin88(147, 23, 60);
	
	uint16_t hue16 = sHue16;
	uint16_t hueinc16 = beatsin88(113, 300, 1500);
	
	uint16_t ms = millis();
	uint16_t deltams = ms - sLastMillis ;
	sLastMillis  = ms;
	sPseudotime += deltams * msmultiplier;
	sHue16 += deltams * beatsin88( 400, 5,9);
	uint16_t brightnesstheta16 = sPseudotime;
	
	for( uint16_t i = 0 ; i < _numberOfLeds; i++)
	{
		hue16 += hueinc16;
		uint8_t hue8 = hue16 / 256;
		uint16_t h16_128 = hue16 >> 7;
		if( h16_128 & 0x100)
		{
			hue8 = 255 - (h16_128 >> 1);
		}
		else
		{
			hue8 = h16_128 >> 1;
		}
		
		brightnesstheta16  += brightnessthetainc16;
		uint16_t b16 = sin16( brightnesstheta16  ) + 32768;
		
		uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
		uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
		bri8 += (255 - brightdepth);
		
		uint8_t index = hue8;
		index = scale8( index, 240);
		
		CRGB newcolor = ColorFromPalette( palette, index, bri8);
		
		uint16_t pixelnumber = i;
		pixelnumber = (_numberOfLeds - 1) - pixelnumber;
		
		nblend(_leds[pixelnumber], newcolor, 128);
	}

	FastLED.show();
}

void LedStrip::Rainbow()
{
	fill_rainbow(_leds, _numberOfLeds, _gHue, 7);
	_gHue++;
	FastLED.show();
}

void LedStrip::RainbowWithGlitter(uint8_t hue, byte changeInHue)
{
	fill_rainbow(_leds, _numberOfLeds, hue, changeInHue);
	AddGlitter(100);
	FastLED.show();
}

void LedStrip::RainbowWithGlitter()
{
	Rainbow();
	AddGlitter(100);
	FastLED.show();
}

void LedStrip::Confetti()
{
	fadeToBlackBy(_leds, _numberOfLeds, 10);
	int pos = random16(_numberOfLeds);
	_leds[pos] += CHSV(_gHue + random8(64), 200, 255);
	
	FastLED.show();
}

void LedStrip::Juggle()
{
	fadeToBlackBy(_leds, _numberOfLeds, 20);
	byte dothue = 0;
	for (int i = 0; i < 8; i++)
	{
		_leds[beatsin16(i + 7, 0, _numberOfLeds - 1)] != CHSV(dothue, 200, 255);
		dothue += 32;
	}
	
	FastLED.show();
}

void LedStrip::Fill(byte red, byte green, byte blue)
{
	SetAllPixels(red, green, blue);
	FastLED.show();
}

void LedStrip::Fill(CHSV color)
{
	SetAllPixels(color);
	FastLED.show();
}

void LedStrip::Fill(CRGB color)
{
	SetAllPixels(color);
	FastLED.show();
}

void LedStrip::Off()
{
	Fill(CRGB::Black);
}

void LedStrip::ShowPalette(CRGBPalette16 pal)
{
	static uint8_t startIndex = 0;
	startIndex = startIndex + 2;
	fill_palette(_leds, _numberOfLeds, startIndex, 8, pal, BRIGHTNESS, LINEARBLEND);
	FastLED.show();
}

void LedStrip::Strobe(byte red, byte green, byte blue, int flashDelay)
{
	SetAllPixels(red,green,blue);
	FastLED.show();

	EVERY_N_MILLISECONDS(flashDelay)
	{
		SetAllPixels(0, 0, 0);
		FastLED.show();
	}
}

void LedStrip::Strobe(byte red, byte green, byte blue, int flashDelay, int strobeCount)
{
	for(int i = 0; i < strobeCount; i++)
	{
		Strobe(red, green, blue, flashDelay);
	}
}

void LedStrip::CylonBounce(byte red, byte green, byte blue, int eyeSize, int speedDelay, int returnDelay)
{
	EVERY_N_MILLISECONDS(returnDelay)
	{
		for(int i = 0; i < _numberOfLeds - eyeSize-2; i++)
		{
			EVERY_N_MILLISECONDS(speedDelay)
			{
				SetAllPixels(0, 0, 0);
				SetPixel(i, red/10, green/10, blue/10);
				for(int j = 1; j <= eyeSize; j++)
				{
					SetPixel(i + j, red, green, blue);
				}
				SetPixel(i + eyeSize + 1, red/10, green/10, blue/10);
				FastLED.show();
			}
		}
	}
	
	EVERY_N_MILLISECONDS(returnDelay)
	{
		for(int k = _numberOfLeds - eyeSize-2; k > 0; k--)
		{
			EVERY_N_MILLISECONDS(speedDelay)
			{
				SetAllPixels(0,0,0);
				SetPixel(k, red/10, green/10, blue/10);
				for(int l = 1; l <= eyeSize; l++)
				{
					SetPixel(k + l, red, green, blue);
				}
				SetPixel(k + eyeSize + 1, red/10, green/10, blue/10);
				FastLED.show();
			}
		}
	}
}

void LedStrip::RGBLoop()
{
	for (int i = 0; i < 3; i++)
	{
		//Fade In
		for (int j = 0; j < 256; j++)
		{
			EVERY_N_MILLISECONDS(3)
			{
				switch (i)
				{
					case 0: SetAllPixels(j, 0, 0); break;
					case 1: SetAllPixels(0, j, 0); break;
					case 2: SetAllPixels(0, 0, j); break;
				}
				FastLED.show();
			}
		}

		//Fade OUT
		for (int k = 255; k>= 0; k--)
		{
			EVERY_N_MILLISECONDS(3)
			{
				switch (i)
				{
					case 0: SetAllPixels(k, 0, 0); break;
					case 1: SetAllPixels(0, k, 0); break;
					case 2: SetAllPixels(0 ,0 , k); break;
				}
				FastLED.show();
			}
		}
	}
}

void LedStrip::RunningLights(byte red, byte green, byte blue, int waveDelay)
{
	int position = 0;

	for(int i = 0; i < _numberOfLeds * 2; i++)
	{
		EVERY_N_MILLISECONDS(waveDelay)
		{
			position++;
			for(int j = 0; j < _numberOfLeds; j++)
			{
				SetPixel(j,
				((sin(i + position) * 127 + 128)/255) * red,
				((sin(i + position) * 127 + 128)/255) * green,
				((sin(i + position) * 127 + 128)/255) * blue);
			}

			FastLED.show();
		}
	}
}

void LedStrip::FadeInOut(byte red, byte green, byte blue)
{
	float r, g, b;

	for (int i = 0; i < 256; i = i + 1)
	{
		r = (i / 256.0) * red;
		g = (i / 256.0) * green;
		b = (i / 256.0) * blue;
		SetAllPixels(r, g, b);
		FastLED.show();
	}

	for(int j = 255; j >= 0; j = j - 2)
	{
		r = (j / 256.0) * red;
		g = (j / 256.0) * green;
		b = (j / 256.0) * blue;
		SetAllPixels(r, g, b);
		FastLED.show();
	}
}

void LedStrip::ColorWipe(byte red, byte green, byte blue, int speedDelay)
{
	for(uint16_t i = 0; i < _numberOfLeds; i++)
	{
		EVERY_N_MILLISECONDS(speedDelay)
		{
			SetPixel(i, red, green, blue);
			FastLED.show();
		}
	}
}

void LedStrip::TheaterChase(byte red, byte green, byte blue, int speedDelay)
{
	for (int j = 0; j < 10; j++)
	{
		for (int q = 0; q < 3; q++)
		{
			EVERY_N_MILLISECONDS(speedDelay)
			{
				for (int i = 0; i < _numberOfLeds; i = i + 3)
				{
					SetPixel(i + q, red, green, blue);
				}
				FastLED.show();
			}
						
			for (int i = 0; i < _numberOfLeds; i = i + 3)
			{
				SetPixel(i + q, 0,0,0);
			}
		}
	}
}

void LedStrip::MeteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int speedDelay)
{
	SetAllPixels(0, 0, 0);

	for(int i = 0; i < _numberOfLeds * 2; i++)
	{
		EVERY_N_MILLISECONDS(speedDelay)
		{
			for(int j = 0; j < _numberOfLeds; j++)
			{
				if((!meteorRandomDecay) || (random(10) > 5) )
				{
					FadeToBlack(j, meteorTrailDecay);
				}
			}
			
			for(int k = 0; k < meteorSize; k++)
			{
				if( ( i - k < _numberOfLeds) && (i - k >= 0) )
				{
					SetPixel(i - k, red, green, blue);
				}
			}
			
			FastLED.show();
		}
	}
}

void LedStrip::Bounce(uint8_t hue)
{
	Bounce(_frame, hue);
	FastLED.show();
	IncrementFrame();
}

void LedStrip::Ring(uint8_t hue)
{
	Ring(_frame, hue);
	FastLED.show();
	IncrementFrame();
}

void LedStrip::Wave(uint8_t hue)
{
	Wave(_frame, hue);
	FastLED.show();
	IncrementFrame();
}

void LedStrip::WaveInt(uint8_t hue)
{
	WaveInt(_frame, hue);
	FastLED.show();
	IncrementFrame();
}

void LedStrip::Spark(uint8_t fade, uint8_t hue)
{
	Spark(_frame, fade, hue);
	FastLED.show();
	IncrementFrame();
}

void LedStrip::Spark(uint8_t fade)
{
	Spark(_frame, fade);
	FastLED.show();
	IncrementFrame();
}

void LedStrip::CenterToOutside(byte red, byte green, byte blue, int eyeSize, int speedDelay, int returnDelay)
{
	EVERY_N_MILLISECONDS(returnDelay)
	{
		for(int i = ((_numberOfLeds - eyeSize) / 2); i >= 0; i--)
		{
			EVERY_N_MILLISECONDS(speedDelay)
			{
				SetAllPixels(0, 0, 0);
			
				SetPixel(i, red/10, green/10, blue/10);
				for(int j = 1; j <= eyeSize; j++) {
					SetPixel(i + j, red, green, blue);
				}
				SetPixel(i + eyeSize+1, red/10, green/10, blue/10);
			
				SetPixel(_numberOfLeds-i, red/10, green/10, blue/10);
				for(int j = 1; j <= eyeSize; j++) {
					SetPixel(_numberOfLeds - i - j, red, green, blue);
				}
				SetPixel(_numberOfLeds - i - eyeSize-1, red/10, green/10, blue/10);
				FastLED.show();
			}
		}
	}
}

void LedStrip::OutsideToCenter(byte red, byte green, byte blue, int eyeSize, int speedDelay, int returnDelay)
{
	EVERY_N_MILLISECONDS(returnDelay)
	{
		for(int i = 0; i <= ((_numberOfLeds - eyeSize) / 2); i++) {
			EVERY_N_MILLISECONDS(speedDelay){
				SetAllPixels(0,0,0);
				
				SetPixel(i, red/10, green/10, blue/10);
				for(int j = 1; j <= eyeSize; j++) {
					SetPixel(i+j, red, green, blue);
				}
				SetPixel(i+eyeSize+1, red/10, green/10, blue/10);
				
				SetPixel(_numberOfLeds - i, red/10, green/10, blue/10);
				for(int j = 1; j <= eyeSize; j++) {
					SetPixel(_numberOfLeds - i - j, red, green, blue);
				}
				SetPixel(_numberOfLeds - i - eyeSize - 1, red/10, green/10, blue/10);
				
				FastLED.show();
			}
		}
	}
}

void LedStrip::LeftToRight(byte red, byte green, byte blue, int eyeSize, int speedDelay, int returnDelay)
{
	EVERY_N_MILLISECONDS(returnDelay)
	{
		for(int i = 0; i < _numberOfLeds - eyeSize - 2; i++) {
			EVERY_N_MILLISECONDS(speedDelay){
				SetAllPixels(0,0,0);
				SetPixel(i, red/10, green/10, blue/10);
				for(int j = 1; j <= eyeSize; j++) {
					SetPixel(i + j, red, green, blue);
				}
				SetPixel(i +eyeSize + 1, red/10, green/10, blue/10);
				FastLED.show();
			}
		}
	}
}

void LedStrip::RightToLeft(byte red, byte green, byte blue, int eyeSize, int speedDelay, int returnDelay)
{
	EVERY_N_MILLISECONDS(returnDelay)
	{
		for(int i = _numberOfLeds - eyeSize - 2; i > 0; i--) {
			EVERY_N_MILLISECONDS(speedDelay)
			{
				SetAllPixels(0,0,0);
				SetPixel(i, red/10, green/10, blue/10);
				for(int j = 1; j <= eyeSize; j++) {
					SetPixel(i + j, red, green, blue);
				}
				SetPixel(i + eyeSize + 1, red/10, green/10, blue/10);
				FastLED.show();
			}
		}
	}

}

void LedStrip::Twinkle(byte red, byte green, byte blue, int count, int speedDelay, boolean onlyOne)
{
	EVERY_N_MILLISECONDS(speedDelay)
	{
		SetAllPixels(0, 0, 0);
		
		for (int i=0; i < count; i++) 
		{
			EVERY_N_MILLISECONDS(speedDelay)
			{
				SetPixel(random(_numberOfLeds), red, green, blue);
				FastLED.show();
			}
			if(onlyOne) {
				SetAllPixels(0,0,0);
			}
		}
	}	
}

void LedStrip::TwinkleRandom(int count, int speedDelay, boolean onlyOne)
{
	EVERY_N_MILLISECONDS(speedDelay)
	{
		SetAllPixels(0, 0, 0);
		
		for (int i = 0; i < count; i++) 
		{
			EVERY_N_MILLISECONDS(speedDelay)
			{
				SetPixel(random(_numberOfLeds), random(0, 255), random(0, 255), random(0, 255));
				FastLED.show();
			}
			if(onlyOne) {
				SetAllPixels(0, 0, 0);
			}
		}
	}	
}

void LedStrip::TripleBounce()
{
	FastLED.clear();
	Bounce(_frame, 0);
	Bounce(_frame + (MAX_INT_VALUE / 3), 100);
	Bounce(_frame + (MAX_INT_VALUE / 3) * 2, 150);
	FastLED.show();
	IncrementFrame();
}

void LedStrip::DoubleChaser()
{
	FastLED.clear();
	_frame = _frame * 2;
	Ring(_frame, 0);
	Ring(_frame + (MAX_INT_VALUE / 2), 150);
	FastLED.show();
	IncrementFrame();
}

void LedStrip::RingPair()
{
	FastLED.clear();
	Ring(_frame, 30);
	Ring(MAX_INT_VALUE - _frame, 150);
	FastLED.show();
	IncrementFrame();
}

void LedStrip::RainbowSpark(uint8_t fade)
{
	EVERY_N_MILLISECONDS(20)
	{
		Spark(_frame, fade, _frame/255);
	}
	FastLED.show();
	IncrementFrame();
}


//Public Helper Methods
void LedStrip::AddGlitter(fract8 chanceOfGlitter)
{
	if (random8() < chanceOfGlitter)
	{
		_leds[random16(_numberOfLeds)] += CRGB::White;
	}
}

void LedStrip::SetPixel(int pixel, byte red, byte green, byte blue)
{
	_leds[pixel].r = red;
	_leds[pixel].g = green;
	_leds[pixel].b = blue;
}

void LedStrip::SetPixel(int pixel, CRGB color)
{
	_leds[pixel] = color;
}

void LedStrip::SetPixel(int pixel, CHSV color)
{
	_leds[pixel] = color;
}

void LedStrip::SetPixel(int pixel, int hue)
{
	_leds[pixel].setHue(hue);
}

void LedStrip::SetAllPixels(byte red, byte green, byte blue)
{
	for (int i = 0; i < _numberOfLeds; i++)
	{
		SetPixel(i, red, green, blue);
	}
}

void LedStrip::SetAllPixels(CHSV color)
{
	fill_solid(_leds, _numberOfLeds, color);
}

void LedStrip::SetAllPixels(CRGB color)
{
	fill_solid(_leds, _numberOfLeds, color);
}

void LedStrip::FadeToBlack(int pixel, byte fadeValue)
{
	_leds[pixel].fadeToBlackBy(fadeValue);
}

void LedStrip::DrawFractionalBar(int pos16, int width, uint8_t hue, bool wrap)
{
	uint8_t i = pos16 / 16; // convert from pos to raw pixel number

	uint8_t frac = pos16 & 0x0F; // extract the 'factional' part of the position
	uint8_t firstpixelbrightness = 255 - (frac * 16);

	uint8_t lastpixelbrightness = 255 - firstpixelbrightness;

	uint8_t bright;

	for (int n = 0; n <= width; n++)
	{
		if (n == 0)
		{
			// first pixel in the bar
			bright = firstpixelbrightness;
		}
		else if (n == width)
		{
			// last pixel in the bar
			bright = lastpixelbrightness;
		}
		else
		{
			// middle pixels
			bright = 255;
		}

		_leds[i] += CHSV(hue, 255, bright);
		i++;

		if (i == _numberOfLeds)
		{
			if (wrap == 1)
			{
				i = 0; // wrap around
			}
			else
			{
				return;
			}
		}
	}
}

void LedStrip::Bounce(uint16_t animationFrame, uint8_t hue)
{
	uint16_t pos16;
	if (animationFrame < (MAX_INT_VALUE / 2))
	{
		pos16 = animationFrame * 2;
	}
	else
	{
		pos16 = MAX_INT_VALUE - ((animationFrame - (MAX_INT_VALUE / 2)) * 2);
	}

	int position = map(pos16, 0, MAX_INT_VALUE, 0, ((_numberOfLeds) * 16));
	DrawFractionalBar(position, 3, hue, 0);
}

void LedStrip::Ring(uint16_t animationFrame, uint8_t hue)
{
	int pos16 = map(animationFrame, 0, MAX_INT_VALUE, 0, (_numberOfLeds * 16));
	DrawFractionalBar(pos16, 3, hue, 1);
}

void LedStrip::Wave(uint16_t animationFrame, uint8_t hue)
{
	FastLED.clear();
	float deg;
	float value;

	for(uint8_t i = 0; i < _numberOfLeds; i++)
	{
		deg = float(animationFrame + ((MAX_INT_VALUE / _numberOfLeds) * i)) / (float(MAX_INT_VALUE)) * 360.0;
		Serial.println(deg);
		value = pow(sin(radians(deg)), 8);
		Serial.println(value);
		//Chop sine wave (no negative values)
		if(value >= 0)
		{
			_leds[i] += CHSV(hue, 255, value * 256);
		}
	}
}

void LedStrip::WaveInt(uint16_t animationFrame, uint8_t hue)
{
	FastLED.clear();
	uint8_t value;

	for(uint8_t i = 0; i < _numberOfLeds; i++)
	{
		value = (sin16(animationFrame + ((MAX_INT_VALUE / _numberOfLeds)*i)) + (MAX_INT_VALUE / 2)) / 256;
		
		if(value >= 0)
		{
			_leds[i] += CHSV(hue, 255, value);
		}
	}
}

void LedStrip::Spark(uint16_t animationFrame, uint8_t fade, uint8_t hue)
{
	uint16_t rand = random16();

	for(int i = 0; i < _numberOfLeds; i++)
	{
		_leds[i].nscale8(fade);
	}


	if(rand < (MAX_INT_VALUE / (256 - (constrain(_animateSpeed, 1, 256)))))
	{
		_leds[rand % _numberOfLeds].setHSV(hue, 255, 255);
	}
}

void LedStrip::Spark(uint16_t animateSpeed,uint8_t fade)
{
	uint16_t rand = random16();

	for(int i = 0; i < _numberOfLeds; i++)
	{
		_leds[i].nscale8(fade);
	}


	if(rand < (MAX_INT_VALUE / (256 - (constrain(_animateSpeed, 1, 255)))))
	{
		_leds[rand % _numberOfLeds].setHSV(0, 0, 255);
	}
}

void LedStrip::Show()
{
	FastLED.show();
}

uint8_t LedStrip::NumberOfLeds()
{
	return _numberOfLeds;
}

//Private Helper Methods
void LedStrip::IncrementFrame()
{
	_frame += _animateSpeed;
}

