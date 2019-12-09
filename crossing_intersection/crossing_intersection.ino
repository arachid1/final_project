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
int L = 1;
int R = 2;
int leftPin = A0;

int echoPinL = 13;
int trigPinL = 12;

int echoPinF = 11;
int trigPinF = 10;
const int MAX_DISTANCE = 350;

long duration, cm, start, ending;

//NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

int left_distance;
int front_distance;
int old_distance = -1;
bool deactivated = false;

void setup() {
  Serial.begin(9600);
  pinMode(L, OUTPUT);
  pinMode(R, OUTPUT);
}

void loop() {
  rbt_forward(200,200);
  for (int i = 0; i < 3; i++) {
    Serial.println("iteration");
    rbt_forward(220, 220);
    delay(1000);
    left_distance = detect_left();
    if (left_distance < 15) {
      Serial.println("here");
      rbt_stop();
    }
    rbt_stop();
    delay(1500);
  }
  exit(0);
  // BELOW USES FRONT SENSOR

  // Situation 4: The robot is at a corner
  // DETECT: left and front sensor show short distance
  // -> what to do?
  // Turn right
  // a) if front sensor is OFF, follow wall
  // a) if front sensor is ON, turn right again



  // Situation 6: There is an obstacle we need to pass
  // DETECT:

}

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
  delay(200);
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
    // convert the time into a distance
    cm += microsecondsToCentimeters(duration);
  }
  delay(200);
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

  digitalWrite(R, LOW);
  digitalWrite(L, HIGH);
}

void rbt_stop() {
  digitalWrite(L, HIGH);
  digitalWrite(R, HIGH);
}

void rbt_forward(int left_value, int right_value) {
  rbt_move();
  delay(250);
  analogWrite(enable_left, left_value);
  // delay(1400);
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

void rbt_wall_search(int left_value, int right_value) {
  rbt_forward(255, 255);
  rbt_stop();
}
