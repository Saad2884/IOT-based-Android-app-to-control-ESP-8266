#include <Arduino.h>
#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <WebSocketsServer.h> //import for websocket

#define ledpin 2 //defining the OUTPUT pin for LED
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15


const char *ssid =  "HelloHPC - Wifi";   //Wifi SSID (Name)
const char *pass =  "12345678"; //wifi password
String cmd = "";

WebSocketsServer webSocket = WebSocketsServer(81); //websocket init with port 81

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  //webscket event method

  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("Websocket is disconnected");
      //case when Websocket is disconnected
      break;
    case WStype_CONNECTED: {
        //wcase when websocket is connected
        Serial.println("Websocket is connected");
        Serial.println(webSocket.remoteIP(num).toString());
        webSocket.sendTXT(num, "connected");
      }
      break;
    case WStype_TEXT:
      cmd = "";
      for (int i = 0; i < length; i++) {
        cmd = cmd + (char) payload[i];
      } //merging payload to single string
      Serial.println(cmd);

      D0button();
      D1button();
      D2button();
      D3button();
      D4button();
      D5button();
      D6button();
      D7button();
      D8button();


      webSocket.sendTXT(num, cmd += ":success");

      //send response to mobile, if command is "poweron" then response will be "poweron:success"
      //this response can be used to track down the success of command in mobile app.
      break;
    case WStype_FRAGMENT_TEXT_START:
      break;
    case WStype_FRAGMENT_BIN_START:
      break;
    case WStype_BIN:
      //hexdump(payload, length);
      break;
    default:
      break;
  }
}

void D0button() {
  if (cmd == "D0on") { //when command from app is "poweron"
    digitalWrite(D0, HIGH);

  } if (cmd == "D0off") {
    digitalWrite(D0, LOW);

  }
}

void D1button() {

  if (cmd == "D1on") {
    digitalWrite(D1, HIGH);
  }

  if (cmd == "D1off") {
    digitalWrite(D1, LOW);
  }
}

void D2button() {
  if (cmd == "D2on") {
    digitalWrite(D2, HIGH);
  }

  if (cmd == "D2off") {
    digitalWrite(D2, LOW);
  }

  if (cmd == "D2slow") {
    analogWrite(D2, 64);
  }

  if (cmd == "D2moderate") {
    analogWrite(D2, 128);
  }
  if (cmd == "D2fast") {
    analogWrite(D2, 192);
  }
}


void D3button() {

  if (cmd == "D3on") {
    digitalWrite(D3, HIGH);
  }

  if (cmd == "D3off") {
    digitalWrite(D3, LOW);
  }
}


void D4button() {

  if (cmd == "D4on") {
    digitalWrite(D4, HIGH);
  }

  if (cmd == "D4off") {
    digitalWrite(D4, LOW);
  }
}



void D5button() {
  if (cmd == "D5on") {
    digitalWrite(D5, HIGH);
  }

  if (cmd == "D5off") {
    digitalWrite(D5, LOW);
  }

  if (cmd == "D5slow") {
    analogWrite(D5, 64);
  }

  if (cmd == "D5moderate") {
    analogWrite(D5, 128);
  }
  if (cmd == "D5fast") {
    analogWrite(D5, 192);
  }
}

void D6button() {
  if (cmd == "D6on") {
    digitalWrite(D6, HIGH);
  }

  if (cmd == "D6off") {
    digitalWrite(D6, LOW);
  }

  if (cmd == "D6slow") {
    analogWrite(D6, 64);
  }

  if (cmd == "D6moderate") {
    analogWrite(D6, 128);
  }
  if (cmd == "D5fast") {
    analogWrite(D6, 192);
  }
}

void D7button() {

  if (cmd == "D7on") {
    digitalWrite(D7, HIGH);
  }

  if (cmd == "D7off") {
    digitalWrite(D7, LOW);
  }
}

void D8button() {
  if (cmd == "D8on") {
    digitalWrite(D8, HIGH);
  }

  if (cmd == "D8off") {
    digitalWrite(D8, LOW);
  }

  if (cmd == "D8slow") {
    analogWrite(D8, 64);
  }

  if (cmd == "D8moderate") {
    analogWrite(D8, 128);
  }
  if (cmd == "D8fast") {
    analogWrite(D8, 192);
  }
}

void setup() {
  //pinMode(ledpin, OUTPUT); //set ledpin (D2) as OUTPUT pin
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);

  Serial.begin(9600); //serial start

  Serial.println("Connecting to wifi");

  IPAddress apIP(192, 168, 0, 1);   //Static IP for wifi gateway
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); //set Static IP gateway on NodeMCU
  WiFi.softAP(ssid, pass); //turn on WIFI

  webSocket.begin(); //websocket Begin
  webSocket.onEvent(webSocketEvent); //set Event for websocket
  Serial.println("Websocket is started");
}

void loop() {
  webSocket.loop(); //keep this line on loop method
}
