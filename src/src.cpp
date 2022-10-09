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
#include "utils/Notify.h"

#include "modules/TempModule.h"
#include "modules/RTCModule.h"
#include "modules/EncoderModule.h"

volatile int lastTime = 0;
volatile int lastTime2 = 0;
volatile int lastTime3 = 0;

volatile int lastInput = 0;

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

		digitalWrite(BL_PIN, HIGH);
		

		Serial.printf("/// FINISHED INITIALISING MODULES ///\n");
		Serial.printf("Module Errors: %d\n\n", errors);
		lastInput = millis();
}



void loop(){
	//EncoderModule::_rotaryEncorderISR();

	//Screen sleeping after 3 min
	if (millis() > lastInput + 60*3000)
	{
		Notify::sleep = true;
	}else{
		Notify::sleep = false;
	}

	// TODO: This could be neater & more responsive with callbacks binding in setup
	if (EncoderModule::selectFlag())
	{
		lastInput = millis();
		if (Notify::sleep == false){Nav::currentScreen->onSelect();}
		Notify::clear_notification();
	}
	if (EncoderModule::leftFlag())
	{
		lastInput = millis();
		if (Notify::sleep == false){Nav::currentScreen->onLeft();}
		Notify::clear_notification();
	}
	if (EncoderModule::rightFlag())
	{
		lastInput = millis();
		if (Notify::sleep == false){Nav::currentScreen->onRight();}
		Notify::clear_notification();
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
		Notify::update();
	}

	// 5s
	if (millis() > lastTime2 + 5000)
	{
		lastTime2 = millis();
		TempController::update();
	}
	// 5min
	if (millis() > lastTime3 + 60*5000)
	{
		lastTime3 = millis();
		StateController::update();
	}
}