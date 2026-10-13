# Smart Cleaning Robot

An Arduino-based mobile cleaning robot prototype developed during a Robotistan internship. It combines wheeled movement, a fan-assisted debris collection mechanism, and ultrasonic obstacle detection.

![Smart cleaning robot prototype](images/robot-prototype.jpg)

## Project Overview

The goal is to build a low-cost robot that can move across a floor while collecting dust and small particles. A fan or vacuum motor provides the cleaning action, while drive motors move the robot. When the ultrasonic sensor detects an obstacle, the robot can stop, reverse, and turn before continuing.

The prototype demonstrates the integration of mobile robotics, motor control, and a basic cleaning mechanism using accessible components.

## How It Works

1. An Arduino controls the drive motors through a motor-driver circuit.
2. The robot moves forward while the fan or vacuum motor provides the cleaning action.
3. An HC-SR04 ultrasonic sensor measures the distance to nearby obstacles.
4. When an obstacle is closer than 20 cm, the robot stops briefly, reverses, turns right, and then resumes movement.

The drive system uses differential steering: the relative direction of the left and right wheels determines whether the robot moves straight or turns.

## Main Components

- Arduino microcontroller
- Motor-driver board
- DC gear motors and wheels
- Fan or vacuum motor for collecting debris
- Chassis and power source
- HC-SR04 ultrasonic distance sensor
- Servo motor for sensor positioning, if used in the build
- Jumper wires and supporting materials

![Wiring diagram](images/wiring-diagram.jpg)

*The wiring image is provided as a visual reference. Confirm pin assignments and power requirements against the actual build before wiring or powering the circuit.*

## Software

The Arduino sketch reads distance measurements from the HC-SR04 sensor and controls the drive motors. When the path is clear, the robot moves forward. When an obstacle is detected within 20 cm, it stops, reverses, and turns right.

### Arduino Code

```arduino
#define TRIG_PIN 6
#define ECHO_PIN 7
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

long duration;
int distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  distance = measureDistance();

  if (distance > 20) {
    moveForward();
  } else {
    stopRobot();
    delay(300);
    moveBackward();
    delay(500);
    turnRight();
    delay(400);
  }
}

int measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
```

The pin assignments above match the example code. Check the wiring and motor-driver type in the physical build before uploading the sketch.

## Possible Improvements

- Add a systematic coverage pattern to reduce missed areas.
- Add a mobile application for manual control.
- Add mapping and localization.
- Add a docking station for charging.
- Improve the debris collection mechanism and dust container.

## Project Files

- `images/robot-prototype.jpg` — photo of the assembled prototype
- `images/wiring-diagram.jpg` — wiring reference image

## Notes

This is an educational prototype. Cleaning performance and autonomous coverage depend on the final hardware, firmware, and testing conditions.
