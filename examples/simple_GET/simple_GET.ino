/* RestClient simple GET request
 *
 * by Chris Continanza (csquared)
 */

#include <WiFi.h>
#include <SPI.h>
#include "RestClient.h"

char ssid[] = "YOUR_SSID";            //  your network SSID (name)
char pass[] = "YOUR_WIFI_PW";         // your network password
int status = WL_IDLE_STATUS;          // the Wifi radio's status
RestClient client = RestClient("google.com", ssid, pass);

String response;
void setup() {

  // Initiate Serial Connection
  Serial.begin(9600);
  Serial.println("Starting REST client over Wi-Fi");
  if(client.connect() == WL_CONNECTED){
    
    Serial.println("Starting REST client over Wi-Fi");
    response = "";
    int statusCode = client.get("/?search=arduino", &response);
    Serial.print("Status code from server: ");
    Serial.println(statusCode);
    Serial.print("Response body from server: ");
    Serial.println(response);
    delay(1000);
  }
}

void loop(){
}

