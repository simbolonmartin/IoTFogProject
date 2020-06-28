#include <LWiFi.h> // for Linkit
#include <PubSubClient.h>
//#include <stdio.h>
#include <stdlib.h>
#include <itoa.h>


// Update these with values suitable for your network.
const char* ssid = "Factory2_2.4G";
//const char* ssid = "vito9580";
const char* password = "118factory2";
//const char* password = "v3877468";
//const char* mqtt_server = "192.168.43.252";
//const char* mqtt_server = "192.168.43.109";
const char* mqtt_server = "192.168.50.99";


const char* OUT_Topic = "test";
const char* IN_Topic = "ESP02/#";
const char* q;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
float take_Ambient_Temp, take_Target_Temp;
char take_Target_Temp_Char[10];

int data[3];
int count = 0;
float _value;
bool recieve = false;
float temp;
char tempString[10];

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}


void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
    setup_wifi();
  client.setServer(mqtt_server, 1883);
//  client.setCallback(callback);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(OUT_Topic, "hello world from LinkitPRoject");
      // ... and resubscribe
      client.subscribe(IN_Topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  // read from port 1, send to port 0:
    if (!client.connected()) {
    reconnect();
  }
  client.loop();


  while (Serial1.available()) {
    int inByte = Serial1.read();

    if(inByte==83){
      recieve=true;
    }
    if(inByte==69){
      recieve=false;
//      Serial.println(_value);
//      temp = _value;
        Serial.println(_value);
        itoa(_value, tempString, 10);

       client.publish("Temp", tempString);

      count=0;
//      break;
    }

    if(recieve){
      data[count]=inByte;
      count++;
      _value=float(data[1]*256+data[2]);
    }    
  }

  // read from port 0, send to port 1:
  if (Serial.available()) {
    int inByte = Serial.read();
    Serial1.write(inByte);
  }
}
