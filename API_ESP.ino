#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>

#define LED_PIN 13

String ssid; 
String wifi_password; 

void setup() {
  pinMode(LED_PIN, OUTPUT); 
  Serial.begin(9600); 
  delay(3000);

  int choice;
  uint addr = 0;  
  
  Serial.println();
  Serial.println("1. Do you want to enter new credentials?"); 
  Serial.println("2. Do you want to search in EEPROM for credentials?"); 
  while(!choice) {
     Serial.println("Enter your choice: ");
     char c = Serial.read(); 
     choice = int(c); 
    }
  if(choice == 2) {
    while(ssid == "") {
    Serial.println("Enter your SSID: "); 
    ssid = Serial.readString();
    } 
    while(wifi_password == "") {
      Serial.println("Enter your WiFi password: "); 
      wifi_password = Serial.readString();
    }
    ssid.replace("\n", ""); 
    wifi_password.replace("\n", ""); 
    
    Serial.print("SSID: "); 
    Serial.println(ssid); 
    Serial.println("Password you entered has " + String(wifi_password.length()) + " characters!"); 

    EEPROM.begin(512); 
    EEPROM.put(addr, ssid);
    EEPROM.put(addr + ssid.length(), wifi_password);  
    EEPROM.commit(); 

    Serial.println("WiFi data has been written in EEPROM"); 

    } else {
      EEPROM.get(addr, ssid); 
      EEPROM.get(addr + ssid.length(), wifi_password); 
      }
  
  Serial.print("Now connecting to: "); 
  Serial.println(ssid); 

  WiFi.begin(ssid, wifi_password); 
  Serial.print("Connecting...");

  digitalWrite(LED_PIN, HIGH); 
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);  
    Serial.print("."); 
    }
  Serial.println(" "); 
  Serial.println("Connected to your network!"); 
  digitalWrite(LED_PIN, LOW); 
  
  Serial.println("Use this URL to connect: "); 
  Serial.print("http://");
  Serial.println(WiFi.localIP()); 

}

void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    digitalWrite(LED_PIN, HIGH); 
    HTTPClient http; 
    http.begin("http://192.168.43.68:4567/esp");
    int httpCode = http.GET(); 
    Serial.println(httpCode); 
    digitalWrite(LED_PIN, LOW); 
    }
  delay(5000); 
}
