//Arav Sharma
//Ecolibrium Remote Sensor
//Air Quality Monitor

#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <SensirionI2CSen5x.h>
#include <SensirionI2CScd4x.h>
#include <Wire.h>

SensirionI2CSen5x sen5x;
SensirionI2CScd4x scd4x;

const char* ssid = "ECO-Sensorlab";
const char* password = "MikroKlimat";

AsyncWebServer server(80);

float massConcentrationPm1p0;
float massConcentrationPm2p5;
float massConcentrationPm4p0;
float massConcentrationPm10p0;
float ambientHumidity;
float ambientTemperature;
float vocIndex;
float noxIndex;
uint16_t co2;

String readScdCo2() {
  
    uint16_t c;
    float t;
    float h;
    
    scd4x.readMeasurement(c, t, h);
    
    if (c != 0) {
      co2 = c;
    }
    
    return String(co2);
}

String readPm1p0() {
    
    sen5x.readMeasuredValues(
        massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0,
        massConcentrationPm10p0, ambientHumidity, ambientTemperature, vocIndex,
        noxIndex);
    
    return String(massConcentrationPm1p0);
}

String readPm2p5() {
    
    sen5x.readMeasuredValues(
        massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0,
        massConcentrationPm10p0, ambientHumidity, ambientTemperature, vocIndex,
        noxIndex);
    
    return String(massConcentrationPm2p5);
}

String readPm4p0() {
    
    sen5x.readMeasuredValues(
        massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0,
        massConcentrationPm10p0, ambientHumidity, ambientTemperature, vocIndex,
        noxIndex);
    
    return String(massConcentrationPm4p0);
}

String readPm10p0() {
    
    sen5x.readMeasuredValues(
        massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0,
        massConcentrationPm10p0, ambientHumidity, ambientTemperature, vocIndex,
        noxIndex);
    
    return String(massConcentrationPm10p0);
}

String readAmbientHumidity() {
    
    sen5x.readMeasuredValues(
        massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0,
        massConcentrationPm10p0, ambientHumidity, ambientTemperature, vocIndex,
        noxIndex);
    
    return String(ambientHumidity);
}

String readAmbientTemperature() {
    
    sen5x.readMeasuredValues(
        massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0,
        massConcentrationPm10p0, ambientHumidity, ambientTemperature, vocIndex,
        noxIndex);
    
    return String(ambientTemperature);
}

String readVocIndex() {
    
    sen5x.readMeasuredValues(
        massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0,
        massConcentrationPm10p0, ambientHumidity, ambientTemperature, vocIndex,
        noxIndex);
    
    return String(vocIndex);
}

