# Plant Health

A project to track data about my house plant(s).

## Equipment
- [Arduino MKR WiFi 1010](https://store.arduino.cc/products/arduino-mkr-wifi-1010)
- [Battery](https://www.adafruit.com/product/2011)
- [Raspberry Pi 4 Model B](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/?variant=raspberry-pi-4-model-b-8gb)
- [Moisture Sensor](https://www.amazon.com/gp/product/B07QXZC8TQ/)
- [Bread Board](https://www.adafruit.com/product/239?gad_source=1&gclid=CjwKCAiAlcyuBhBnEiwAOGZ2S3EZKIMj9_BwmLrHyNFh9rwf-k6iW4ZmXnfJANrQMKz_nFzQjY7kIBoC-rIQAvD_BwE)
- [Jump Wires](https://www.amazon.com/Elegoo-EL-CP-004-Multicolored-Breadboard-arduino/dp/B01EV70C78)

## Software
- [Raspberry Pi Imager](https://www.raspberrypi.com/software/)
- [Arduino IDE](https://www.arduino.cc/en/software)

This guide assumes that you are somewhat familiar with the basics of working with a breadboard and arduino devices.

## Hardware Setup
Although you technically can plug all the devices directly into the MKR1010, I recommend installing it onto a breadboard and utilizing the rails for ease of setup/use. I chose to jump the pins to different rails away from the arduino to make it easier to deal with and keep all the wires on one side of the board.

1. Install the MKR1010 into your breadboard.
2. Connect the ground pin to the ground rail of the breadboard.
3. Connect the 0 and 1 pins (digital) to the VCC connector on the moisture sensor using a 1k ohm resistor between them.
4. Connect the A0 and A1 (analog in) to the Analog connector on the moisture sensor
5. Connect the ground connector on the moisture sensor to the ground rail on the bread board.
6. When ready, connect the battery to the arduino making note of the arduino data sheet and the polarity of the battery. The connector can sometimes be incorrect on cheaper batteries and you'll need to buy another or change the polarity which can be quite tricky. If you're unsure of what you are doing, I recommend skipping this step and using the usb power and an outlet.

## Software Setup
1. Clone repository
2. Plug in the Arduino into a usb port on your PC. Open the Arduino IDE and load the main.ino file. `devices/arduino/main.ino`. If there are errors loading the code onto the Arduino you may need to update the firmware.
4. Test the Arduino
    - With the cables connected to the moisture module and Arduino, connect the serial port to the PC running the Arduino IDE.
    - Load the sketch onto the Arduino
    - To enable WiFi, replace the `{{SSID}}` and `{{WIFI_PASSWORD}}` with your WiFi information.
    - To enable communication, replace the `{{TCP_SERVER}}` with the IP of your server and `{{TCP_PORT}}` with the port to communicate over.
    - Open the serial viewer in the Arduino IDE. You should see values being printed out to the screen. If you hold or move the sensor to a new environment you should see changes to the values being printed out. Once the IO is verified as working, continue to the next step.
    - If your arduino does not have WiFi capabilities, the code will skip over the WiFi portion of the code and will write all output to the serial out.
5. Using the Raspberry Pi Imager, flash Ubuntu Server to the Raspberry Pi. If you are not familiar with linux, I recommend using the Imagers settings to add your WiFi network (if not using ethernet) and enable ssh.
6. Once complete, find your the Raspberry Pi IP address to ssh to it or plug into it manually.
7. Load and start the data reader
    - Once you have access to the Raspberry Pi, load the reader script onto the Pi. It is in `data_reciever/reader.sh`.
    - Update the permissions on the script by running `chmod u+x reader.sh`.
    - Create a new screen by running `screen -S reader`.
    - Start the reader by running `./reader.sh`
    - Use ctrl + a followed by d to exit the screen and leave it running in the background.
8. Serve the data file
    - Create a new screen by running `screen -S server`.
    - Start a python server in the same directory as the `reader.sh` file by running `python3 -m http.server`
    - Use ctrl + a followed by d to exit the screen and leave it running in the background.
9. Using a browser on a device that is on the same network as the Pi, navigate to `{{pi IP address}}:8000/sensor_data.txt` to see a list of values read by the sensor.
10. Refresh this page to see updated data.
11. Once the dataflow is working, setup the hardware near your plant and place the sensors in the soil. Before restarting the devices you may want to clear out the data file.

## Changelog
2024-02-19
- Hardware
    - Can now power the solution with a battery instead of needing to be plugged in.
    - Added 1k ohm resistors between the digital pins and VCC of the sensors as recommended on the Arduino docs.
- Arduino Code
    - Updated to only use WiFi when a WiFi module is detected.
    - Updated to only power on the sensors when taking readings to conserve power and longevity of the sensors.
    - Updated to set the WiFi module to low power mode for bettery battery life.
    - Consolidated the WiFi and Serial only code to be one sketch.
    - Code no longer tries to read pins that are not connected. To add pins, user will have to manually update code to read from them.
    - Sensors are only read from once a minute instead of every five seconds.
- Updated README.

2024-01-21
- Add initial code to support data flow from the moisture sensor to a web page.
- Add equipment list to README
- Add setup instructions to README