#include <SPI.h>
#include <WiFiNINA.h>

/* communication to server */
char TCP_SERVER[] = "{{TCP_IP}}";
int TCP_PORT = {{TCP_PORT}};

/* WiFi connection */
char SSID[] = "{{SSID}}";
char SSID_PASS[] = "{{WIFI_PASSWORD}}";
int status = WL_IDLE_STATUS;
bool HAS_WIFI_MODULE = false;
WiFiClient client;

/* Setup pins to read */
int digitalOut[] = { 0, 1 };

void setup() {
  /* Serial setup */  
  Serial.begin(9600);

  /* WiFi setup */
  HAS_WIFI_MODULE = WiFi.status() != WL_NO_MODULE;
  if (HAS_WIFI_MODULE) {
    while (status != WL_CONNECTED) {
      Serial.print("Attempting to connect to WPA SSID: ");
      Serial.println(SSID);

      status = WiFi.begin(SSID, SSID_PASS);

      delay(10000);
    }

    WiFi.lowPowerMode();    

    Serial.print("Connected to: ");
    Serial.println(SSID);
  } else {
     Serial.println("No WiFi module detected, communicating over serial only");
  }

  /* Set pins to output to toggle high/low for reads */
  for(int i = 0; i < 2; i++){
    pinMode(digitalOut[i], OUTPUT);
  }
}

void loop() {
  String payload = "";
  for(int i = 0; i < 2; i++){
    /* Set pin as high to power the sensors */
    digitalWrite(i, HIGH);
    delay(50);
    payload = payload + analogRead(i);
    if (i != 1){
      payload = payload + ",";
    }

    /* Set pin as low to power off the sensors */
    digitalWrite(i, LOW);
  }

  /* Print payload to serial */
  Serial.println(payload);

  /* If wifi, send payload to server */
  if(HAS_WIFI_MODULE) {
    if (client.connect(TCP_SERVER, TCP_PORT)) {
     client.print(payload);
     client.stop();
   }
  }  

  /* Read data once a minute */
  delay(60000);
}
