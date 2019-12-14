#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {15, 16, 7, 17}; 
byte colPins[COLS] = {19, 18, 3}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int echoPin = 13;
int trigPin = 12;

int distance;
int old_distance = -1; 
bool deactivated = false;
long duration, cm, start, ending;
bool alarm_on = true;

void setup(){
  Serial.begin(9600);
  
  
}
  
void loop(){
  char customKey1 = customKeypad.getKey();
  if ((alarm_on == true) && (customKey1 == '9')){
    Serial.println("EMERGENCY");
    alarm_on = false; 
    //rest of code only starts after this becomes false
  }
  else if (alarm_on == false){
    distance = detect_wall();
    if (deactivated == true) {
      old_distance = distance;
      deactivated = false;
    }
    Serial.print(distance);
    Serial.print("cm");
    Serial.println();
  }

 
}

int detect_wall() {

  int cm = 0;
  for (int i = 0; i < 5; i++) {
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    // convert the time into a distance
    cm += microsecondsToCentimeters(duration);
  }

  return cm / 5;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
