# Plant Health

A project to track data about my house plant(s).

## Equipment
- [Arduino Uno WiFi Rev2](https://store.arduino.cc/products/arduino-uno-wifi-rev2)
- [Raspberry Pi 4 Model B](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/?variant=raspberry-pi-4-model-b-8gb)
- [Moisture Sensor](https://www.amazon.com/gp/product/B07QXZC8TQ/)
- [Jump Wires](https://www.amazon.com/Elegoo-EL-CP-004-Multicolored-Breadboard-arduino/dp/B01EV70C78)

## Software
- [Raspberry Pi Imager](https://www.raspberrypi.com/software/)
- [Arduino IDE](https://www.arduino.cc/en/software)

## Setup
1. Clone repository
2. Plug in the Arduino into a usb port on your PC. Open the Arduino IDE and load the moisture_sensor.ino file. `devices/moisture_sensor/moisture_sensor.ino`. If there are errors loading the code onto the Arduino you may need to update the firmware. The current code was written for the Arduino Uno WiFi Rev2 on firmware 1.5.0.
3. Wire a moisture sensor into the 'first' analog slot (A0).
    - Connect the VCC pin on the moisture module to the 3.3v pin on the Arduino.
    - Connect the ground pin on the moisture module to one of the ground pins on the Arduino.
    - Connect the A0 pin on the moisture module to the A0 input on the Arduino.
4. Test the Arduino
    - With the cables connected to the moisture module and Arduino, connect the serial port to the PC running the Arduino IDE.
    - Load the sketch onto the Arduino
    - Open the serial viewer in the Arduino IDE. You should see values being printed out to the screen. If you hold or move the sensor to a new environment you should see changes to the values being printed out. Once the IO is verified as working, continue to the next step.
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
2024-01-21
- Add initial code to support data flow from the moisture sensor to a web page.
- Add equipment list to README
- Add setup instructions to README