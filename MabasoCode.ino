// ============================================================
// Blynk Template Info
#define BLYNK_TEMPLATE_ID   "TMPL2qI5Tgkvs"
#define BLYNK_TEMPLATE_NAME "SmartHome v2"
#define BLYNK_AUTH_TOKEN    "d1pZL-uxliLyvdux_6B3dAtxDF8z_ICd"
// ============================================================
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char ssid[] = "Hidden Network";
char pass[] = "Aa1234567890";

#define DHTPIN 16
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int ledPin = 2;
const int fanPin = 27;
int fanSpeed = 0;

BlynkTimer timer;

// -----------------------------
// Blynk handlers
// -----------------------------
BLYNK_WRITE(V2) {
  int val = param.asInt();
  digitalWrite(ledPin, val);
  Serial.print("LED set to: ");
  Serial.println(val ? "ON" : "OFF");
}

BLYNK_WRITE(V3) {
  int sliderValue = param.asInt();  // 0–100 from Blynk
  fanSpeed = map(sliderValue, 0, 100, 0, 255);  // Convert to 0-255
  
  ledcWrite(fanPin, fanSpeed);
  
  Serial.print("Slider: "); 
  Serial.print(sliderValue);
  Serial.print("% -> PWM: "); 
  Serial.println(fanSpeed);
  Serial.print("PWM Duty Cycle: ");
  Serial.print((fanSpeed * 100) / 255);
  Serial.println("%");

  Blynk.virtualWrite(V4, sliderValue);  // Send back the percentage
}

void sendSensorData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Temp: "); 
  Serial.print(t);
  Serial.print(" °C, Humidity: "); 
  Serial.print(h);
  Serial.println(" %");

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}

// Test function - runs fan through speeds on startup
void testFan() {
  Serial.println("\n=== FAN TEST START ===");
  
  Serial.println("Fan OFF (0%)");
  ledcWrite(fanPin, 0);
  delay(2000);
  
  Serial.println("Fan 25% speed");
  ledcWrite(fanPin, 64);
  delay(3000);
  
  Serial.println("Fan 50% speed");
  ledcWrite(fanPin, 128);
  delay(3000);
  
  Serial.println("Fan 75% speed");
  ledcWrite(fanPin, 191);
  delay(3000);
  
  Serial.println("Fan 100% speed");
  ledcWrite(fanPin, 255);
  delay(3000);
  
  Serial.println("Fan OFF");
  ledcWrite(fanPin, 0);
  
  Serial.println("=== FAN TEST COMPLETE ===\n");
}

// -----------------------------
// Setup & Loop
// -----------------------------
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\n=== Starting SmartHome v2 ===");
  
  dht.begin();

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Setup fan pin
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW);

  // New PWM setup
  Serial.println("Configuring PWM for fan control...");
  ledcAttach(fanPin, 5000, 8);  // 5kHz, 8-bit resolution
  ledcWrite(fanPin, 0);
  Serial.println("PWM configured on pin 27");

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Connected to Blynk!");
  
  timer.setInterval(5000L, sendSensorData);
  
  // Run fan test after 3 seconds
  delay(3000);
  testFan();
}

void loop() {
  Blynk.run();
  timer.run();
}