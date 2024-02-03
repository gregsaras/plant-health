// Device: Arduino Uno WiFi Rev 2
// Device Firmware: 1.5.0

#include <WiFiNINA.h>

char ssid[] = "{{YOUR_SSID}}";
char pword[] = "{{WIFI_PASSWORD}}";
int status = WL_IDLE_STATUS;
WiFiClient client;

void setup() {
  Serial.begin(9600);
  while(!Serial) {
    ;
  }

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

  Serial.print("Connected to: ");
  Serial.println(ssid);
}

void loop() {
  String payload = "";
  for(int i = 0; i < 6; i++){
    payload = payload + analogRead(i);
    if (i != 5){
      payload = payload + ",";
    }
  }

  // print data out to serial, easier debugging
  Serial.println(payload);

  // Send data to server listening for messaging
  if (client.connect("{{SERVER_IP}}", {{SERVER_PORT}})) {
     client.print(payload);
     client.stop();
   }

  delay(5000);
}