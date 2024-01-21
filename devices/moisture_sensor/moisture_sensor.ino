// Device: Arduino Uno WiFi Rev 2
// Device Firmware: 1.5.0

int moistureSensorInput = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float moistureSensorValue = analogRead(moistureSensorInput);
  Serial.println(moistureSensorValue);

  delay(500);
}
