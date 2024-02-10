// Device Firmware: 1.5.0

int digitalOut[] = { 0, 1 };

void setup() {
  /*Serial setup*/
  Serial.begin(9600);
  while(!Serial) {
    ;
  }

  /*Pin setup*/
  for(int i = 0; i < 2; i++){
    pinMode(digitalOut[i], OUTPUT);
  }
}

void loop() {
  String payload = "";
  for(int i = 0; i < 2; i++){
    digitalWrite(i, HIGH);
    delay(50);
    payload = payload + analogRead(i);
    if (i != 1){
      payload = payload + ",";
    }
    digitalWrite(i, LOW);
  }

  Serial.println(payload);

  delay(60000);
}
