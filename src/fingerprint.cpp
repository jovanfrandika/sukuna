#include "../include/fingerprint.hpp"

/**************************************************************************/
/*!
    @brief  Get the fingerprint image then turn it into a template
    @param  finger Fingerprint instance  
    @param  slot Location to place feature template 
    (put one in 1 and another in 2 for verification to create model)
*/
/**************************************************************************/
int8_t getImageThenConvertToTemplate(Adafruit_Fingerprint finger, uint8_t slot) {
  int16_t p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    getMessage(p);
  }

  p = finger.image2Tz(slot);
  getMessage(p);
  if (p != FINGERPRINT_OK) return -1;
  return 1;
}

/**************************************************************************/
/*!
    @brief  Register the fingerprint to an ID
    @param  finger Fingerprint instance  
    @param  id  Destinated ID
*/
/**************************************************************************/
int8_t registerFingerprint(Adafruit_Fingerprint finger, uint8_t id) {
  uint8_t initial = 1;
  uint8_t verification = 2;
  
  Serial.print("Registering ID: ");
  Serial.println(id);
  Serial.println("Place same finger!"); 
  if (!getImageThenConvertToTemplate(finger, initial))
    return -1;
  
  Serial.println("Remove finger!!");
  delay(2);
  
  int8_t p = 0;   

  Serial.println("Place same finger again!!"); 
  if (!getImageThenConvertToTemplate(finger, verification))
    return -1;

  Serial.println("Creating Model"); 
  p = finger.createModel();
  getMessage(p);

  Serial.println("Storing Model"); 
  p = finger.storeModel(id);
  getMessage(p);

  return 1; 
}

/**************************************************************************/
/*!
    @brief  Get fingerprint ID from sensor
    @param  finger Fingerprint instance 
*/
/**************************************************************************/
int8_t getFingerprintID(Adafruit_Fingerprint finger) {
  uint8_t p;
  if (!getImageThenConvertToTemplate(finger))
    return -1;

  p = finger.fingerSearch();
  getMessage(p);

  if (p != FINGERPRINT_OK) 
    return -1;

  return finger.fingerID;
}

/**************************************************************************/
/*!
    @brief  Log the sensor's reading
    @param  p Sensor reading result
*/
/**************************************************************************/
void getMessage(uint8_t p) {
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Fingerprint have been read");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No fingers");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      break;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      break;
    case FINGERPRINT_ENROLLMISMATCH:
      Serial.println("Fingerprints did not match");
      break;
    case FINGERPRINT_BADLOCATION:
      Serial.println("Could not store in that location");
      break;
    case FINGERPRINT_FLASHERR:
      Serial.println("Error writing to flash");
      break;
    default:
      Serial.println("Unknown error");
      break;
  }
}