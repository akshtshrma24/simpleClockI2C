#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <map>
#include <iostream>
#include <string>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows
const char* ssid     = "<SSID>";
const char* password = "<PASSWORD>";
String days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String trimmedTime = "";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String formattedDate;
String dayStamp;
String timeStamp;

void setup() {

  lcd.init();  // initialize the lcd
  lcd.backlight();
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  timeClient.setTimeOffset(18000);
}


void loop() {
  String temp = timeClient.getFormattedTime().substring(0, timeClient.getFormattedTime().length() - 3);
  if(trimmedTime != temp){
    timeClient.forceUpdate();
    Serial.println();
    lcd.clear();                 // clear display
    lcd.setCursor(0, 0);         // move cursor to   (0, 0)
    // lcd.print(std::string(timeClient.getHours())+ ":" + timeClient.getMinutes() + " " + days[timeClient.getDay() - 1]);        // print message at (0, 0)
    // days[timeClient.getDay() - 1]
    trimmedTime = temp;
    lcd.print(trimmedTime);
    Serial.println("looped");
  }
  delay(200);                 // display the above for two seconds
}