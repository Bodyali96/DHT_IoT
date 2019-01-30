# DHT_IoT
Basic implementation of transferring DHT values through UDP connection and Arduino Uno.
![](https://i.imgur.com/ZkWWNF3.jpg)

## The Goal
Using Arduino Uno to collect DHT sensor values and send them through UDP protocol to local server on my laptop device.

## Components
* [Arduino Uno](https://store.arduino.cc/usa/arduino-uno-rev3)
* [Wifi Shield V2](http://wiki.seeedstudio.com/Wifi_Shield_V2.0/)
* [Base Shield](https://www.seeedstudio.com/Base-Shield-V2-p-1378.html)
* [Air Humidity Sensor - DHT](https://www.mysensors.org/build/humidity)

## Software Side
* Python local server
* [Arduino IDE](https://www.arduino.cc/en/main/software)

## External Arduino Libraries
* Wifly
* [AndroidJson](https://arduinojson.org/v5/example/)
* DHT

## Python External Modules
* socket
* json
Note: unlike Arduino libraries, it is enough here to just import the libraries in the code (there is no need to download anything)

## How to Start
After connecting all pieces together, just upload the Arduino code to the Arduino and then run the python code using the command `python recieve.py`. You will then watch the data printed in the console.

## How it works?
The DHT sensor collects data, these data are packaged using json generator and send through UDP protocol to the local python server to parse the json object and show the data on console.
