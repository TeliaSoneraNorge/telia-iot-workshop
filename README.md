# Telia IoT Workshop

## 1. Install software
The Crowduino M0 is an Arduino-compatible board. To program it, we need some software. Follow this guide: https://www.elecrow.com/wiki/index.php?title=Step1:_Download_Arduino_IDE_and_install_Arduino_driver

## 2. Blink an led
Make sure everything is working by running a simple example. Follow this guide: https://www.elecrow.com/wiki/index.php?title=Step2:_The_very_basic_experiments_with_Crowduino

You should se the LED on the board blinking. **Bonus:** try changing the delays and adding in more lines to create other blinking patterns.

## 3. Print a message
It is sometimes helpful to print out a message to yourself to figure out how the code works. Try out this code and see if you can understand it. Create a new file in the Arduino software and paste it, then press upload (arrow button). After uploading, open the serial monitor (button on the top right).

```c
int messageNumber = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting program")
}

void loop() {
  Serial.println("This is message number " + String(messageNumber));
  messageNumber++;
  delay(1000);
}
```

**Bonus:** try adding another line with ```Serial.print("Hi! ");``` and upload again. See the difference between ```print``` and ```println```?

## 4. Get connected
* Download the code in this repository by clicking "Clone or Download" and then "Download ZIP" at the top of this page.
* In Arduino, click "Sketch", "Include library", "Add .ZIP library" and coose the file you just downloaded.
* Click "File", "Examples", "Telia NB-IoT", "PeriodicTemperatureUpdate"
* In the code, replace ```<device_id>``` with your own device ID given to you by the instructor.
* Upload the code, then go to the website to see you data.




