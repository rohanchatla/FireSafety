#include <dht.h>
#define RED_LED_PIN 6
#define GREEN_LED_PIN 5
#define BUZZER_PIN 13
#define DHT_SENSOR_PIN 2
#define SMOKE_SENSOR_PIN A0
#define FLAME_SENSOR_PIN A2
#define SMOKE_THRESHOLD 100
#define TEMP_THRESHOLD 40
#define FLAME_THRESHOLD 300

dht DHT;
int chk_dht;

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);

  pinMode(SMOKE_SENSOR_PIN, INPUT);
  pinMode(FLAME_SENSOR_PIN, INPUT);
}

void sirenAlarm(int buzzer) {
  for (int hz = 440; hz < 1000; hz++) {
    tone(buzzer, hz, 50);
    delay(3);
  }

  for (int hz = 1000; hz > 440; hz--) {
    tone(buzzer, hz, 50);
    delay(3);
  }
}

void loop() {
  chk_dht = DHT.read11(DHT_SENSOR_PIN);

  Serial.println("Smoke Val: " + String(analogRead(SMOKE_SENSOR_PIN)) + ", Temperature: " + String(DHT.temperature) + ", Flame: " + String(analogRead(FLAME_SENSOR_PIN)));
  
  if (analogRead(SMOKE_SENSOR_PIN) > SMOKE_THRESHOLD || (DHT.temperature) > TEMP_THRESHOLD || analogRead(FLAME_SENSOR_PIN) < FLAME_THRESHOLD) {
    digitalWrite(RED_LED_PIN, HIGH);
    sirenAlarm(BUZZER_PIN);
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  } else {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    noTone(BUZZER_PIN);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
  delay(400);
}
