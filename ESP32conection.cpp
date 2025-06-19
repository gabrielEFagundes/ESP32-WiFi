// incluindo bibliotecas
#include <WiFi.h>
#include <PubSubClient.h>

// acesso wifi
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "test.mosquitto.org"; // server mqtt

// "objetos"
WiFiClient WOKWI_client; // cria um objeto cliente wifi para comunicação
PubSubClient client(WOKWI_client); // veio da classe pubsub

// conectar no WiFi
void connect_wifi(){

  delay(10);
  //
  //
  //
  // define o modo do wifi como cliente (ou seja, não cria um ponto de acesso)
  WiFi.mode(WIFI_STA);
  // inicia a conexão com as credênciais no monitor serial
  WiFi.begin(ssid, password);

  // loop para verificar a conexão até ela ser estabelecida
  while(WiFi.status() != WL_CONNECTED){

    delay(50);
    Serial.print(".");
    //
    //
    //
    //
    Serial.println(WiFi.localIP()); // mostra o endereço IP

  }
}

void setup(){
  Serial.begin(115200);
  setup_wifi();
}

void loop(){
  
}