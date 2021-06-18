# FPM10A Sensor 

**FPM10A Sensor** is small project where user can store one's fingerprint and verify it as the program runs.

## How to run

Prequesites:
- Install platformio

Before running the command below, it is recommended to check platformio.ini file and add your own env.

Run this to install dependencies
```bash
pio lib install
```
If the environment is Arduino Uno.

Build files
```bash
pio run -e uno 
```

Upload to board 
```bash
pio run -e uno -t upload 
```

If its esp32.

Build files
```bash
pio run -e esp 
```

Upload to board 
```bash
pio run -e esp -t upload 
```

If you don't find the environment that you use, I strongly suggest to check [Platformio](https://platformio.org/) to look for your preferred boards and frameworks.

### Technologies & Stacks
- [Arduino](https://www.arduino.cc/)
- [Adafruit Fingerprint](https://learn.adafruit.com/adafruit-optical-fingerprint-sensor)
- [SoftwareSerial](https://www.arduino.cc/en/Reference/softwareSerial)

### Inspiration
SPYxFAMILY manga inspires us to make this fun little project.

### What it does
The device will record one person's finger and continue verify every finger that hit the sensor. If the finger matches the registered finger then it will light up the LED.

### How we built it
The project mostly relies on the adafruit fingerprint library and arduino built-in class. 

### What's next for Keycodes
- Implementing multiple users support for fingerprint sensor 

### Contributors
- [Jovan Frandika](https://github.com/uriella)
- [Lukas Linardi](https://www.instagram.com/lukas.linardi/)
- [Nicholas Permana](https://www.instagram.com/nnicholasp/)
