#include <SoftwareSerial.h>
#include <MeMegaPi.h>

MeBluetooth bluetoothSerial(9);

void setup() {
  Serial.begin(9600);         // Initialize Serial Monitor
  bluetoothSerial.begin(9600);  // Initialize Bluetooth module
}

void loop() {
  if (bluetoothSerial.available()) {
    char receivedChar = bluetoothSerial.read();
    Serial.print("Received: ");
    Serial.println(receivedChar);
  }

  if (Serial.available()) {
    char sendChar = Serial.read();
    Serial.print("Sending: ");
    Serial.println(sendChar);
    bluetoothSerial.print(sendChar);
  }
}
