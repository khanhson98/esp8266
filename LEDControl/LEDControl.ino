#include <SocketIoClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>

#define USER_SERIAL Serial


//const char* ssid1 = "DODO-78D9";
const char* ssid1 = "Galaxy Tab S6 Lite87F1";
const char* ssid2 = "Son";
const char* ssid3 = "Mechanics";
//const char* pass = "UV5NNLGWGT";
const char* pass = "88888888";
const char* passWorkshop = "ask Will he knows the password!";
SocketIoClient webSocket;


void setup() {
  USER_SERIAL.begin(115200);

  connectWiFi();

 //webSocket.begin("192.168.233.8", 5000);
  webSocket.begin("khanhsonesp8266.herokuapp.com");
  webSocket.on("colorChanged", changeColor);
}

void loop() {
  webSocket.loop();

}

void changeColor(const char* data, size_t length){ 
  USER_SERIAL.println(data);
}

void connectWiFi(){
  WiFi.begin(ssid1, pass);
  int count = 0;
  
  while(WiFi.status() != WL_CONNECTED){
    USER_SERIAL.print(".");
    delay(1000);
    count ++;
    if (count == 7)
        WiFi.begin(ssid2, pass);
    else if (count == 14)
        WiFi.begin(ssid3, passWorkshop);
  }

  USER_SERIAL.print("");
  USER_SERIAL.println("WiFi connected");
  USER_SERIAL.print("IP Address : ");
  USER_SERIAL.println(WiFi.localIP());
  
}
