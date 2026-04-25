/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

int xPin = A0;
int yPin = A1;
int buttonPin = D2;

void setup() {
    Serial.begin(9600);
    pinMode(buttonPin, INPUT_PULLUP); // button is usually active LOW
}


void loop() {
    double xValue = analogRead(xPin);
    double yValue = analogRead(yPin);
    double xRatio = xValue / 4095, yRatio = yValue / 4095;
    double xMotor = xRatio * 180, yMotor = yRatio * 180;


  /*Serial.print(xMotor);
  Serial.print(" | Y: ");
  Serial.print(yMotor);
  Serial.print(" | Button: ");
  Serial.println(buttonState);*/

    Serial.printf("%f,%f\n", xMotor, yMotor);
    delay(20);
}