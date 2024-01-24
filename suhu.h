#define       DHTPIN          13     // Digital pin connected to the DHT sensor
#define       DHTTYPE         DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

void suhu_setup() {
  dht.begin();
}

float suhu() {
  // Read temperature as Celsius
  float temperature_raw = dht.readTemperature();
  float temperature = konst_temp + (koef_reg_temp * temperature_raw);
  if (isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return 0;
  }
  return temperature;

}

float kelembaban() {
  // Read humidity as percentage
  float humidity_raw = dht.readHumidity();
  float humidity = konst_humi + (koef_reg_humi * humidity_raw);
  if (isnan(humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return 0;
  }
  return humidity;
}
