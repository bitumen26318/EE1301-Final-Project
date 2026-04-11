/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

Servo myServo;

int servoPin = D1;
int buttonPin = D2;

int mode = 0;

bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 250;

int angle = 90;

void setup() {
    Serial.begin(9600);

    myServo.attach(servoPin);
    pinMode(buttonPin, INPUT_PULLDOWN);

    myServo.write(90);

    Serial.println("System ready. Mode = 0");
}

void loop() {

    bool buttonState = digitalRead(buttonPin);

    // Detect PRESS (HIGH → LOW)
    if (buttonState == LOW && lastButtonState == HIGH) {

        if (millis() - lastDebounceTime > debounceDelay) {

            mode++;
            if (mode > 2) mode = 0;

            Serial.print(">>> BUTTON PRESSED | NEW MODE = ");
            Serial.println(mode);

            lastDebounceTime = millis();
        }
    }

    lastButtonState = buttonState;

    // ---------------- MODE LOGIC ----------------

if (mode == 0) {
    myServo.write(90);  // stop (neutral)
    Serial.println("Mode 0: STOP");
    delay(200);
}

else if (mode == 1) {
    // clockwise continuous motion (simulated)
    angle++;

    myServo.write(angle);

    Serial.print("Mode 1: CW | angle = ");
    Serial.println(angle);

    delay(15);
}

else if (mode == 2) {
    // anticlockwise continuous motion (simulated)
    angle--;

    myServo.write(angle);

    Serial.print("Mode 2: CCW | angle = ");
    Serial.println(angle);

    delay(15);
}
}