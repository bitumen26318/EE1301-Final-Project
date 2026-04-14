/*
 * Photon 2 / P2 Continuous Servo Max Speed Test
 * D1 = servo signal
 * D2 = button
 *
 * Mode 0: STOP
 * Mode 1: MAX CW
 * Mode 2: MAX CCW
 */

#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

Servo myServo;

const int servoPin = D1;
const int buttonPin = D2;

int mode = 0;


const int neutral = 90;  
const int maxCW   = 180;  
const int maxCCW  = 0;    

bool lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 250;

void applyMode() {
    if (mode == 0) {
        myServo.write(neutral);
        Serial.println("Mode 0: STOP");
    }
    else if (mode == 1) {
        myServo.write(maxCW);
        Serial.println("Mode 1: MAX CW");
    }
    else if (mode == 2) {
        myServo.write(maxCCW);
        Serial.println("Mode 2: MAX CCW");
    }
}

void setup() {
    Serial.begin(9600);

    pinMode(buttonPin, INPUT_PULLDOWN);
    myServo.attach(servoPin);

    delay(1000);
    applyMode();

    Serial.println("System ready");
    Serial.println("Press button to change mode: 0 -> 1 -> 2 -> 0");
}

void loop() {
    bool buttonState = digitalRead(buttonPin);

    // detect button press: LOW -> HIGH
    if (buttonState == HIGH && lastButtonState == LOW) {
        if (millis() - lastDebounceTime > debounceDelay) {
            mode++;
            if (mode > 2) {
                mode = 0;
            }

            Serial.print("Button pressed | New mode = ");
            Serial.println(mode);

            applyMode();
            lastDebounceTime = millis();
        }
    }

    lastButtonState = buttonState;
}