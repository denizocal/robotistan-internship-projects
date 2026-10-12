import processing.serial.*;

Serial radarPort;
String serialData = "";
float angle = 0;
float distanceCm = 0;
int lastTrailTime = 0;
ArrayList<ObjectTrail> trails = new ArrayList<ObjectTrail>();

final String SERIAL_PORT = "COM5";  // Change this to the port used by your Arduino
final int SERIAL_BAUD = 9600;

void setup() {
  fullScreen();
  smooth();
  radarPort = new Serial(this, SERIAL_PORT, SERIAL_BAUD);
  radarPort.bufferUntil('.');
}

void draw() {
  fill(0, 15, 0, 80);
  noStroke();
  rect(0, 0, width, height);

  drawRadarGrid();
  drawRadarSweep();

  for (int i = trails.size() - 1; i >= 0; i--) {
    ObjectTrail trail = trails.get(i);
    trail.display();
    if (trail.isExpired()) trails.remove(i);
  }

  if (distanceCm > 0 && distanceCm < 40) {
    if (millis() - lastTrailTime > 1000) {
      trails.add(new ObjectTrail(angle, distanceCm));
      lastTrailTime = millis();
    }
  }

  drawStatus();
}

void drawRadarGrid() {
  stroke(0, 80, 0);
  strokeWeight(2);
  noFill();

  int centerX = width / 2;
  int baseline = height - 100;
  float radarRadius = height * 0.8;

  for (int r = 1; r <= 4; r++) {
    float radius = (radarRadius / 4) * r;
    arc(centerX, baseline, radius * 2, radius * 2, PI, TWO_PI);
  }
}

void drawRadarSweep() {
  stroke(30, 255, 30);
  strokeWeight(3);

  int centerX = width / 2;
  int baseline = height - 100;
  float radarRadius = height * 0.8;
  float radiansAngle = radians(angle);

  line(centerX, baseline,
       centerX - radarRadius * cos(radiansAngle),
       baseline - radarRadius * sin(radiansAngle));
}

void drawStatus() {
  fill(30, 255, 30);
  textSize(24);
  text("Angle: " + (int) angle, 50, 50);
  text("Distance: " + (int) distanceCm + " cm", 50, 90);
  text("Press ESC to exit", 50, 130);
}

void serialEvent(Serial port) {
  serialData = port.readStringUntil('.');
  if (serialData != null) {
    serialData = trim(serialData);
    int commaIndex = serialData.indexOf(',');
    if (commaIndex > 0) {
      angle = float(serialData.substring(0, commaIndex));
      distanceCm = float(serialData.substring(commaIndex + 1));
    }
  }
}

class ObjectTrail {
  float x;
  float y;
  float distanceCm;
  float opacity = 255;

  ObjectTrail(float angleDegrees, float distance) {
    float scale = (height * 0.8) / 40.0;
    float radiansAngle = radians(angleDegrees);
    x = (width / 2) - (distance * scale) * cos(radiansAngle);
    y = (height - 100) - (distance * scale) * sin(radiansAngle);
    distanceCm = distance;
  }

  void display() {
    stroke(255, 255, 0, opacity);
    strokeWeight(15);
    point(x, y);

    fill(255, 255, 255, opacity);
    textSize(18);
    text((int) distanceCm + " cm", x + 15, y - 15);
    opacity -= 2.1;
  }

  boolean isExpired() {
    return opacity <= 0;
  }
}
