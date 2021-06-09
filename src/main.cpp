#include <Arduino.h>
#include <WiFi.h>
#include <DHT.h>
#include <HTTPClient.h>

#define DHTPIN 27
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const char* ENDPOINT_URL = "MyEndpointURL";
const char* SSID = "MyHotspot";
const char* PASSWORD = "MyPassword";

float temperature;
float humidity;

unsigned long lastMillis = 0;
int delayTime = 600000;

// for debugging
void establishSerialConnection() {
    Serial.begin(115200);
    while (!Serial) {
        digitalWrite(BUILTIN_LED, HIGH);
    }
    digitalWrite(BUILTIN_LED, LOW);
    Serial.println("Serial connection established");
}

void connectToWiFi() {
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(BUILTIN_LED, HIGH);
    }
    digitalWrite(BUILTIN_LED, LOW);
}

void readTemperatureAndHumidity() {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
}

void sendTemperatureAndHumidity() {
    if (WiFi.status() == WL_CONNECTED) {
        digitalWrite(BUILTIN_LED, HIGH);
        HTTPClient http;
        String request = String(ENDPOINT_URL) + "?temperature=" + temperature + "&humidity=" + humidity;
        http.begin(request.c_str());
        http.end();
        digitalWrite(BUILTIN_LED, LOW);
    }
}

void setup() {
    pinMode(BUILTIN_LED, OUTPUT);
    connectToWiFi();
    dht.begin();
}

void loop() {
    try {
        if (millis() - lastMillis > delayTime) {
            lastMillis = millis();
            readTemperatureAndHumidity();
            sendTemperatureAndHumidity();
        }
    } catch (...) {
        ESP.restart();
    }
}
