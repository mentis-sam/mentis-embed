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
volatile int lastTime3 = 0;

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


		// WARNING: THE ORDER OF THESE IS ANNOYINGLY IMPORTANT
		errors += TempModule::initialise();
		errors += RTCModule::initialise();
		errors += EncoderModule::initialise();
		errors += Screen::initialise();

		errors += IO::initialise();
		errors += FileManager::initialise();

		errors += TempController::initialise();
		errors += MachineState::initialise();
		

		Serial.printf("/// FINISHED INITIALISING MODULES ///\n");
		Serial.printf("Module Errors: %d\n\n", errors);
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
	if (millis() > lastTime + 120)
	{
		lastTime = millis();
		Nav::currentScreen->nextFrame();
	}

	// 5s
	if (millis() > lastTime2 + 5000)
	{
		lastTime2 = millis();
		TempController::update();
	}
	// 5min
	if (millis() > lastTime3 + 5000)
	{
		lastTime3 = millis();
		StateController::update();
	}
}