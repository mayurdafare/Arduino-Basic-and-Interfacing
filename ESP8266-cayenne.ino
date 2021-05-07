// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

#define CAYENNE_DEBUG
//#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

#include<DHT.h>

// WiFi network info.
char ssid[] = "Nokia 6";
char wifiPassword[] = "mayur@123";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "9f67e470-11bc-11e8-a2eb-7d0b45aada7b";
char password[] = "2fe69e0a6c885a2da6b717f049fd0351ca2ca5c7";
char clientID[] = "a177ffc0-11bc-11e8-9f2a-b3b29283a596";

DHT dht(D2, DHT11);

void setup() {
	Serial.begin(9600);
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
pinMode(D4,OUTPUT);
digitalWrite(D4,HIGH);
pinMode(D0,OUTPUT);
digitalWrite(D0,HIGH);

}

void loop() {
	Cayenne.loop();
 float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  Cayenne.virtualWrite(1,temp,TYPE_TEMPERATURE, UNIT_CELSIUS);
  Cayenne.virtualWrite(2,hum,TYPE_RELATIVE_HUMIDITY, UNIT_PERCENT);
  
//*********************************************************************************************************************************************************//
   Serial.print(temp);
   Serial.print(hum);
  
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_IN(0)
{

  digitalWrite(D4, !getValue.asInt());
  
  
}
CAYENNE_IN(3)
{

  digitalWrite(D0, !getValue.asInt());
}
