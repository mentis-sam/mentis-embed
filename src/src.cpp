// KY-040 ...  ESP32
// CLK    ...  PIN 4
// DT     ...  PIN 2  // upload impossible ->21
// SW     ...  PIN 5
// +      ...  3.3V
// GND    ...  GND
#include <Arduino.h>
#include <SPI.h>


#include "utils/NavManager.h"
#include "utils/MachineState.h"
#include "utils/TempController.h"
#include "utils/IO.h"

#include "modules/TempModule.h"
#include "modules/RTCModule.h"
#include "modules/EncoderModule.h"

volatile int lastTime = 0;
volatile int lastTime2 = 0;

u_long lastIsrAt = 0;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;


void IRAM_ATTR timerISR() {
  	portENTER_CRITICAL_ISR(&timerMux);
	lastIsrAt = millis();
	//timerFlag = 1;
  	portEXIT_CRITICAL_ISR(&timerMux);
	//currentScreen->nextFrame();		
}

void setup(){
		Serial.begin(115200);

		uint8_t errors = 0;
		Serial.printf("/// INITIALISING MODULES ///\n\n");

		errors += TempModule::initialise();
		errors += RTCModule::initialise();
		errors += EncoderModule::initialise();
		errors += Screen::initialise();

		errors += IO::initialise();
		errors += FileManager::initialise();

		errors += MachineState::initialise();
		errors += TempController::initialise();

		

		Nav::gotoScreen(&Nav::menu_colonise);
		Nav::currentScreen->load();

		Serial.printf("/// FINISHED INITIALISING MODULES ///\n");
		Serial.printf("Module Errors: %d\n\n", errors);

		MachineState::startState(dehydration, &Settings::lerpSettings.d_timeperiod);
}



void loop(){
	//EncoderModule::_rotaryEncorderISR();

	// TODO: This could be neater & more responsive with callbacks binding in setup
	if (EncoderModule::selectFlag())
	{
		Nav::currentScreen->onSelect();
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

	if (millis() > lastTime2 + 5000)
	{
		lastTime2 = millis();

		//TODO: Make these happen different rates

		// 5 min
		StateController::update();

		// 5 sec
		TempController::update();
	}
}