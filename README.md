# WiFi RestClient for Arduino

HTTP Request library for Arduino and the WiFi shield. I modified the original Ethernet-only version to use on Intel Edison, should work fine with other Arduino WiFi devices though.

I think aJSON would be really helpful to integrate as a next step.

# Install

Clone (or download and unzip) the repository to `~/Documents/Arduino/libraries`
where `~/Documents/Arduino` is your sketchbook directory.

    > cd ~/Documents/Arduino
    > mkdir libraries
    > cd libraries
    > git clone https://github.com/rexstjohn/arduino-restclient.git RestClient

# Usage

### Include

You need to have the `WiFi` library already included.

```c++
#include <WiFi.h>
#include <SPI.h>
#include "RestClient.h"
```

### RestClient(host/ip, [port])

Constructor to create an RestClient object to make requests against.

Use domain name and default to port 80, add your WiFi SSID and password:
```c++
RestClient client = RestClient("google.com", SSID, PW);
```

### connect()

Sets up `WiFiClient` using the provided SSID and PW

```c++
  client.connect()
```

Note: you can have multiple RestClient objects but only need to call
this once.

Note: if you have multiple Arduinos on the same network, you'll need
to give each one a different mac address.

### begin(char* ssid, char *pw)

It just wraps the `WiFiClient` call to `begin` and connects.

## RESTful methods

All methods return an HTTP status code or 0 if there was an error.

### `get(const char* path)`
### `get(const char* path, String* response)`

Start making requests!

```c++
int statusCode = client.get("/"));
```

Pass in a string *by reference* for the response:
```
String response = "";
int statusCode = client.get("/", &response);
```

### post(const char* path, const char* body)
### post(const char* path, String* response)
### post(const char* path, const char* body, String* response)

```
String response = "";
int statusCode = client.post("/", &response);
statusCode = client.post("/", "foo=bar");
response = "";
statusCode = client.post("/", "foo=bar", &response);
```

### put(const char* path, const char* body)
### put(const char* path, String* response)
### put(const char* path, const char* body, String* response)

```
String response = "";
int statusCode = client.put("/", &response);
statusCode = client.put("/", "foo=bar");
response = "";
statusCode = client.put("/", "foo=bar", &response);
```

### del(const char* path)
### del(const char* path, const char* body)
### del(const char* path, String* response)
### del(const char* path, const char* body, String* response)

```
String response = "";
int statusCode = client.del("/", &response);
```



