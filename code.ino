// incluindo bibliotecas
#include <WiFi.h>
#include <PubSubClient.h>

// acesso wifi
const char* ssid = ""; // sua net
const char* password = ""; // senha da sua net
const char* mqtt_server = "broker.hivemq.com"; // server mqtt

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
    Serial.println(" ");
    Serial.println("Wifi Connected.");
    
    Serial.println("IP Adress:");
    Serial.println(WiFi.localIP()); // mostra o endereço IP

  }
}

void reconnect_MQTT(){
  while(!client.connected()){ // enquanto o client não estiver conectado ao broker
    Serial.println("Trying to connect with broker...");

    if(client.connect("WOKWI_client")){ // tentando conectar-se usando o ID do wowki_client
      Serial.println("Connected!");
      //
      //
    }else{
      Serial.println("Couldn't connect to the broker. Reason: ");
      Serial.println(client.state()); // estado de conexão
      Serial.println("Trying to reconnect in 5 seconds...");
      delay(5000);
    }
  }
}

// função para indicar o status de conexão usando led no pino 15
void wifi_on(){
  if(WiFi.status()){
    digitalWrite(2, HIGH);
  }else{
    digitalWrite(2, LOW);
  }
}

// indica a conexão do wifi com led no pino 2
void broker_on(){
  if(client.connected()){
    digitalWrite(15, HIGH);
  }else{
    digitalWrite(15, LOW);
  }
}

void send_data(){ // envio de dados
  int value = analogRead(34);
  Serial.println(value);
  // publicando dados com o publish
  client.publish("fagundinho123", String(value).c_str());
  delay(1000);
}

void setup(){
  pinMode(2, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(34, INPUT);
  Serial.begin(115200); // inicia a comunicação serial em 115200bps
  connect_wifi(); // função para conectar ao wifi

  client.setServer(mqtt_server, 1883); // servidor mqtt e porta (padrão 1883)

}

void loop(){
  client.loop();
  reconnect_MQTT(); // mantém ativa a conexão MQTT

  send_data();

  wifi_on();
  broker_on();
}
