#include <Mouse.h>

const int X_PIN = A0;
const int Y_PIN = A1;
const int SWITCH_PIN = 2;

const int DEADZONE = 10;  // Ignore small movements to prevent drift
const int SENSITIVITY = 6
; // Adjust movement speed

bool drawing = false;  
bool lastButtonState = HIGH;  

void setup() {
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    Mouse.begin();
}

void loop() {
    int xValue = analogRead(Y_PIN);
    int yValue = analogRead(X_PIN);
    int buttonState = digitalRead(SWITCH_PIN);

    // Center the joystick (adjust if needed)
    int centerX = 512;
    int centerY = 512;

    // Calculate movement
    int moveX = centerX - xValue;  // Invert X-axis
    int moveY = yValue - centerY;  // Keep Y-axis normal

    // Apply deadzone to prevent unwanted drift
    if (abs(moveX) < DEADZONE) moveX = 0;
    if (abs(moveY) < DEADZONE) moveY = 0;

    // Scale movement
    moveX = map(moveX, -512, 512, -SENSITIVITY, SENSITIVITY);
    moveY = map(moveY, -512, 512, -SENSITIVITY, SENSITIVITY);

    // Move cursor if joystick is outside deadzone
    if (moveX != 0 || moveY != 0) {
        Mouse.move(moveX, moveY);
    }

    // Toggle drawing mode on button press
    if (buttonState == LOW && lastButtonState == HIGH) {
        drawing = !drawing;  

        if (drawing) {
            Mouse.press(MOUSE_LEFT);  // Start drawing immediately on press
        } else {
            Mouse.release(MOUSE_LEFT);  // Release mouse when button is pressed again
        }

        delay(200); // Debounce delay to avoid accidental toggles
    }

    lastButtonState = buttonState;

    delay(10);  // Smooth movement
}
