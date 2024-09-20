#include <HttpClient.h>
#include <b64.h>

#include <HTTPClient.h>
#include <b64.h>

// Include required libraries
#include "WiFi.h"
#include "time.h"

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;
const int daylightOffset_sec = 0;

// WiFi credentials
const char* ssid = "OnePlus Nord CE 3 Lite 5G";    // change SSID
const char* password = "jaishreekrishna";        // change password

// Google script ID and required credentials
String GOOGLE_SCRIPT_ID = "1kHCG-lZjwFylDeir1478qf9IoU2cjhSsoboh2U42hePGe4X-GVur45Ad";    // change Gscript ID

int count = 0;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    static bool flag = false;
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      Serial.println("Failed to obtain time");
      return;
    }

    char timeStringBuff[50]; // 50 chars should be enough
    strftime(timeStringBuff, sizeof(timeStringBuff), "%A, %B %d %Y %H:%M:%S", &timeinfo);
    String asString(timeStringBuff);
    asString.replace(" ", "-");
    Serial.print("Time:");
    Serial.println(asString);

    String urlFinal = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?" + "date=" + asString + "&sensor=" + String(count);
    Serial.print("POST data to spreadsheet:");
    Serial.println(urlFinal);

    HttpClient http;
http.begin(urlFinal.c_str());
http.setFollowRedirects(HTTPC_STRICT_FOLLOW);  // Change this line
int httpCode = http.GET();
    Serial.print("HTTP Status Code: ");
    Serial.println(httpCode);

    // Getting response from google sheet
    String payload;
    if (httpCode > 0) {
      payload = http.getString();
      Serial.println("Payload: " + payload);
    }

    http.end();
  }

  count++;
  delay(1000);
}
