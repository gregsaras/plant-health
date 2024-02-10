// Device Firmware: 1.5.0

#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "{{YOUR_SSID}}";
char pword[] = "{{WIFI_PASSWORD}}";
int status = WL_IDLE_STATUS;
WiFiClient client;
int digitalOut[] = { 0, 1 };

void setup() {
  /*Serial setup*/
  Serial.begin(9600);
  while(!Serial) {
    ;
  }

  /*WiFi setup*/
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed");
    while(true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Firmware version out of date");
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pword);

    delay(10000);
  }

  WiFi.lowPowerMode();

  Serial.print("Connected to: ");
  Serial.println(ssid);

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
  
  if (client.connect("{{SERVER_IP}}", {{SERVER_PORT}})) {
     client.print(payload);
     client.stop();
   }

  delay(60000);
}