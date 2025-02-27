#define BLYNK_TEMPLATE_ID "TMPL34BTEaEQF"       // Replace with your Blynk Template ID
#define BLYNK_TEMPLATE_NAME "Smart HealthKit" // Replace with your Blynk Template Name
#define BLYNK_AUTH_TOKEN "BzCQHvDDabeO0MWaEzbtk8X3TXuBgDSQ"     // Replace with your Blynk Authentication Token
#define BLYNK_PRINT Serial
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <SPIFFS.h>

// Wi-Fi Credentials
const char* ssid = "POCO_F4";
const char* pass = "Dhruv0825";


// DS18B20 Configuration
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Pulse Sensor Configuration
#define PulseSensorPin 34
#define LED_BUILTIN 2
int signalValue = 0;
int threshold = 1800;
unsigned long lastBeatTime = 0;
unsigned long currentTime = 0;
int beatInterval = 0;
int bpm = 0;
bool pulseDetected = false;

// Signal Smoothing Configuration
#define SAMPLE_SIZE 10
int signalValues[SAMPLE_SIZE];
int currentIndex = 0;

// Timing for temperature updates
unsigned long lastTempTime = 0;
const unsigned long tempInterval = 1000;

// Blynk Timer
BlynkTimer timer;

// File Path
const char* csvPath = "/health_data.csv";

// Function to calculate the average of the last SAMPLE_SIZE readings
int getAverageSignal() {
  int sum = 0;
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    sum += signalValues[i];
  }
  return sum / SAMPLE_SIZE;
}

// Save data to CSV file
void saveDataToCSV(float temperature, int bpm) {
  File file = SPIFFS.open(csvPath, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open CSV file for writing.");
    return;
  }

  String data = String(temperature) + "," + String(bpm) + "," + String(millis()) + "\n";
  file.print(data);
  file.close();
  Serial.println("Data saved to CSV: " + data);
}

// Function to send data to Blynk
void sendDataToBlynk() {
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  // Send to Blynk Virtual Pins
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V3, bpm);

  // Save data to CSV
  saveDataToCSV(temperature, bpm);

  // Print to Serial
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("BPM: ");
  Serial.println(bpm);
}

void setup() {
  // Initialize Serial
  Serial.begin(115200);

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  // Initialize Wi-Fi and Blynk
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Initialize DS18B20 sensor
  sensors.begin();

  // Configure pins
  pinMode(PulseSensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize Signal Smoothing Array
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    signalValues[i] = 0;
  }

  // Timer to send data every 5 seconds
  timer.setInterval(5000L, sendDataToBlynk);

  // Initialize CSV file
  File file = SPIFFS.open(csvPath, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to create CSV file.");
  } else {
    file.println("Temperature(BPM),BPM,Time(ms)");
    file.close();
    Serial.println("CSV file initialized.");
  }
}

void loop() {
  Blynk.run();
  timer.run();

  currentTime = millis();

  // Read and smooth the pulse sensor signal
  signalValues[currentIndex] = analogRead(PulseSensorPin);
  currentIndex = (currentIndex + 1) % SAMPLE_SIZE;
  signalValue = getAverageSignal();

  // Detect a heartbeat
  if (signalValue > threshold && !pulseDetected) {
    if (currentTime - lastBeatTime > 300) {
      pulseDetected = true;
      digitalWrite(LED_BUILTIN, HIGH);

      // Calculate BPM
      beatInterval = currentTime - lastBeatTime;
      bpm = 60000 / beatInterval;

      if (bpm > 40 && bpm < 200) {
        Serial.print("Heartbeat detected! BPM: ");
        Serial.println(bpm);
      } else {
        Serial.println("Invalid BPM reading, ignored.");
      }

      lastBeatTime = currentTime;
    }
  }

  // Reset pulse detection
  if (signalValue < threshold && pulseDetected) {
    pulseDetected = false;
    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(20);
}