#include <Servo.h>

const int sensorPin = A0;
const int greenLED = 6;
const int redLED = 7;
const int buzzer = 8;
const int servoPin = 9;

Servo gateServo;

bool gateOpen = false;

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  gateServo.attach(servoPin);
  gateServo.write(0);   // Closed position

  Serial.begin(9600);
}

void loop() {

  // Average 10 readings
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(sensorPin);
    delay(10);
  }

  int waterLevel = sum / 10;

  Serial.print("Water Level: ");
  Serial.println(waterLevel);

  if (waterLevel >= 500) {

    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);

    // Only trigger once
    if (!gateOpen) {

      // 3-second warning sound
      for (int i = 0; i < 6; i++) {
        tone(buzzer, 1000);   // 1000 Hz
        delay(250);
        noTone(buzzer);
        delay(250);
      }

      // Slowly open servo
      for (int angle = 0; angle <= 90; angle++) {
        gateServo.write(angle);
        delay(20);
      }

      gateOpen = true;
    }

  } else {

    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);

    noTone(buzzer);

    // Close servo only once
    if (gateOpen) {

      for (int angle = 90; angle >= 0; angle--) {
        gateServo.write(angle);
        delay(20);
      }

      gateOpen = false;
    }
  }

  delay(200);
}