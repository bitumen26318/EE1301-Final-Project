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

// setup() runs once, when the device is first turned on
void setup() {
    Serial.begin(9600);      // USB serial (for debugging)
    Serial1.begin(9600);     // HC-06 default baud rate
}

void loop() {
    // Send data to Bluetooth
    Serial1.println("Hello from Photon P2!");

    // Read from Bluetooth and print to Serial Monitor
    if (Serial1.available()) {
        char c = Serial1.read();
        Serial.print(c);
    }

    delay(1000);
}