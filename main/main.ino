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

int old_distance = -1;

//Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int enable_left = 11;
int enable_right = 10;
int L = 1;
int R = 2;
int leftPin = A0;

int echoPin = 13;
int trigPin = 12;
const int MAX_DISTANCE = 350;

long duration, cm, start, ending;

//NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

//float duration, distance;

void setup() {
  Serial.begin(9600);
  pinMode(L, OUTPUT);
  pinMode(R, OUTPUT);
  //rbt_forward(255);
}

void loop() {

  rbt_forward(255);
  int distance = detect_wall();
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  if (abs(distance - old_distance) > 10) {
    if (old_distance != -1) {
      Serial.println("here");
      rbt_stop();
      //      Serial.print("turn right");
      //      turn_right();
      //      rbt_stop();
      delay(5000);
    }
  }
  old_distance = distance;
  

  //  if (customKey1 == '9') {
  //    digitalWrite(A, LOW);
  //    digitalWrite(B, HIGH);
  //
  //    int lSensor = analogRead(A0);
  //
  //    if (lSensor < 200) {
  //      analogWrite (enable1, 255); // left
  //      analogWrite (enable2, 240);
  //    }
  //    else {
  //      delay(50);
  //
  //      duration = sonar.ping();
  //      distance = (duration / 2) * .0343;
  //
  //      if (distance < 10) {
  //        analogWrite (enable1, 0);
  //        analogWrite (enable2, 240);
  //      }
  //    }
  //  }
}

int detect_wall() {

  int cm = 0;
  for (int i = 0; i < 15; i++) {
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);

    pinMode(trigPin, INPUT);

    while (digitalRead(echoPin) == LOW) {
    }
    start = micros();
    while (digitalRead(echoPin) == HIGH) {
    }
    ending = micros();
    duration = ending - start;
    // convert the time into a distance
    cm += microsecondsToCentimeters(duration);
  }

  return cm / 10;
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

  digitalWrite(L, HIGH);
  digitalWrite(R, LOW);
}

void rbt_stop() {
  digitalWrite(L, HIGH);
  digitalWrite(R, HIGH);
}

void rbt_forward(int value) {
  analogWrite(enable_left, value);
  analogWrite(enable_right, value);
  rbt_move();
}

void turn_left() {
  rbt_move();
  analogWrite(enable_left, 255);
  analogWrite(enable_right, 0);
  delay(2080);
  rbt_stop();
}

void turn_right() {
  rbt_move();
  analogWrite(enable_right, 255);
  analogWrite(enable_left, 0);
  delay(1860);
  rbt_stop();
}
