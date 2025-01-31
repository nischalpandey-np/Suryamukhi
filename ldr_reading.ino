#include <Servo.h>

// LDR sensor pins
int ldrTopLeft = A5, ldrTopRight = A4, ldrBottomLeft = A3, ldrBottomRight = A2, centralLDR = A1;

void setup() {
  Serial.begin(9600);
 
}

void loop() {
  // Read LDR values
  int topLeft = analogRead(ldrTopLeft);
  int topRight = analogRead(ldrTopRight);
  int bottomLeft = analogRead(ldrBottomLeft);
  int bottomRight = analogRead(ldrBottomRight);
  int central = analogRead(centralLDR);

  Serial.println("=== LDR Readings ===");
  Serial.print("Top Left: "); Serial.println(topLeft);
  Serial.print("Top Right: "); Serial.println(topRight);
  Serial.print("Bottom Left: "); Serial.println(bottomLeft);
  Serial.print("Bottom Right: "); Serial.println(bottomRight);
  Serial.print("Central: "); Serial.println(central);
  Serial.println("====================");
  delay(2000);

  }
