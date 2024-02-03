// Device: Arduino Uno WiFi Rev 2
// Device Firmware: 1.5.0

void setup() {
  Serial.begin(9600);
}

void loop() {
  String payload = "";
  for(int i = 0; i < 6; i++){
    payload = payload + analogRead(i);
    if (i != 5){
      payload = payload + ",";
    }
  }

  Serial.println(payload);

  delay(500);
}
