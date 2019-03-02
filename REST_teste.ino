#include "WiFi.h"
#include "aREST.h"

aREST rest = aREST();

WiFiServer server(80);

const char* ssid = "Giovini";
const char* password = "navi2517";

int testFunction(String command){
  Serial.println("Request REST recebido");
}

void setup() {
  Serial.begin(115200);
  rest.function("test", testFunction);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(450);
    Serial.print(".");
  }

  Serial.println("WiFi conectado com IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client){
    while (!client.available()){
      delay(5);
    }
    rest.handle(client);
  }

}
