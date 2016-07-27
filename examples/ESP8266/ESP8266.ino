/*
  This a simple example of the aREST UI Library for the ESP8266.
  See the README file for more details.

  Written in 2014-2016 by Marco Schwartz under a GPL license.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>
#include <aREST_UI.h>

// Create aREST instance
aREST_UI rest = aREST_UI();

// WiFi parameters
const char* ssid = "yourSSID";
const char* password = "yourPassword";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Variables to be exposed to the API
int temperature;
float humidity;

int ledControl(String command);

void setup(void) {
  // Start Serial
  Serial.begin(115200);

  // Set the title
  rest.title("aREST UI Demo");

  // Create button to control pin 5
  rest.button(5);

  // Init variables and expose them to REST API
  temperature = 22;
  humidity = 39.1;
  rest.variable("temperature", &temperature);
  rest.variable("humidity", &humidity);

  // Labels
  rest.label("temperature");
  rest.label("humidity");

  // Function to be exposed
  rest.function("led", ledControl);

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("esp8266");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

}

void loop() {
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  rest.handle(client);

}

int ledControl(String command) {
  // Print command
  Serial.println(command);

  // Get state from command
  int state = command.toInt();

  digitalWrite(5, state);
  return 1;
}
