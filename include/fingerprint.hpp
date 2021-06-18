#ifndef _FINGERPRINT_HPP
#define _FINGERPRINT_HPP

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>

uint8_t getImageThenConvertToTemplate(Adafruit_Fingerprint finger, uint8_t slot);

uint8_t getImageThenConvertToTemplate(Adafruit_Fingerprint finger);

uint8_t registerFingerprint(Adafruit_Fingerprint finger, uint8_t id);

uint8_t getFingerprintID(Adafruit_Fingerprint finger);

void getMessage(uint32_t p);

#endif