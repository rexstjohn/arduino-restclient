#include "RestClient.h"

RestClient::RestClient(const char* _host, const char* _ssid, const char* _pw){
  host = _host;
  port = 80;
  ssid = _ssid;
  pw = _pw;
  num_headers = 0;
  contentType = "x-www-form-urlencoded";  // default
}

int RestClient::connect(){
  int status = begin((char*)ssid,(char*)pw);
  if (status != WL_CONNECTED) {
    Serial.println("Failed to configure WIFI using provided ssid, pw");
  } else {
    Serial.println("Connected to WiFi!");
  }
  return status;
}

int RestClient::begin(char* _ssid, char* _pw){
  //give it time to initialize
  Serial.print("Attempting to connect to SSID:");
  Serial.println(_ssid);
  Serial.print("Attempting to connect to SSID PW:");
  Serial.println(_pw);
  int status = WL_IDLE_STATUS;
  status = WiFi.begin(_ssid, _pw);
  return status;
}

// GET path
int RestClient::get(const char* path){
  return request("GET", path, NULL, NULL);
}

//GET path with response
int RestClient::get(const char* path, String* response){
  return request("GET", path, NULL, response);
}

// POST path and body
int RestClient::post(const char* path, const char* body){
  return request("POST", path, body, NULL);
}

// POST path and body with response
int RestClient::post(const char* path, const char* body, String* response){
  return request("POST", path, body, response);
}

// PUT path and body
int RestClient::put(const char* path, const char* body){
  return request("PUT", path, body, NULL);
}

// PUT path and body with response
int RestClient::put(const char* path, const char* body, String* response){
  return request("PUT", path, body, response);
}

// DELETE path
int RestClient::del(const char* path){
  return request("DELETE", path, NULL, NULL);
}

// DELETE path and response
int RestClient::del(const char* path, String* response){
  return request("DELETE", path, NULL, response);
}

// DELETE path and body
int RestClient::del(const char* path, const char* body ){
  return request("DELETE", path, body, NULL);
}

// DELETE path and body with response
int RestClient::del(const char* path, const char* body, String* response){
  return request("DELETE", path, body, response);
}

void RestClient::write(const char* string){
  Serial.println(string);
  client.print(string);
}

void RestClient::setHeader(const char* header){
  headers[num_headers] = header;
  num_headers++;
}

void RestClient::setContentType(const char* contentTypeValue){
  contentType = contentTypeValue;
}

// The mother- generic request method.
//
int RestClient::request(const char* method, const char* path,
                  const char* body, String* response){

  if(client.connect(host, port)){
    Serial.println("REQUEST: \n");
    // Make a HTTP request line:
    write(method);
    write(" ");
    write(path);
    write(" HTTP/1.1\r\n");
    for(int i=0; i<num_headers; i++){
      write(headers[i]);
      write("\r\n");
    }
    write("Host: ");
    write(host);
    write("\r\n");
    write("Connection: close\r\n");

    if(body != NULL){
      char contentLength[30];
      sprintf(contentLength, "Content-Length: %d\r\n", strlen(body));
      write(contentLength);

    write("Content-Type: ");
    write(contentType);
    write("\r\n");
    }

    write("\r\n");

    if(body != NULL){
      write(body);
      write("\r\n");
      write("\r\n");
    }

    //make sure you write all those bytes.
    delay(100);
    int statusCode = readResponse(response);

    //cleanup
    num_headers = 0;
    client.stop();
    delay(50);

    return statusCode;
  }else{
    Serial.println("HTTP Connection failed");
    return 0;
  }
}

int RestClient::readResponse(String* response) {

  // an http request ends with a blank line
  boolean currentLineIsBlank = true;
  boolean httpBody = false;
  boolean inStatus = false;

  char statusCode[4];
  int i = 0;
  int code = 0;

  if(response == NULL){
    Serial.println("HTTP: NULL RESPONSE POINTER: ");
  }else{
    Serial.println("HTTP: NON-NULL RESPONSE POINTER: ");
  }

  Serial.println("HTTP: RESPONSE: ");
  while (client.connected()) {

    if (client.available()) {
      Serial.print(",");
      char c = client.read();
      Serial.print(c);

      if(c == ' ' && !inStatus){
        inStatus = true;
      }

      if(inStatus && i < 3 && c != ' '){
        statusCode[i] = c;
        i++;
      }
      if(i == 3){
        statusCode[i] = '\0';
        code = atoi(statusCode);
      }

      if(httpBody){
        //only write response if its not null
        if(response != NULL) response->concat(c);
      }
      else
      {
          if (c == '\n' && currentLineIsBlank) {
            httpBody = true;
          }

          if (c == '\n') {
            // you're starting a new line
            currentLineIsBlank = true;
          }
          else if (c != '\r') {
            // you've gotten a character on the current line
            currentLineIsBlank = false;
          }
      }
    } else break;
  }

  Serial.println("HTTP: return readResponse");
  return code;
}
