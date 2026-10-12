#include <Servo.h>

const int TRIG_PIN = 10;
const int ECHO_PIN = 11;
const int SERVO_PIN = 9;

Servo radarServo;
int angle = 0;
int distanceCm = 0;

int measureDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int cm = duration * 0.034 / 2;
  return cm;
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  radarServo.attach(SERVO_PIN);
}

void loop() {
  for (angle = 0; angle <= 180; angle += 2) {
    radarServo.write(angle);
    delay(30);
    distanceCm = measureDistanceCm();
    Serial.print(angle);
    Serial.print(',');
    Serial.print(distanceCm);
    Serial.print('.');
  }

  for (angle = 180; angle >= 0; angle -= 2) {
    radarServo.write(angle);
    delay(30);
    distanceCm = measureDistanceCm();
    Serial.print(angle);
    Serial.print(',');
    Serial.print(distanceCm);
    Serial.print('.');
  }
}
