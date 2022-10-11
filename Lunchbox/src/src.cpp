
#include <Arduino.h>
#include <WiFiManager.h>
#include <ota.h>

// DO NOT CHANGE WITHOUT THINKING
String host = "mentis-ota-lunchbox.s3.eu-west-2.amazonaws.com"; 
String bin = "/lunchbox-release.bin"; 
// DO NOT CHANGE WITHOUT THINKING

void setup(){
		Serial.begin(115200);

		uint8_t errors = 0;
		Serial.printf("/// INITIALISING MODULES ///\n\n");


		Serial.printf("/// FINISHED INITIALISING MODULES ///\n");
		Serial.printf("Module Errors: %d\n\n", errors);

		Serial.printf("/// INITIALISING WIFI ///\n\n");

		WiFiManager wm;
		bool res;
		res = wm.autoConnect("Mentis Lunchbox");
		
		if(!res) {
        	Serial.println("Failed to connect");
        	ESP.restart();
		} 
		else {
			//if you get here you have connected to the WiFi    
			Serial.println("Connected to WiFi");
		}

		Serial.printf("/// FINISHED INITIALISING WIFI ///\n");

		// Execute OTA Update
  		execOTA(host, bin);
}



void loop(){
	sleep(1);
	Serial.print("Version: 1\n");
}