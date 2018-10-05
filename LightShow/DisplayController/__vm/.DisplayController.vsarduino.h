/* 
	Editor: https://www.visualmicro.com/
			visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
			the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
			all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
			note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino/Genuino Uno, Platform=avr, Package=arduino
*/

#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define ARDUINO 10806
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define F_CPU 16000000L
#define ARDUINO 10806
#define ARDUINO_AVR_UNO
#define ARDUINO_ARCH_AVR
//
//
void ReadKey();
void StopScene();
void Scene1();
void Scene2();
void Scene3();
void Scene4();
void Scene5();
void Scene6();
void Scene7();
void Scene8();
void Scene9();
void Scene10();
void Scene11();
void Scene12();
void Scene13();
void Scene14();
void Scene15();
void TransmitPatternToAllLocations(byte patternId);
void TransmitStopToAllLocations();
void TransmitPatternToWonderWheel(byte patternId);
void TransmitPatternToLocation(uint64_t nodeId, byte patternId);
void PrintNodeId(uint64_t nodeId);

#include "pins_arduino.h" 
#include "arduino.h"
#include "DisplayController.ino"
