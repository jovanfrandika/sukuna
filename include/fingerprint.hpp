#ifndef _FINGERPRINT_HPP
#define _FINGERPRINT_HPP

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>

int8_t getImageThenConvertToTemplate(Adafruit_Fingerprint finger, uint8_t slot = 1);

int8_t registerFingerprint(Adafruit_Fingerprint finger, uint8_t id);

int8_t getFingerprintID(Adafruit_Fingerprint finger);

void getMessage(uint8_t p);

#endif