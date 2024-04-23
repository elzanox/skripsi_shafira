#include <WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include <GP2YDustSensor.h>
#include <MQUnifiedsensor.h>
#include <ArduinoJson.h>
#include "time.h"
#include <stdlib.h>
#include "DHT.h"
#include "variabel_regresi.h"
#include "mqtt.h"
#include "lcd.h"
#include "suhu.h"
#include "pm10.h"
#include "gas_co.h"

void setup() {
  Serial.begin(115200);
  mqtt_setup();
  lcd_setup();
  suhu_setup();
  pm10_setup();
  co_setup();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  lcd_print(suhu(), kelembaban(), debu(), co());
  publish_to_broker(suhu(), kelembaban(), debu(), co(), 1000);
}
