//configuration for EMG
#define EMG1_PIN A0
int emgValue = 0;
char emgString[10];



//with ld3320
#include <LWiFi.h> // for Linkit
#include <PubSubClient.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <itoa.h>


//#define button1 2
int button=LED_BUILTIN;

// Update these with values suitable for your network.
//const char* ssid = "vito9580";
//const char* password = "v3877468";
const char* ssid = "Factory2_2.4G";
const char* password = "118factory2";

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

void callback(char* topic, byte* payload, unsigned int length) {
 // Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] ");
  int Command_counter = 0;
  String InData;
 char RcvChar;
 String data[10];

  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
     RcvChar =(char)payload[i];
    if(RcvChar==','||RcvChar=='\n')        //EX:P.10.5.0.10
        {
          data[Command_counter]=InData; 
          InData="";                     //InData 存入一組字串後clear
          Command_counter++;
        }else
        {
          InData += RcvChar;    //InData先後存入P=>10=>5=>0
          delay(10);
        }
  }
    //Serial.println(Command_counter);
  for (int i=0;i<Command_counter;i++)
  {
    //Serial.println(data[i]);
    if(data[i]=="ProjectorOFF")
    {
       //digitalWrite(button,LOW);
        Serial.write('Q');
        //Serial.println(data[i]);
    }else if(data[i]=="ProjectorON")
        //digitalWrite(button,HIGH);
        Serial.write('P');
        //Serial.println(data[i]);
  }
  //Serial.write('\n');
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

void setup() {
//  pinMode(button, OUTPUT);      // Initialize the BUILTIN_LED pin as an output
//  pinMode(button1, INPUT);     // Initialize the BUILTIN_LED pin as an output
  
//  Serial.begin(115200);
Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode (LED_BUILTIN, OUTPUT);
  pinMode (EMG1_PIN, OUTPUT);

}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
//     long now = millis();
//  if (now - lastMsg > 500) {
     
//    lastMsg = now; 
//    OUT_Topic="test";
//    if(digitalRead(button1)==LOW)
//    {
//      
//   
//    client.publish(OUT_Topic, "ON");
//    }
//    if (Serial.available())
//    {
//       
//      if(Serial.read()=='o')
//      {
//        client.publish(OUT_Topic,"o");
//        Serial.println("Message o sent");
//      }
//    }
//    }
emgValue = analogRead(EMG1_PIN);
Serial.println(emgValue);
//emgString = String(emgValue);
itoa(emgValue, emgString, 10);
client.publish("EMG",emgString);

}
