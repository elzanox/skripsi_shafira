const uint8_t SHARP_LED_PIN = 33;   // Sharp Dust/particle sensor Led Pin
const uint8_t SHARP_VO_PIN  = 32;    // Sharp Dust/particle analog out pin used for reading
const int dataSize = 10;
int dataBuffer[dataSize];
int dataIndex = 0;
GP2YDustSensor dustSensor(GP2YDustSensorType::GP2Y1010AU0F, SHARP_LED_PIN, SHARP_VO_PIN);

void pm10_setup() {
  dustSensor.begin();
  for (int i = 0; i < dataSize; i++) {
    dataBuffer[i] = 0;
  }
}

float debu() {
  float debu_raw = dustSensor.getDustDensity();
  // Memasukkan data baru ke dalam buffer
  dataBuffer[dataIndex] = debu_raw;

  // Menghitung rata-rata dari data di dalam buffer
  int sum = 0;
  for (int i = 0; i < dataSize; i++) {
    sum += dataBuffer[i];
  }
  float average = static_cast<float>(sum) / dataSize;

  // Pindah ke indeks berikutnya dalam buffer
  dataIndex = (dataIndex + 1) % dataSize;
//  Serial.println(average);
  float debu = konst_debu + (koef_reg_debu*average);
  return debu;
}

float debu_avg() {
  float debu_avg = dustSensor.getRunningAverage();
  //  Serial.println(debu_avg);
  return debu_avg;
}
