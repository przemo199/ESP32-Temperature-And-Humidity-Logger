# ESP32 Temperature Logger

This project uses ESP32 and DHT22 temperature and humidity sensor to store measurements in a Google spreadsheet.

## Google Apps Script setup

To be able to save the values in a spreadsheet you need an endpoint to which you can send the requests with the data.

You can do it by creating a Google Apps Script:

1. Create a new [Google spreadsheet](https://docs.google.com/spreadsheets) and open it.
2. Go to `Extensions > Apps Scripts`.
3. Copy the content of `./gs/Code.gs` to the opened editor.
4. Find the URL of the spreadsheet you just created (you can find it in the browser address bar) and use it to replace the string `'Link to your spreadsheet'`.
5. Select `Deploy > New Deployment` and in `Who has access` choose `Anyone`.
6. Click `Deploy` and accept all of the required app permissions.
7. Now select `Deploy > Manage Deployments`, you should see your last deployment, select it and copy the Web App URL, it is your endpoint to which you can send the data.

## ESP32 setup

To connect the sensor to the ESP32 board you will need one 10kΩ resistor and at least 3 wires, one to deliver power, one to connect the sensor to ground and one for transmitting the data.

First copy this repository to your computer and set 3 variables in `./src/main.cpp` file:

- ENDPOINT_URL - URL that you copied when creating Google Apps Script
- SSID - your WiFi network's name
- PASSWORD - your WiFi network's password
 
To flash your board with the new firmware I recommend using [PlatformIO](https://platformio.org/) as it was used to develop this project and will automatically handle required dependencies.  
Once you install PlatformIO and add it to the CLASSPATH you should connect your board to the computer with this repository, open command line inside of the repository and run command `pio run -t upload`.  
The ESP32 should now be automatically flashed and if you correctly setup the variables the onboard LED will light up and quickly turn off which indicates that the WiFi connection has beed stablished.  
During every request send to the endpoint the onboard LED briefly lights up but if it remains turned on for more than 5 second it may indicate that the network connection has been interrupted or the endpoint is unavailable.
