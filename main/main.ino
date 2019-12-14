//#include <Keypad.h>
//#include <NewPing.h>

const byte ROWS = 4;
const byte COLS = 3;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};

//Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int enable_left = 11;
int enable_right = 10;

int direction_left1 = 6;
int direction_left2 = 7;

int direction_right1 = 2;
int direction_right2 = 3;

int leftPin = A0;

int echoPinL = 13;
int trigPinL = 12;

int echoPinF = 9;
int trigPinF = 8;

int echoPinR = 5;
int trigPinR = 4;

const int MAX_DISTANCE = 350;

long duration, cm, start, ending;

//NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

int left_distance;
int front_distance;
int right_distance;
int old_distance = -1;
bool follow_left = false;

void setup() {
  Serial.begin(9600);
  pinMode(direction_left1, OUTPUT);
  pinMode(direction_left2, OUTPUT);
  pinMode(direction_right1, OUTPUT);
  pinMode(direction_right2, OUTPUT);

}

void loop() {

  right_distance = detect_right();
  Serial.print("right: ");
  Serial.print(right_distance);
  Serial.println("cm");
  delay(3000);
  //  rbt_stop();
  //  delay(500);
  //  if (follow_left) {
  //    left_distance = detect_left();
  //    Serial.print("left: ");
  //    Serial.print(left_distance);
  //    Serial.print("cm");
  //    Serial.println();
  //    front_distance = detect_front();
  //    Serial.print("front: ");
  //    Serial.print(front_distance);
  //    Serial.println("cm");
  //
  //    if (front_distance <= 15) {
  //      rbt_stop();
  //      delay(1000);
  //      rbt_backwards(200, 200);
  //      delay(250);
  //      turn_right();
  //      rbt_stop();
  //      delay(500);
  //      while (detect_left() > 40) {
  //        rbt_forward(220, 220);
  //        delay(250);
  //        rbt_stop();
  //      }
  //      delay(1000);
  //      rbt_stop();
  //    }
  //
  //    //  // Situation 3: Robot is driving towards wall.
  //    //  // DETECT: distance is getting closer to a MIN threshold
  //    //  // -> what to do?
  //    //  // add more power on the left side
  //    if (left_distance < 8) {
  //      Serial.println("go right");
  //      rbt_stop();
  //      delay(1000);
  //      rbt_forward(220, 200);
  //      delay(250);
  //    }
  //
  //    // Situation 1: Robot is following the wall.
  //    // DETECT: distances remain below a MAX threshold
  //    // -> what to do?
  //    // keep going straight
  //    if ((left_distance >= 8) && (left_distance < 20)) {
  //      Serial.println("go straight");
  //      rbt_forward(220, 220);
  //      delay(500);
  //    }
  //
  //    // Situation 4: Robot is at corner
  //    // DETECT: front and left distances
  //    // -> what to do?
  //    // turn left
  //    //   if ((left_distance >= 8) && (left_distance < 10) && (front_distance < 8)) {
  //    //    turn_left();
  //    //   }
  //
  //    // Situation 2: Robot is driving away from wall.
  //    // DETECT: distance are above a MAX threshold
  //    // -> what to do?
  //    // add more power on the right side
  //    if ((left_distance >= 20) && (left_distance <= 35)) {
  //      Serial.println("go left");
  //      rbt_stop();
  //      delay(1000);
  //      rbt_forward(200, 240);
  //      delay(250);
  //    }
  //
  //    // Situation 5: There is no more wall
  //    // DETECT: big change in distances of left sensor
  //    // -> what to do?
  //    // turn left
  //
  //    if (left_distance > 35) {
  //      Serial.println("turning left");
  //      rbt_stop();
  //      delay(1000);
  //      rbt_backwards(200, 200);
  //      delay(250);
  //      turn_left();
  //      rbt_stop();
  //      delay(500);
  //      while (detect_left() > 40) {
  //        rbt_forward(220, 220);
  //        delay(250);
  //        rbt_stop();
  //      }
  //      delay(1000);
  //      rbt_stop();
  //    }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //  } else {
  //    front_distance = detect_front();
  //    Serial.print("front: ");
  //    Serial.print(front_distance);
  //    Serial.println("cm");
  //    right_distance = detect_right();
  //    Serial.print("right: ");
  //    Serial.print(right_distance);
  //    Serial.println("cm");
  //    if (front_distance <= 15) {
  //      rbt_stop();
  //      delay(1000);
  //      rbt_backwards(200, 200);
  //      delay(250);
  //      turn_left();
  //      rbt_stop();
  //      delay(500);
  //      while (dectect_right() > 40) {
  //        rbt_forward(220, 220);
  //        delay(250);
  //        rbt_stop();
  //      }
  //      delay(1000);
  //      rbt_stop();
  //    }
  //
  //    //  // Situation 3: Robot is driving towards wall.
  //    //  // DETECT: distance is getting closer to a MIN threshold
  //    //  // -> what to do?
  //    //  // add more power on the left side
  //    if (right_distance < 8) {
  //      Serial.println("go right");
  //      rbt_stop();
  //      delay(1000);
  //      rbt_forward(220, 200);
  //      delay(250);
  //    }
  //
  //    // Situation 1: Robot is following the wall.
  //    // DETECT: distances remain below a MAX threshold
  //    // -> what to do?
  //    // keep going straight
  //    if ((right_distance >= 8) && (right_distance < 20)) {
  //      Serial.println("go straight");
  //      rbt_forward(220, 220);
  //      delay(500);
  //    }
  //
  //    // Situation 4: Robot is at corner
  //    // DETECT: front and left distances
  //    // -> what to do?
  //    // turn left
  //    //   if ((left_distance >= 8) && (left_distance < 10) && (front_distance < 8)) {
  //    //    turn_left();
  //    //   }
  //
  //    // Situation 2: Robot is driving away from wall.
  //    // DETECT: distance are above a MAX threshold
  //    // -> what to do?
  //    // add more power on the right side
  //    if ((right_distance >= 20) && (right_distance <= 35)) {
  //      Serial.println("go left");
  //      rbt_stop();
  //      delay(1000);
  //      rbt_forward(200, 240);
  //      delay(250);
  //    }
  //
  //    // Situation 5: There is no more wall
  //    // DETECT: big change in distances of left sensor
  //    // -> what to do?
  //    // turn left
  //
  //    if (right_distance > 35) {
  //      Serial.println("turning left");
  //      rbt_stop();
  //      delay(1000);
  //      rbt_backwards(200, 200);
  //      delay(250);
  //      turn_right();
  //      rbt_stop();
  //      delay(500);
  //      while (detect_right() > 40) {
  //        rbt_forward(220, 220);
  //        delay(250);
  //        rbt_stop();
  //      }
  //      delay(1000);
  //      rbt_stop();
  //    }
  //  }

  ////
  ////  // BELOW USES FRONT SENSOR
  ////
  ////  // Situation 4: The robot is at a corner
  ////  // DETECT: left and front sensor show short distance
  ////  // -> what to do?
  ////  // Turn right
  ////  // a) if front sensor is OFF, follow wall
  ////  // a) if front sensor is ON, turn right again

}

