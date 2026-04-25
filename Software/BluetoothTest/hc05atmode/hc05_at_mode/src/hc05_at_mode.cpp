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

void setup() {
    pinMode(D2, OUTPUT);
    digitalWrite(D2, HIGH);
    Serial.begin(9600);   // USB baud doesn't matter on Photon 2 (CDC)
    Serial1.begin(38400); // HC-05 AT mode baud
    Serial.println("Ready");
}

void loop() {
    if (Serial1.available()) {
        char c = Serial1.read();
        Serial.print(c);
    }
    if (Serial.available()) {
        char c = Serial.read();
        Serial1.print(c);
    }
}