#include <IRremote.h>
#define MAX_TIME 150
#define red 2
#define green 4
#define blue 5

IRrecv irrecv(8);
decode_results results;
long lastPressTime = 0;
int state = LOW;

int x;
int y = 255;

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void writ (int a,int b,int c) {
  if (a == 1) {
    analogWrite(red, y);
    }
    else {
      analogWrite(red, 0);
      }
  if (b == 1) {
    analogWrite(blue, y);
    }
    else {
      analogWrite(blue, 0);
      }
  if (c == 1) {
    analogWrite(green, y);
    }
    else {
      analogWrite(green, 0);
      }
  }

void loop() {
  if (x == 0) {
    writ(0,0,0);
    }
  if (x == 1) {
    writ(1,1,1);
    }
  if (x == 2) {
    writ(1,0,0);
    }
  if (x == 3) {
    writ(0,1,0);
    }
  if (x == 4) {
    writ(0,0,1);
    }
  if (x == 5) {
    x = 0;
    }
  if (irrecv.decode(&results)) {
    if (results.value == 0xA25D847B) {
      if (millis() - lastPressTime > MAX_TIME) {
        // It's been a while since the last press, so this
        // must be a new press.
        // Toggle the state
        x++;
      }
      lastPressTime = millis();
    }
    irrecv.resume(); // Receive the next value
  }
}