// Situation 6: There is an obstacle we need to pass
// DETECT:



int detect_front() {
  int cm = 0;
  for (int i = 0; i < 15; i++) {
    pinMode(trigPinF, OUTPUT);
    digitalWrite(trigPinF, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinF, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinF, LOW);
    pinMode(echoPinF, INPUT);
    duration = pulseIn(echoPinF, HIGH);
    // convert the time into a distance
    cm += microsecondsToCentimeters(duration);
  }
  return cm / 15;
}

int detect_left() {

  int cm = 0;
  for (int i = 0; i < 10; i++) {
    pinMode(trigPinL, OUTPUT);
    digitalWrite(trigPinL, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinL, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinL, LOW);
    pinMode(echoPinL, INPUT);
    duration = pulseIn(echoPinL, HIGH);
    Serial.println(duration);
    // convert the time into a distance
    cm += microsecondsToCentimeters(duration);
  }
  return cm / 10;
}

int detect_right() {

  int cm = 0;
  for (int i = 0; i < 15; i++) {
    pinMode(trigPinR, OUTPUT);
    digitalWrite(trigPinR, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinR, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPinR, LOW);
    pinMode(echoPinR, INPUT);
    duration = pulseIn(echoPinR, HIGH);
    Serial.println(duration);
    // convert the time into a distance
    cm += microsecondsToCentimeters(duration);
  }
  return cm / 15;
}

double microsecondsToInches(double microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

void rbt_move() {

  digitalWrite(direction_left1, HIGH);
  digitalWrite(direction_left2, LOW);
  digitalWrite(direction_right1, LOW);
  digitalWrite(direction_right2, HIGH);
}

void rbt_backwards_move() {

  digitalWrite(direction_left1, LOW);
  digitalWrite(direction_left2, HIGH);
  digitalWrite(direction_right1, HIGH);
  digitalWrite(direction_right2, LOW);
}

void rbt_stop() {
  digitalWrite(direction_left1, LOW);
  digitalWrite(direction_left2, LOW);
  digitalWrite(direction_right1, LOW);
  digitalWrite(direction_right2, LOW);
  analogWrite(enable_left, 0);
  analogWrite(enable_right, 0);
}


void rbt_backwards(int left_value, int right_value) {
  rbt_backwards_move();
  analogWrite(enable_left, left_value);
  analogWrite(enable_right, right_value);
}

void rbt_forward(int left_value, int right_value) {
  rbt_move();
  analogWrite(enable_left, left_value);
  analogWrite(enable_right, right_value);
}

void turn_right() {
  rbt_move();
  analogWrite(enable_left, 255);
  analogWrite(enable_right, 0);
  delay(2080);
}

void turn_left() {
  rbt_move();
  analogWrite(enable_right, 255);
  analogWrite(enable_left, 0);
  delay(2080);
}
