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
unsigned long lastReceiveTime = 0;
const unsigned long timeoutMs = 200;
int angle = 90;
char lastButton = '\0', lastCommand = 'x';


void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    myServo.attach(servoPin);

    myServo.write(90); // stop
}

void loop() {
    if (Serial1.available() > 0) {
        char c2 = Serial1.read();

        Serial.print("Received: ");
        Serial.println(c2);

        if (c2 == 'w' || c2 == 's' || c2 == 'x') {
            lastCommand = c2;
            lastReceiveTime = millis();
        }
    }
    if (millis() - lastReceiveTime > timeoutMs){
        Serial.print("Doesn't work");
        lastCommand = 'x';
    }

    // Apply the most recent command
    if (lastCommand == 'w') {
        myServo.write(180);   // forward
    }
    else if (lastCommand == 's') {
        myServo.write(0);     // backward
    }
    else {
        myServo.write(90);    // stop
    }

    delay(20);
}