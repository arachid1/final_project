//pseudocode ish: 
//if detect red, go straight
//calculate time it takes to reach the cup after detection

#include <Pixy2.h>
#include <Servo.h>

Pixy2 pixy;
Servo myServo;

int servopwm = 3;
int enable_left = 1;
int enable_right = 0;
int L = 10;
int R = 11;
int leftPin = A0;

int echoPin = 13;
int trigPin = 12;
const int MAX_DISTANCE = 350;


void setup() {
  pixy.init();
  myServo.attach(3);
  Serial.begin(9600);
  pinMode(L, OUTPUT);
  pinMode(R, OUTPUT);
  
}

void loop() {
rbt_forward(255);
//  int i;
//  pixy.ccc.getBlocks();
//  if (pixy.ccc.numBlocks) {
//    for (i = 0; i < pixy.ccc.numBlocks; i++) {
//      if (pixy.ccc.blocks[i].m_signature == 1){
//        myServo.write(0);
//        rbt_forward(150);
//        delay(2000);
//        rbt_stop();
//        myServo.write(90);
//        delay(3000);
//      }
//    }
//  }
}

void rbt_move() {
  digitalWrite(R, LOW);
  digitalWrite(L, HIGH);
}

void rbt_stop() {
  digitalWrite(L, HIGH);
  digitalWrite(R, HIGH);
}

void rbt_forward(int value) {
  rbt_move();
  analogWrite(enable_left, value);
  analogWrite(enable_right, value);
}
