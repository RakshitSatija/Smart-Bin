#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#include <WiFiClient.h> 
#include <WiFiServer.h>

#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

int sensorPin = A0;     
int sensorValue = 0; 
int Trig = D1;
int Echo = D0;
int distance =0;
String myString;
String myString2;

#define FIREBASE_HOST "hackcbs-fire.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "fFrJEXCGKHZnFx1NLccxOeGjWtOfEHYBGjt8GfuZ"            // the secret key generated from firebase

#define WIFI_SSID "Connected"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "dell12345"                                    //password of wifi ssid

void setup() {
  Serial.begin(9600);  
  delay(1000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);                         }
    
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase


  pinMode(sensorPin, INPUT);
  pinMode(Trig, INPUT);
  pinMode(Echo, OUTPUT);
  
}

void loop() {

  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  delay(2000);
  long duration;

digitalWrite(Trig, LOW);
delayMicroseconds(2);
digitalWrite(Trig, HIGH);
delayMicroseconds(10);
digitalWrite(Trig, LOW);
duration = pulseIn(Echo, HIGH);
distance = (duration/2) / 29.1 ;
Serial.println(distance);
Serial.println("cm");
myString = String(distance);
myString2 = String(sensorValue);
 Firebase.pushString("Presssure", myString2);                                  //setup path and send readings
 Firebase.pushString("Distance", myString);                                //setup path and send readings

}
