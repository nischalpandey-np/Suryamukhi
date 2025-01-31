#include <Servo.h>

// Servo objects
Servo baseServo;       // 360-degree servo for base rotation
Servo tiltServo;      // 180-degree servo for tilt rotation
Servo panelServo1;    // Solar panel servo 1
Servo panelServo2;    // Solar panel servo 2
Servo panelServo3;    // Solar panel servo 3

// LDR pin connections
int ldrlt = A5; // LDR top left
int ldrrt = A4; // LDR top right
int ldrld = A3; // LDR down left
int ldrrd = A2; // LDR down right
int ldrctr = A1; // LDR center

// Variables for light detection
int tol = 90; // Tolerance for light difference
int dtime = 10; // Delay time
const int thr = 550;

// Initial and Final positions of solar panel servo
int panelServo1_initial= 50, panelServo1_final= 100;
int panelServo2_initial= 65, panelServo2_final= 100;
int panelServo3_initial= 110, panelServo3_final= 70;

void setup() {
  // Attach servos to pins
  baseServo.attach(11);      // Base servo on pin 11
  tiltServo.attach(8);      // Tilt servo on pin 8
  panelServo1.attach(2);    // Solar panel servo1 in pin 2
  panelServo2.attach(3);    // Solar panel servo2 in pin 3
  panelServo3.attach(4);    // Solar panel servo3 in pin 4

  //Defining initial position of panel servo
  panelServo1.write(panelServo1_initial);
  panelServo2.write(panelServo2_initial);
  panelServo3.write(panelServo3_initial);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read LDR values
  int lt = analogRead(ldrlt); // Top left
  int rt = analogRead(ldrrt); // Top right
  int ld = analogRead(ldrld); // Down left
  int rd = analogRead(ldrrd); // Down right
  int ct = analogRead(ldrctr); // Center

  if(ct > thr || lt > thr || rt > thr || ld > thr || rd > thr)
  {
    panelServo1.write(panelServo1_final);
    panelServo2.write(panelServo2_final);
    panelServo3.write(panelServo3_final);
  }

  // Calculate average light intensity
  int avt = (lt + rt) / 2; // Average top
  int avd = (ld + rd) / 2; // Average down
  int avl = (lt + ld) / 2; // Average left
  int avr = (rt + rd) / 2; // Average right

  // Calculate differences
  int dvert = avt - avd; // Difference between top and bottom
  int dhoriz = avl - avr; // Difference between left and right

  // Base servo rotation logic
  if (abs(dhoriz) > tol) {
    if (avl > avr) {
      // Rotate base servo counterclockwise
      baseServo.write(0); // Adjust this value for counterclockwise rotation
    } else {
      // Rotate base servo clockwise
      baseServo.write(180); // Adjust this value for clockwise rotation
    }
  } else {
    // Stop base servo
    baseServo.write(90); // Adjust this value to stop the servo
  }
;
  // Tilt servo rotation logic
  if (abs(dvert) > tol) {
    if (avt > avd) {
      // Rotate tilt servo up
      tiltServo.write(50);
    } else {
      // Rotate tilt servo down
      tiltServo.write(0);
    }
  }

  // Add a small delay for stability
  delay(dtime);
}
