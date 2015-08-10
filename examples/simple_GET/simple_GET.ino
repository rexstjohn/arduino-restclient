/* RestClient simple GET request
 *
 * by Rex St John
 */

#include <WiFi.h>
#include <SPI.h>
#include "RestClient.h"

char ssid[] = "YOUR_SSID";            //  your network SSID (name)
char pass[] = "YOUR_WIFI_PW";         // your network password
char host[] = "www.google.com";      // target for your REST queries
int status = WL_IDLE_STATUS;         // the Wifi radio's status

// Create your WiFi RestClient, pass in the ssid and password.
RestClient client = RestClient(host, ssid, pass);

String response;
void setup() {

  // Initiate Serial Connection
  Serial.begin(9600);
  Serial.println("Starting REST client over Wi-Fi");
  if(client.connect() == WL_CONNECTED){
    response = "";
    int statusCode = client.get("/q=tacos", &response);
    Serial.print("Status code from server: ");
    Serial.println(statusCode);
    Serial.print("Response body from server: ");
    Serial.println(response);
    delay(1000);
  }
}

void loop(){
  // 
}
