#include <Arduino.h>

// This is just a dummy so that platformio is quiet ;)

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Dummy");
  delay(1000);
}
