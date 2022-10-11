
#include <Arduino.h>
#include <WiFiManager.h>


void setup(){
		Serial.begin(115200);

		uint8_t errors = 0;
		Serial.printf("/// INITIALISING MODULES ///\n\n");

		WiFiManager wm;
		bool res;
		res = wm.autoConnect("Mentis Lunchbox");
		
		if(!res) {
        	Serial.println("Failed to connect");
        	// ESP.restart();
		} 
		else {
			//if you get here you have connected to the WiFi    
			Serial.println("connected...yeey :)");
		}

		Serial.printf("/// FINISHED INITIALISING MODULES ///\n");
		Serial.printf("Module Errors: %d\n\n", errors);
}



void loop(){

}