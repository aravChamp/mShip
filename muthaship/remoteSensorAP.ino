#include <WiFi.h>
#include <HTTPClient.h>

#include "Adafruit_SHT4x.h"  //humidity and temperature sensor

const char* ssid = "Muthaship";  //mothership wifi network
const char* password = "sensorhub1";

const char* serverName = "http://10.20.1.1/fetchRemoteSensorData.php";
//name of php code running on mothership apache2 server

String apiKeyValue = "gH8lPhd7v8a4f";

Adafruit_SHT4x sht4 = Adafruit_SHT4x(); //construct sht sensor

void setup() {
  
  Serial.begin(115200);  //standard baud rate for esp32

  WiFi.begin(ssid, password);  
  //begins wifi connection and waits for connection
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println(WiFi.localIP());  //displays local ip adress

  sht4.begin();  \\begins sht sensor readings

  sht4.setPrecision(SHT4X_HIGH_PRECISION);

  sht4.setHeater(SHT4X_NO_HEATER);  //ideal for low power application

  delay(5000);
  
}
void loop() {
  


  sensors_event_t humidity, temp;
  
  // populate temp and humidity objects with fresh data
  sht4.getEvent(&humidity, &temp);

    int x = analogRead(35);  //co2 sensor connected to pin 35

    int y = analogRead(32);  //methane sensor connected to pin 32

    double z = analogRead(33);  //thermistor connected to pin 33

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, serverName);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    //adds all sensor data to a single string
    //this can easily be manipulated by the php code
    String httpRequestData = "api_key=" + apiKeyValue 
                          + "&value1=" + String(temp.temperature)
                          + "&value2=" + String(humidity.relative_humidity) 
                          + "&value3=" + String(analogRead(34)) 
                          + "&value4=" + String(x) 
                          + "&value5=" + String(y) 
                          + "&value6=" + String(z) + "";

    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);

    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 5 seconds
  delay(5000); 

}