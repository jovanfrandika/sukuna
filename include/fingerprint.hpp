#ifndef _FINGERPRINT_HPP
#define _FINGERPRINT_HPP

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>

int8_t getImageThenConvertToTemplate(Adafruit_Fingerprint finger, int8_t slot);

int8_t getImageThenConvertToTemplate(Adafruit_Fingerprint finger);

int8_t registerFingerprint(Adafruit_Fingerprint finger, int8_t id);

int8_t getFingerprintID(Adafruit_Fingerprint finger);

void getMessage(int32_t p);

#endif