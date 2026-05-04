#include "Particle.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

const int steeringPin = D13;
const int drivePin = D1;

Servo steeringServo;
Servo driveServo;

String buffer = "";

const int DRIVE_STOP = 90;
const int DRIVE_FORWARD = 115;
const int DRIVE_REVERSE = 65;

const int STEERING_CENTER = 90;
const int STEERING_STEP = 7;

unsigned long lastMessageTime = 0;
const unsigned long timeoutMs = 1000;

int xToSteeringAngle(int x) {
    x = constrain(x, -2, 2);
    return STEERING_CENTER + (x * STEERING_STEP);
}

int yToDriveSpeed(int y) {
    if (y == -1) {
        return DRIVE_REVERSE;
    }

    if (y == 1) {
        return DRIVE_FORWARD;
    }

    return DRIVE_STOP;
}

void stopDrive() {
    driveServo.write(DRIVE_STOP);
}

void parseData(String data) {
    data.trim();

    int commaIndex = data.indexOf(',');

    if (commaIndex == -1) {
        return;
    }

    int xMode = data.substring(0, commaIndex).toInt();
    int yMode = data.substring(commaIndex + 1).toInt();

    int steeringAngle = xToSteeringAngle(xMode);
    int driveSpeed = yToDriveSpeed(yMode);

    steeringServo.write(steeringAngle);
    driveServo.write(driveSpeed);

    lastMessageTime = millis();

    Serial.print("x=");
    Serial.print(xMode);

    Serial.print(" y=");
    Serial.print(yMode);

    Serial.print(" | steer=");
    Serial.print(steeringAngle);

    Serial.print(" | drive=");
    Serial.println(driveSpeed);
}

void setup() {
    Serial.begin(115200);
    Serial1.begin(9600);

    steeringServo.attach(steeringPin);
    driveServo.attach(drivePin);

    steeringServo.write(STEERING_CENTER);
    driveServo.write(DRIVE_STOP);

    Serial.println("Ready");
}

void loop() {
    while (Serial1.available() > 0) {
        char c = Serial1.read();

        if (c == '\n') {
            parseData(buffer);
            buffer = "";
        } 
        else if (c != '\r') {
            buffer += c;
            

            if (buffer.length() > 20) {
                buffer = "";
            }
        }
    }

    if (millis() - lastMessageTime > timeoutMs) {
        stopDrive();
    }
}
