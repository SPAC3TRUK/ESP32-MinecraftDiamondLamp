#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

//CONFIG RETE
const char* ssid     = ""; // Inserisci nome rete
const char* password = ""; // Inserisci password rete

//RING
#define LED_PIN   4
#define NUM_LEDS  13

Adafruit_NeoPixel ring(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// SERVER HTTP
WebServer server(80);

//STATI
uint8_t luminosita = 128;
bool statoAcceso = true;
uint8_t effettoCorrente = 0;
uint32_t coloreCorrente = 0xFF0000;

//FILE CONFIG
String configPath = "/config.json";

//FUNZIONE: SALVA CONFIG
void salvaConfig() {
  DynamicJsonDocument doc(256);
  doc["luminosita"] = luminosita;
  doc["statoAcceso"] = statoAcceso;
  doc["effetto"] = effettoCorrente;
  doc["colore"] = coloreCorrente;

  File f = LittleFS.open(configPath, "w");
  serializeJson(doc, f);
  f.close();
}

//FUNZIONE: CARICA CONFIG
void caricaConfig() {
  if (!LittleFS.exists(configPath)) {
    salvaConfig();
    return;
  }

  File f = LittleFS.open(configPath, "r");
  DynamicJsonDocument doc(256);
  DeserializationError err = deserializeJson(doc, f);
  f.close();

  if (!err) {
    luminosita = doc["luminosita"];
    statoAcceso = doc["statoAcceso"];
    effettoCorrente = doc["effetto"];
    coloreCorrente = coloreHEX(doc["colore"]);
  }
}

// WEB APP
const char MAIN_page[] PROGMEM = R"=====(<!DOCTYPE html>
<html lang="it">
<head>
  <meta charset="UTF-8">
  <title>Lampada LED ESP32</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <style>
    body{margin:0;background:#f3f3f3;padding:20px;min-height:100vh;font-family:Arial,sans-serif;text-align:center;}
    .container{max-width:900px;margin:0 auto;}
    h1{margin-bottom:20px;font-size:26px;}
    .btn{width:100%;padding:14px;margin:8px 0;border-radius:10px;border:none;font-size:18px;cursor:pointer;display:block;}
    .btn-effetto{background:#1976d2;color:#fff;}
    .btn-on{background:#37ec00;color:#fff;}
    .btn-off{background:#E53935;color:#fff;}
    .btn-applica{background:#FF9800;color:#fff;}
    .card{background:#fff;border-radius:12px;padding:16px;margin:12px 0;box-shadow:0 4px 15px rgba(0,0,0,0.1);text-align:left;}
    .card h2{margin-top:0;font-size:20px;}
    label{display:block;margin:8px 0 4px;font-weight:bold;}
    input[type="color"],input[type="range"]{width:100%;}
    .info-row{margin:4px 0;}
  </style>
</head>
<body>
  <div class="container">
    <h1>Lampada LED ESP32</h1>

    <div class="card">
      <h2>Effetti</h2>
      <button class="btn btn-effetto" onclick="setEffetto(0)">Ciclo colori</button>
      <button class="btn btn-effetto" onclick="setEffetto(1)">Effetto trasversale</button>
      <button class="btn btn-effetto" onclick="setEffetto(2)">Lampeggio + cambio colore</button>
      <button class="btn btn-effetto" onclick="setEffetto(3)">Colore fisso</button>
    </div>

    <div class="card">
      <h2>Colore & Stato</h2>
      <label for="pickerColore">Colore</label>
      <input type="color" id="pickerColore" value="#ff0000">
      <button class="btn btn-on" onclick="accendi()">Accendi</button>
      <button class="btn btn-off" onclick="spegni()">Spegni</button>
      <button class="btn btn-applica" onclick="applicaColore()">Imposta colore</button>
    </div>

    <div class="card">
      <h2>Luminosità</h2>
      <label for="sliderLuminosita">Luminosità</label>
      <input type="range" id="sliderLuminosita" min="0" max="255" value="128">
      <button class="btn btn-applica" onclick="applicaLuminosita()">Imposta luminosità</button>
    </div>

    <div class="card">
      <h2>Impostazioni / Info</h2>
      <div class="info-row">IP: <span id="ip"></span></div>
      <div class="info-row">MAC: <span id="mac"></span></div>
      <div class="info-row">Firmware: <span id="fw"></span></div>
    </div>
  </div>

<script>
function ajax(path, cb){
  var x=new XMLHttpRequest();
  x.onreadystatechange=function(){
    if(this.readyState===4 && this.status===200){cb && cb(this.responseText);}
  };
  x.open("GET", path, true);
  x.send();
}

function setEffetto(e){ ajax("/impostaEffetto?e="+e); }
function applicaColore(){
  var c=document.getElementById("pickerColore").value;
  ajax("/impostaColore?c="+encodeURIComponent(c));
}
function applicaLuminosita(){
  var b=document.getElementById("sliderLuminosita").value;
  ajax("/impostaLuminosita?b="+b);
}
function accendi(){ ajax("/accendi"); }
function spegni(){ ajax("/spegni"); }

function caricaInfo(){
  ajax("/info",function(r){
    var d=JSON.parse(r);
    document.getElementById("ip").textContent=d.ip;
    document.getElementById("mac").textContent=d.mac;
    document.getElementById("fw").textContent=d.fw;
  });
}

function caricaStato(){
  ajax("/stato",function(r){
    var d=JSON.parse(r);
    document.getElementById("pickerColore").value = "#" + d.colore.toString(16).padStart(6,'0');
    document.getElementById("sliderLuminosita").value = d.luminosita;
  });
}

setInterval(caricaStato,1000);
caricaInfo();
caricaStato();
</script>

</body>
</html>
)=====";



uint32_t coloreHEX(uint32_t c) {
  return ((c >> 16) & 0xFF) << 16 |
         ((c >> 8) & 0xFF) << 8 |
         (c & 0xFF);
}


//EFFETTI

void effettoCicloColori() {
  static uint16_t hue = 0;
  hue += 2;
  ring.setBrightness(luminosita);

  for (int i = 0; i < NUM_LEDS; i++) {
    uint32_t c = ring.ColorHSV(hue * 256);
    ring.setPixelColor(i, c);
  }
  ring.show();
}

void effettoTrasversale() {
  static int pos = 0;
  ring.setBrightness(luminosita);

  ring.clear();
  ring.setPixelColor(pos, coloreCorrente);
  ring.show();

  pos = (pos + 1) % NUM_LEDS;
}

void effettoLampeggioCambio() {
  static bool acceso = false;
  ring.setBrightness(luminosita);

  if (acceso) {
    for (int i = 0; i < NUM_LEDS; i++) ring.setPixelColor(i, coloreCorrente);
  } else {
    ring.clear();
  }

  ring.show();
  acceso = !acceso;
}

void effettoColoreFisso() {
  ring.setBrightness(luminosita);

  for (int i = 0; i < NUM_LEDS; i++) {
    ring.setPixelColor(i, coloreCorrente);
  }
  ring.show();
}

//HANDLER per webserver

void handleRoot() {
  server.send_P(200, "text/html", MAIN_page);
}

void handleStato() {
  DynamicJsonDocument doc(256);
  doc["luminosita"] = luminosita;
  doc["statoAcceso"] = statoAcceso;
  doc["effetto"] = effettoCorrente;
  doc["colore"] = coloreCorrente;

  String json;
  serializeJson(doc, json);
  server.send(200, "application/json", json);
}

void handleImpostaEffetto() {
  if (server.hasArg("e")) {
    effettoCorrente = server.arg("e").toInt();
    salvaConfig();
  }
  server.send(200, "text/plain", "OK");
}

void handleImpostaColore() {
  if (server.hasArg("c")) {
    String c = server.arg("c");
    if (c.startsWith("#")) c.remove(0, 1);
   coloreCorrente = strtol(c.c_str(), NULL, 16);
    salvaConfig();
  }
  server.send(200, "text/plain", "OK");
}

void handleImpostaLuminosita() {
  if (server.hasArg("b")) {
    luminosita = server.arg("b").toInt();
    ring.setBrightness(luminosita);
    salvaConfig();
  }
  server.send(200, "text/plain", "OK");
}

void handleAccendi() {
  statoAcceso = true;
  salvaConfig();
  server.send(200, "text/plain", "OK");
}

void handleSpegni() {
  statoAcceso = false;
  ring.clear();
  ring.show();
  salvaConfig();
  server.send(200, "text/plain", "OK");
}

void handleInfo() {
  DynamicJsonDocument doc(256);
  doc["ip"] = WiFi.localIP().toString();
  doc["mac"] = WiFi.macAddress();
  doc["fw"] = "1.0.0";

  String json;
  serializeJson(doc, json);
  server.send(200, "application/json", json);
}



//SETUP

void setup() {
  Serial.begin(115200);

  LittleFS.begin(true);
  caricaConfig();

  ring.begin();
  ring.setBrightness(luminosita);
  ring.show();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }

  server.on("/", handleRoot);
  server.on("/stato", handleStato);
  server.on("/impostaEffetto", handleImpostaEffetto);
  server.on("/impostaColore", handleImpostaColore);
  server.on("/impostaLuminosita", handleImpostaLuminosita);
  server.on("/accendi", handleAccendi);
  server.on("/spegni", handleSpegni);
  server.on("/info", handleInfo);

  server.begin();
}

//LOOP

void loop() {
  server.handleClient();

  if (!statoAcceso) return;

  switch (effettoCorrente) {
    case 0: effettoCicloColori(); break;
    case 1: effettoTrasversale(); break;
    case 2: effettoLampeggioCambio(); break;
    case 3: effettoColoreFisso(); break;
  }

  delay(50);
}
