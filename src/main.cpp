#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include "../include/fingerprint.hpp"

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// Set up the serial port to use softwareserial..
SoftwareSerial mySerial(2, 3);

#else
// // On Leonardo/M0/etc, others with hardware serial, use hardware serial!
// // #0 is green wire, #1 is white
#define mySerial Serial1

#endif

// Using sensor without password
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int8_t id = 1; 
int8_t ledPin = 7;
int16_t fingerID = -1;

void setup() {
  Serial.begin(9600); 

  pinMode(ledPin, OUTPUT);

  // set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
  }

  while (!registerFingerprint(finger, id));
}

void loop() {
  Serial.println("Reading fingerprint to match!");
  fingerID = getFingerprintID(finger);

  // Will light LED if the correct fingerprint match
  if (id == fingerID){
    Serial.println("Fingerprint match!!!");
    digitalWrite(ledPin, HIGH);
    delay(10);
    digitalWrite(ledPin, LOW);
  }
  delay(3);
}
