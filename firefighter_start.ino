#include <Pixy2.h>

Pixy2 pixy;

int enable_left = 11;
int enable_right = 10;
int L = 1;
int R = 2;

int echoPin = 13;
int trigPin = 12;
const int MAX_DISTANCE = 350;

bool wait_start = true; //are we still waiting for the start signal?

void setup() {
  // put your setup code here, to run once:
  pixy.init();
  Serial.begin(9600);
  pinMode(L, OUTPUT);
  pinMode(R, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks) {
    for (i = 0; i < pixy.ccc.numBlocks; i++) {
      if ((wait_start == true) && (pixy.ccc.blocks[i].m_signature == 3)){
        //this is the first time it sees yellow
        rbt_stop();
      }
      else if ((wait_start == true) && (pixy.ccc.blocks[i].m_signature != 3)){
        //unstops robot
        wait_start = false;
      }
      else if (wait_start == false){
        //rest of code
        rbt_forward(255);
      }
    }
  }
  
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
