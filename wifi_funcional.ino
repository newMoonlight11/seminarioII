/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP32     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <WiFi.h>

String ClientRequest;
WiFiServer server(80);

WiFiClient client;

String myresultat;

String ReadIncomingRequest() {
  while (client.available()) {
    String peticion = client.readString();
    ClientRequest = (client.readStringUntil('\r'));
    if ((ClientRequest.indexOf("HTTP/1.1") > 0) && (ClientRequest.indexOf("/favicon.ico") < 0)) {
      myresultat = ClientRequest;
    }
  }
  return myresultat;
}

void setup() {
  ClientRequest = "";

  Serial.begin(115200);

  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("VILLAMIZAR", "T63284443");
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(300);
    Serial.print("Connecting to WiFi");
  }
  //while (WiFi.status() != WL_CONNECTED) {

  //delay(500);

  //Serial.println("Connecting to WiFi..");

  //}

  //Serial.println("Connected to the WiFi network");


  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
  server.begin();
}


void loop() {

  client = server.available();
  if (!client) { return; }
  while (!client.available()) { delay(1); }
  ClientRequest = (ReadIncomingRequest());
  ClientRequest.remove(0, 5);
  ClientRequest.remove(ClientRequest.length() - 9, 9);
  if (ClientRequest == "on") {
    digitalWrite(26, HIGH);
  }
  if (ClientRequest == "off") {
    digitalWrite(27, LOW);
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("OK");
  client.println("</html>");
  delay(1);
  client.flush();

}