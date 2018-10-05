/*
* LedStrip.h
*
* Created: 9/27/2018 12:34:28 PM
* Author: jason.higinbotham
*/
#ifndef __LEDSTRIP_H__
#define __LEDSTRIP_H__

#include "Arduino.h"
#define FASTLED_INTERRUPT_RETRY_COUNT 1
#define FASTLED_ALLOW_INTERRUPTS 0
#include "FastLED.h"

class LedStrip
{
	public:
	LedStrip(uint8_t numberOfLeds, uint8_t ledPin);
	~LedStrip();

	void ColorWaves(CRGBPalette16& palette);
	void Rainbow();
	void RainbowWithGlitter();
	void RainbowWithGlitter(uint8_t hue, byte changeInHue);
	void Confetti();
	void Juggle();
	void Fill(byte red, byte green, byte blue);
	void Fill(CHSV color);
	void Fill(CRGB color);
	void Off();
	void ShowPalette(CRGBPalette16 pal);
	void Strobe(byte red, byte green, byte blue, int flashDelay, int strobeCount);
	void Strobe(byte red, byte green, byte blue, int flashDelay);
	void CylonBounce(byte red, byte green, byte blue, int eyeSize, int speedDelay, int returnDelay);
	void RGBLoop();
	void RunningLights(byte red, byte green, byte blue, int waveDelay);
	void FadeInOut(byte red, byte green, byte blue);
	void ColorWipe(byte red, byte green, byte blue, int speedDelay);
	void TheaterChase(byte red, byte green, byte blue, int speedDelay);
	void MeteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int speedDelay);
	void Bounce(uint8_t hue);
	void Ring(uint8_t hue);
	void Wave(uint8_t hue);
	void WaveInt(uint8_t hue);
	void Spark(uint8_t fade, uint8_t hue);
	void Spark(uint8_t fade);
	void TripleBounce();
	void DoubleChaser();
	void RingPair();
	void RainbowSpark(uint8_t fade);
	void Twinkle(byte red, byte green, byte blue, int count, int speedDelay, boolean onlyOne);
	void TwinkleRandom(int count, int speedDelay, boolean onlyOne);

	void AddGlitter(fract8 chanceOfGlitter);
	void SetPixel(int pixel, byte red, byte green, byte blue);
	void SetPixel(int pixel, CRGB color);
	void SetPixel(int pixel, CHSV color);
	void SetPixel(int pixel, int hue);
	void SetAllPixels(byte red, byte green, byte blue);
	void SetAllPixels(CHSV color);
	void SetAllPixels(CRGB color);
	void FadeToBlack(int pixel, byte fadeValue);
	void DrawFractionalBar(int pos16, int width, uint8_t hue, bool wrap);
	void Bounce(uint16_t animationFrame, uint8_t hue);
	void Ring(uint16_t animationFrame, uint8_t hue);
	void Wave(uint16_t animationFrame, uint8_t hue);
	void WaveInt(uint16_t animationFrame, uint8_t hue);
	void Spark(uint16_t animationFrame, uint8_t fade, uint8_t hue);
	void Spark(uint16_t animateSpeed, uint8_t fade);
	void CenterToOutside(byte red, byte green, byte blue, int eyeSize, int speedDelay, int returnDelay);
	void OutsideToCenter(byte red, byte green, byte blue, int eyeSize, int speedDelay, int returnDelay);
	void LeftToRight(byte red, byte green, byte blue, int eyeSize, int speedDelay, int returnDelay);
	void RightToLeft(byte red, byte green, byte blue, int eyeSize, int speedDelay, int returnDelay);
	void Show();

	uint8_t NumberOfLeds();

	private:
	uint8_t _numberOfLeds;
	CRGB *_leds = NULL;
	uint8_t _gHue = 0;
	uint16_t _frame = 0;
	uint16_t _animateSpeed = 100;

	void IncrementFrame();
};
#endif
