#include <ESP8266WiFi.h>
#include <PubSubClient.h>



// Update these with values suitable for your network.
#include <dht.h>
dht DHT;

// if you require to change the pin number, Edit the pin with your arduino pin.

#define DHT11_PIN 16


const char* ssid = ".....";
const char* password = "......";
//const char* mqtt_server = "broker.mqttdashboard.com";
const char* mqtt_server = "m12.cloudmqtt.com";  //  client.connect ("id", "user" , "pass")


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[300];
int value = 0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  
  setup_wifi();
  //client.setServer(mqtt_server, 1883);
  client.setServer(mqtt_server, 19757);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("You're connected");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client", "UserId", "Password")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

String getTime() {
  WiFiClient client;
  while (!!!client.connect("google.com", 80)) {
    Serial.println("connection failed, retrying...");
  }

  client.print("HEAD / HTTP/1.1\r\n\r\n");
 
  while(!!!client.available()) {
     yield();
  }

  while(client.available()){
    if (client.read() == '\n') {
      if (client.read() == 'D') {   
        if (client.read() == 'a') {  
          if (client.read() == 't') {   
            if (client.read() == 'e') {   
              if (client.read() == ':') {   
                client.read();
                String theDate = client.readStringUntil('\r');
                client.stop();
                return theDate;
              }
            }
          }
        }
      }
    }
  }
}


void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    int chk = DHT.read11(DHT11_PIN); 
    
    //old code snprintf (msg, 75, "Temperature is %d", (int) DHT.temperature);    
    //char str[200] = "{\"Date\": \"01-Jan-2018 21:50:06:387978\", \"Sensor_ID\": \"Dummy-2\", \"Temperature\":  ";
    
    char datestr[50]; 
    String getTimeArr = getTime();
    getTimeArr.toCharArray ( datestr, 50);   
    
    char str[200] = "\"Sensor_ID\": \"Dummy-2\", \"Temperature\":  ";
    
    snprintf (msg, 250, "{\"Date\":  \"%s\", %s \"%d\" }", datestr, str, (int) DHT.temperature);
    
    // If you want both the T and H, uncomment the line below with some light modifications.  
    //snprintf (msg, 75, "Temperature is #%d, Humidity is %d", DHT.temperature, DHT.humidity);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("TempTopic/Temperature", msg);
  }
}