String readNoxIndex() {
    
    sen5x.readMeasuredValues(
        massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0,
        massConcentrationPm10p0, ambientHumidity, ambientTemperature, vocIndex,
        noxIndex);
    
    return String(noxIndex);
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script src="https://kit.fontawesome.com/d91e44f906.js" crossorigin="anonymous"></script>
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>ESP32 Air Quality Server</h2>
  <p>
    <i class="fas fa-smog" style="color:#000000;"></i> 
    <span class="dht-labels">PM 1.0</span>
    <span id="pm1p0">%PM1P0%</span>
    <sup class="units">ug/m3</sup>
  </p>
  <p>
    <i class="fas fa-smog" style="color:#a0a0a0;"></i>
    <span class="dht-labels">PM 2.5</span>
    <span id="pm2p5">%PM2P5%</span>
    <sup class="units">ug/m3</sup>
  </p>
  <p>
    <i class="fas fa-smog" style="color:#afafaf;"></i>
    <span class="dht-labels">PM 4.0</span>
    <span id="pm4p0">%PM4P0%</span>
    <sup class="units">ug/m3</sup>
  </p>
  <p>
    <i class="fas fa-smog" style="color:#f0f0f0;"></i> 
    <span class="dht-labels">PM 10.0</span>
    <span id="pm10p0">%PM10P0%</span>
    <sup class="units">ug/m3</sup>
  </p>
  <p>
    <i class="fas fa-project-diagram" style="color:#631fc4;"></i> 
    <span class="dht-labels">Carbon Dioxide</span>
    <span id="co2">%CO2%</span>
    <sup class="units">ppm</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Ambient Humidity</span>
    <span id="ambienthumidity">%AMBIENTHUMIDITY%</span>
    <sup class="units">&percnt;</sup>
  </p>
  <p>
    <i class="fas fa-thermometer-half" style="color:#bada55;"></i>
    <span class="dht-labels">Ambient Temperature</span>
    <span id="ambienttemperature">%AMBIENTTEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-lungs" style="color:#ffb6c1;"></i> 
    <span class="dht-labels">Voc Index</span>
    <span id="vocindex">%VOCINDEX%</span>
    <sup class="units">-</sup>
  </p>
  <p>
    <i class="fas fa-grin-squint-tears" style="color:#9b870c;"></i> 
    <span class="dht-labels">Nox Index</span>
    <span id="noxindex">%NOXINDEX%</span>
    <sup class="units">-</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("pm1p0").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/pm1p0", true);
  xhttp.send();
}, 5000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("pm2p5").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/pm2p5", true);
  xhttp.send();
}, 5000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("pm4p0").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/pm4p0", true);
  xhttp.send();
}, 5000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("pm10p0").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/pm10p0", true);
  xhttp.send();
}, 5000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("co2").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/co2", true);
  xhttp.send();
}, 5000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ambienthumidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/ambienthumidity", true);
  xhttp.send();
}, 5000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ambienttemperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/ambienttemperature", true);
  xhttp.send();
}, 5000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("vocindex").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/vocindex", true);
  xhttp.send();
}, 5000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("noxindex").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/noxindex", true);
  xhttp.send();
}, 5000 ) ;

</script>
</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
//  if(var == "TEMPERATURE"){
//    return readScdTemp();
//  }
//  else if(var == "HUMIDITY"){
//    return readScdHum();
//  }
//  else if(var == "CO2"){
//    return readScdCo2();
//  }
  if(var == "PM1P0"){
    return readPm1p0();
  }
  else if(var == "PM2P5"){
    return readPm2p5();
  }
  else if(var == "PM4P0"){
    return readPm4p0();
  }
  else if(var == "PM10P0"){
    return readPm10p0();
  }
  else if(var == "AMBIENTHUMIDITY"){
    return readAmbientHumidity();
  }
  else if(var == "AMBIENTTEMPERATURE"){
    return readAmbientTemperature();
  }
  else if(var == "VOCINDEX"){
    return readVocIndex();
  }
  else if(var == "CO2") {
    return readScdCo2();
  }
  else if(var == "NOXINDEX") {
    return readNoxIndex();
  }
  
  
  return String();
}

void setup(){

  Serial.begin(115200);

  //start sensors
  Wire.begin();

  sen5x.begin(Wire);

  sen5x.deviceReset();

  sen5x.setTemperatureOffsetSimple(0.00);

  sen5x.startMeasurement();

  delay(1000);

  scd4x.begin(Wire);

  scd4x.startPeriodicMeasurement();
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/pm1p0", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readPm1p0().c_str());
  });
  server.on("/pm2p5", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readPm2p5().c_str());
  });

  server.on("/pm4p0", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readPm4p0().c_str());
  });

  server.on("/pm10p0", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readPm10p0().c_str());
  });

  server.on("/co2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readScdCo2().c_str());
  });

  server.on("/ambienthumidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readAmbientHumidity().c_str());
  });

  server.on("/ambienttemperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readAmbientTemperature().c_str());
  });

  server.on("/vocindex", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readVocIndex().c_str());
  });

  server.on("/noxindex", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readNoxIndex().c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  
}
