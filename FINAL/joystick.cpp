#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

const int xPin = A0;
const int yPin = A1;
const int buttonPin = D2;

int lastXMode = 999;
int lastYMode = 999;

unsigned long lastSendTime = 0;
const unsigned long sendInterval = 150;
const unsigned long heartbeatInterval = 700;

// Steering: -2 to 2 with small dead zone at center
int xToMode(int value) {
    if (value < 819)  return -2;
    if (value < 1948) return -1;
    if (value < 2148) return  0;
    if (value < 3122) return  1;
    return 2;
}

// Drive: -1, 0, 1 only
int yToMode(int value) {
    if (value < 1500) return -1;
    if (value > 2600) return  1;
    return 0;
}

void setup() {
    Serial.begin(9600);
    pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
    int xMode = xToMode(analogRead(xPin));
    int yMode = yToMode(analogRead(yPin));

    unsigned long now = millis();

    bool changed = (xMode != lastXMode || yMode != lastYMode);
    bool allowedToSend = (now - lastSendTime >= sendInterval);
    bool heartbeat = (now - lastSendTime >= heartbeatInterval);

    if ((changed && allowedToSend) || heartbeat) {
        Serial.printf("%d,%d\n", xMode, yMode);
        lastXMode = xMode;
        lastYMode = yMode;
        lastSendTime = now;
    }
}