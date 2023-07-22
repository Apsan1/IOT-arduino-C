#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "apsan_2";
const char* password = "";
//C++ code for my project
boolean PIRstate;
boolean lastPIRstate;
int led = 2;
int PIR = 0;

void setup(){
    Serial.begin(115200);
    delay(1000); // Wait for serial monitor to open
    
    // Connect to WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    // Print connection info
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Set up PIR sensor
    pinMode(PIR, INPUT);
    pinMode(led, OUTPUT);
    delay(3000);

}

void loop(){
    PIRstate = digitalRead(PIR);
    if (PIRstate != lastPIRstate) {
        digitalWrite(led, LOW);
        delay(100);
        digitalWrite(led, HIGH);
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("Sending request");
            HTTPClient http;
            http.begin("https://maker.ifttt.com/trigger/iot_object/json/with/key/esmoAy7KtRGe-iUYJ7Jv-01b1Y6KgO5hW2Egyw0yBFQ ");
            http.GET();
            Serial.println("Notified!");
            http.end();
    }
    lastPIRstate = PIRstate;
    delay(100);
    }
}
