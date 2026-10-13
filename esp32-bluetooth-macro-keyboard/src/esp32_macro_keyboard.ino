#include <BleKeyboard.h>

// The name shown in the computer's Bluetooth device list
BleKeyboard bleKeyboard("Robotistan Macro", "Maker", 100);

// Button pins and their keyboard shortcuts
const int button1Pin = 13; // Ctrl + Alt + J
const int button2Pin = 12; // Ctrl + Alt + K
const int button3Pin = 14; // Ctrl + Alt + L

void setup() {
  Serial.begin(115200);

  // The buttons use the ESP32's internal pull-up resistors
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);

  bleKeyboard.begin();
  Serial.println("Macro keyboard ready. Waiting for a Bluetooth connection...");
}

void loop() {
  // Read buttons only while the keyboard is connected
  if (bleKeyboard.isConnected()) {
    // Button 1: Ctrl + Alt + J
    if (digitalRead(button1Pin) == LOW) {
      Serial.println("Button 1 pressed.");
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.press('j');
      delay(100);
      bleKeyboard.releaseAll();

      // Wait for release so one press sends only one shortcut
      while (digitalRead(button1Pin) == LOW) {
        delay(10);
      }
    }

    // Button 2: Ctrl + Alt + K
    if (digitalRead(button2Pin) == LOW) {
      Serial.println("Button 2 pressed.");
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.press('k');
      delay(100);
      bleKeyboard.releaseAll();

      while (digitalRead(button2Pin) == LOW) {
        delay(10);
      }
    }

    // Button 3: Ctrl + Alt + L
    if (digitalRead(button3Pin) == LOW) {
      Serial.println("Button 3 pressed.");
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.press('l');
      delay(100);
      bleKeyboard.releaseAll();

      while (digitalRead(button3Pin) == LOW) {
        delay(10);
      }
    }
  }
}
