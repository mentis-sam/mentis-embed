// KY-040 ...  ESP32
// CLK    ...  PIN 4
// DT     ...  PIN 2  // upload impossible ->21
// SW     ...  PIN 5
// +      ...  3.3V
// GND    ...  GND
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "utils/NavManager.h"

#include "module/TempModule.h"
#include "module/RTCModule.h"

#define ROTARY_PINA 26 //2 DT
#define ROTARY_PINB 27 //4 CLK
#define ROTARY_PINSW 25

volatile int rotationFlag = 0;
volatile int switchFlag = 0;
volatile int lastTime = 0;

u_long lastIsrAt = 0;

volatile int8_t g_rotValue = 0;

TFT_eSPI tft = TFT_eSPI();

portMUX_TYPE gpioMux = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

hw_timer_t * timer = NULL;

void IRAM_ATTR rotaryEncorderISR() 
{
    static int8_t ROT_ENC_TABLE[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};
    static uint8_t prevNextCode = 0;
    static uint16_t store = 0;

    prevNextCode <<= 2;
    if (digitalRead(ROTARY_PINA)) prevNextCode |= 0x02;
    if (digitalRead(ROTARY_PINB)) prevNextCode |= 0x01;
    prevNextCode &= 0x0f;

	portENTER_CRITICAL_ISR(&gpioMux);
    if  (ROT_ENC_TABLE[prevNextCode]) {
        store <<= 4;
        store |= prevNextCode;
        if ((store & 0xff) == 0x2b)
		{
			g_rotValue -= 1;
			rotationFlag = 1;
		}
        else if ((store & 0xff) == 0x17)
        {
			g_rotValue += 1;
			rotationFlag = 1;
		}
    }
    portEXIT_CRITICAL_ISR(&gpioMux);
}

void IRAM_ATTR rotarySwitchISR() {
	static long lastSwicthTrigger = 0;
	long t = millis();

	if (t - lastSwicthTrigger < 150)
		return;
	lastSwicthTrigger = t;

 portENTER_CRITICAL_ISR(&gpioMux);
 switchFlag = 1;
 portEXIT_CRITICAL_ISR(&gpioMux);

}

void initializeScreens(void)
{
	Nav::gotoScreen(&Nav::menu_colonise);
	Nav::currentScreen->render();
}

void IRAM_ATTR timerISR() {
  	portENTER_CRITICAL_ISR(&timerMux);
	lastIsrAt = millis();
	//timerFlag = 1;
  	portEXIT_CRITICAL_ISR(&timerMux);
	//currentScreen->nextFrame();		
}

void setup(){
		Serial.begin(115200);

		int module_errors = 0;
		Serial.printf("/// INITIALISING MODULES ///\n\n");

		module_errors += TempModule::initialise(32);
		module_errors += RTCModule::initialise();

		initializeScreens();

		pinMode(ROTARY_PINA, INPUT_PULLUP);
		pinMode(ROTARY_PINB, INPUT_PULLUP);
		pinMode(ROTARY_PINSW, INPUT_PULLUP);

		attachInterrupt(ROTARY_PINA, rotaryEncorderISR, CHANGE);
		attachInterrupt(ROTARY_PINB, rotaryEncorderISR, CHANGE);
		attachInterrupt(ROTARY_PINSW, rotarySwitchISR, RISING);

		tft.init();
		tft.setRotation(1);
		tft.fillScreen(TFT_BLACK);
		
		Serial.printf("\n/// FINISHED INITIALISING MODULES ///\n");
		Serial.printf("Module Errors: %d\n\n", module_errors);
		//timer = timerBegin(0, 240, true);
		//timerAttachInterrupt(timer, &timerISR, true);
		//timerAlarmWrite(timer, 2000000, true);
		//timerAlarmEnable(timer);

}

void loop(){
	if (switchFlag)
	{
		switchFlag = 0;
		Nav::currentScreen->onClick();
	}
	if (rotationFlag)
	{
		rotationFlag = 0;
		Nav::currentScreen->onRotation();
	}
	if (millis() > lastTime + 1000)
	{
		lastTime = millis();
		Nav::currentScreen->nextFrame();
		DateTime now = RTCModule::getTime();
		Serial.printf("Time: %d/%d/%dT%d:%d::%d\n", now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second());
		//Serial.println(TempModule::getTempC());

		/*
		tempScreen.temperature = random(200, 250) / 10.0;

		if (IS_CURRENT_SCREEN(tempScreen))
			tempScreen.rerender();
		*/
	}
}