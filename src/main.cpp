#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>

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

uint8_t getImageThenConvertToTemplate(uint8_t slot);
uint8_t getImageThenConvertToTemplate();
uint8_t registerFingerprint(uint8_t id);
uint8_t getFingerprintID();
void getMessage(uint32_t p);

// Using sensor without password
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id = 1; 
uint8_t ledPin = 7;
uint8_t fingerID = -1;

void setup() {
  // while (!Serial);  // For Yun/Leo/Micro/Zero/...
  Serial.begin(9600); 

  pinMode(ledPin, OUTPUT);

  // set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
  }

  while (!registerFingerprint(id));
}

void loop() {
  Serial.println("Reading fingerprint to match!");
  fingerID = getFingerprintID();

  if (id == fingerID){
    Serial.println("Fingerprint match!!!");
    digitalWrite(ledPin, HIGH);
    delay(10);
    digitalWrite(ledPin, LOW);
  }
  delay(3);
}

uint8_t getImageThenConvertToTemplate(uint8_t slot) {
  uint8_t p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    getMessage(p);
  }

  p = finger.image2Tz(slot);
  getMessage(p);
  if (p != FINGERPRINT_OK) return -1;
  return 1;
}

uint8_t getImageThenConvertToTemplate() {
  uint8_t p = -1;

  // while (p != FINGERPRINT_OK) {
  p = finger.getImage();
  getMessage(p);

  if (p != FINGERPRINT_OK) 
    return -1;

  p = finger.image2Tz();
  getMessage(p);

  if (p != FINGERPRINT_OK) 
    return -1;

  return 1;
}

uint8_t registerFingerprint(uint8_t id) {
  uint8_t initial = 1;
  uint8_t verification = 2;
  
  Serial.print("Registering ID: ");
  Serial.println(id);
  Serial.println("Place same finger!"); 
  if (!getImageThenConvertToTemplate(initial))
    return -1;
  
  Serial.println("Remove finger!!");
  delay(2);
  
  uint8_t p = 0;   
  // while (p != FINGERPRINT_NOFINGER)
  //   p = finger.getImage();

  Serial.println("Place same finger again!!"); 
  if (!getImageThenConvertToTemplate(verification))
    return -1;

  Serial.println("Creating Model"); 
  p = finger.createModel();
  getMessage(p);

  Serial.println("Storing Model"); 
  p = finger.storeModel(id);
  getMessage(p);

  return 1; 
}

uint8_t getFingerprintID() {
  uint8_t p;
  if (!getImageThenConvertToTemplate())
    return -1;

  p = finger.fingerSearch();
  getMessage(p);

  if (p != FINGERPRINT_OK) 
    return -1;

  return finger.fingerID;
}

void getMessage(uint32_t p) {
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