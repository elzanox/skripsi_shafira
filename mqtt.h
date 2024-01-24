// Replace the next variables with your SSID/Password combination
const char* ssid      = "*&^%$#@!";
const char* password  = "87654321";

// Replace the next variables with your SSID/Password combination
//const char* ssid      = "Tselhome-B571";
//const char* password  = "81968016";
//// Replace the next variables with your SSID/Password combination
//const char* ssid      = "SYAMTA";
//const char* password  = "abcd1234";
//
//// Replace the next variables with your SSID/Password combination
//const char* ssid      = "JAMBAN";
//const char* password  = "J4MB4N11";

// Replace with your MQTT broker's IP address
const char* mqtt_server = "dimasalifta.tech";
long lastMsg = 0;
WiFiClient espClient;
PubSubClient client(espClient);


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Message received:");
  Serial.print("Topic: ");
  Serial.println(topic);

  Serial.print("Payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("Connected to MQTT");
      client.subscribe("skripsi_shafira");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}


double conv2do(double value) {
  return (int)(value * 100 + 0.5) / 100.0;
}


void publish_to_broker(float temp, float humi, float dust, float co, int Interval) {
  //  double pii = 3.14;

  long now = millis();
  if (now - lastMsg > Interval) {
    lastMsg = now;
    //    Serial.print(temp);
    //    Serial.print("\t");
    //    Serial.print(humi);
    //    Serial.print("\t");
    //    Serial.print(dust);
    //    Serial.println("\t");
    //    Serial.println("satu menit");
    // Create a JSON object
    StaticJsonDocument<200> jsonDocument;
    jsonDocument["temp"] = conv2do(temp);
    jsonDocument["humi"] = conv2do(humi);
    jsonDocument["dust"] = conv2do(dust);
    jsonDocument["co"] = conv2do(co);

    char jsonBuffer[256];
    serializeJson(jsonDocument, jsonBuffer);

    // Publish the JSON data to MQTT topic
    client.publish("skripsi_shafira", jsonBuffer);
  }
}

void mqtt_setup() {
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Set the MQTT server and callback function
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
