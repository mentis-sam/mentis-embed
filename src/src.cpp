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
#include "module/EncoderModule.h"

volatile int lastTime = 0;

u_long lastIsrAt = 0;

volatile int8_t g_rotValue = 0;

TFT_eSPI tft = TFT_eSPI();


hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void initializeScreens(void)
{
	Nav::gotoScreen(&Nav::menu_colonise);
	Nav::currentScreen->load();
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

		uint8_t module_errors = 0;
		Serial.printf("/// INITIALISING MODULES ///\n\n");

		module_errors += TempModule::initialise();
		module_errors += RTCModule::initialise();

		// TODO: Add debugging
		module_errors += EncoderModule::initialise();

		initializeScreens();

		tft.init();
		tft.setRotation(1);
		tft.fillScreen(TFT_BLACK);

		
		
		Serial.printf("/// FINISHED INITIALISING MODULES ///\n");
		Serial.printf("Module Errors: %d\n\n", module_errors);
		//timer = timerBegin(0, 240, true);
		//timerAttachInterrupt(timer, &timerISR, true);
		//timerAlarmWrite(timer, 2000000, true);
		//timerAlarmEnable(timer);

}



void loop(){
	//EncoderModule::_rotaryEncorderISR();

	// TODO: This could be neater & more responsive with callbacks binding in setup
	if (EncoderModule::selectFlag())
	{
		Nav::currentScreen->onClick();
	}
	if (EncoderModule::leftFlag())
	{
		Nav::currentScreen->onLeft();
	}
	if (EncoderModule::rightFlag()){
		Nav::currentScreen->onRight();
	}

	// Only load the screen if all navigation is complete
	if (EncoderModule::getRotation() == 0){
		Nav::currentScreen->load();
	}

	// Render next frame of animation
	if (millis() > lastTime + 100)
	{
		lastTime = millis();
		Nav::currentScreen->nextFrame();
	}

		//DateTime now = RTCModule::getTime();
		//Serial.printf("Time: %d/%d/%dT%d:%d::%d\n", now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second());
		//Serial.println(TempModule::getTempC());

		/*
		tempScreen.temperature = random(200, 250) / 10.0;

		if (IS_CURRENT_SCREEN(tempScreen))
			tempScreen.rerender();
		*/
}