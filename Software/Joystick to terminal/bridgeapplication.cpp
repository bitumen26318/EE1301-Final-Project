#include <windows.h>
#include <iostream>

HANDLE openPort(const char* portName, DWORD baudRate) {
HANDLE hSerial = CreateFileA(
portName,
GENERIC_READ | GENERIC_WRITE,
0,
NULL,
OPEN_EXISTING,
FILE_ATTRIBUTE_NORMAL,
NULL
);

if (hSerial == INVALID_HANDLE_VALUE) {
std::cerr << "Failed to open " << portName << std::endl;
return INVALID_HANDLE_VALUE;
}

DCB dcb = {0};
dcb.DCBlength = sizeof(dcb);

GetCommState(hSerial, &dcb);
dcb.BaudRate = baudRate;
dcb.ByteSize = 8;
dcb.StopBits = ONESTOPBIT;
dcb.Parity = NOPARITY;

SetCommState(hSerial, &dcb);

COMMTIMEOUTS timeouts = {0};
timeouts.ReadIntervalTimeout = 1;
timeouts.ReadTotalTimeoutConstant = 1;
timeouts.ReadTotalTimeoutMultiplier = 1;

SetCommTimeouts(hSerial, &timeouts);

return hSerial;
}

void forward(HANDLE from, HANDLE to) {
char buffer[256];
DWORD bytesRead;
DWORD bytesWritten;

if (ReadFile(from, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
WriteFile(to, buffer, bytesRead, &bytesWritten, NULL);
}
}

int main() {
HANDLE photonUSB = openPort("\\\\.\\COM7", 9600); // joystick Photon
HANDLE bluetooth = openPort("\\\\.\\COM4", 9600); // HC-06

if (photonUSB == INVALID_HANDLE_VALUE || bluetooth == INVALID_HANDLE_VALUE) {
return 1;
}

while (true) {
forward(photonUSB, bluetooth); // USB → Bluetooth
forward(bluetooth, photonUSB); // Bluetooth → USB, optional
Sleep(1);
}

CloseHandle(photonUSB);
CloseHandle(bluetooth);
return 0;
}