#include <Servo.h>

// pin guude zarlaj ogch baina
const int SensorNum = 3;
int TRIG_PINS[SensorNum] = {12, 10, 8};
int ECHO_PINS[SensorNum] = {11, 9, 7};
unsigned int distances[SensorNum] = {0, 0, 0};

#define TRIG_PIN 6
#define ECHO_PIN 5
unsigned int distance = 0;  

#define SERVO_PIN 13
#define A A0
#define B A1
#define C A2
#define D A3
Servo myservo; 

// define variables
bool state = false;


void setup() {
  Serial.begin(9600);
  //servo bolon busad pinguude init hiij baina
  myservo.attach(SERVO_PIN); 
  myservo.write(0);
  pinMode(ECHO_PIN, INPUT);      
  pinMode(TRIG_PIN, OUTPUT);
  for(int i = 0; i < SensorNum; i++) {
    pinMode(ECHO_PINS[i], INPUT);      
  	pinMode(TRIG_PINS[i], OUTPUT);
  }
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
}

void loop() {
  gateHandler();
  parkHandler();
}

void gateHandler() {
  /*program ajilj ehlehed distance sensor anh udaa ajilj 
  baiga bolhoor init hiihgu bol servo ajilaad baisan*/
  /*
  while(distance == 0) {
  	distance = ultra(TRIG_PIN, ECHO_PIN);
  }
  */
  distance = ultra(TRIG_PIN, ECHO_PIN);
  
  //haalga neegdeh uyiin nohtsol 
  //nemelteer haalganii tolviig nemj ogson baiga
  if(distance <= 100 && !state) {
  	myservo.write(90);
    delay(15);
    state = true;
    delay(500);
  } else if(distance > 100 && state){
  //haalga haagdah uyiin nohtsol
  	myservo.write(0);
    delay(15); 
    state = false;
    delay(500);
  }
  /*haalganii tuluv ni neelttei baihad dahiad 
  neeh hergu tul nemj ogson bga*/
}

void parkHandler() {
  int counter = SensorNum;
  for(int i = 0; i < SensorNum; i++) {
  	distances[i] = ultra(TRIG_PINS[i], ECHO_PINS[i]);
    /*
    while(distances[i] == 0) {
  	  ultra(TRIG_PINS, ECHO_PINS);
  	}
    */
    delay(100);
    if(distances[i] <= 30){
      counter -= 1;
    }
  }
  binTo7seg(counter);
}

unsigned long duration;  
unsigned int _distance;
//distance sensoroos utga awah function
unsigned int ultra(int trig, int echo) {
  digitalWrite(trig, LOW);
  delay(1);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);  
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);  
  _distance = duration * 0.0173;
  delay(100);
  return _distance;
}

void binTo7seg(int count) {
  if(count == 0) {//write 0000
    digitalWrite(A,  LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D,  LOW);
  }
  if(count == 1) {//write 0001
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
  }
  if(count == 2) {//write 0010
    digitalWrite(A, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
  }
  if(count == 3) {//write 0011
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
  }
  if(count == 4) {//write 0100
    digitalWrite(A,  LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D,  LOW);
  } 
  if(count == 5) {//write 0101
    digitalWrite(A,  HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D,  LOW);
  }  
  if(count == 6) {//write 0110
    digitalWrite(A,  LOW);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D,  LOW);
  }  
  if(count == 7) {//write 0111
    digitalWrite(A,  HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D,  LOW);
  }
  if(count == 8) {//write 1000
    digitalWrite(A,  LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D,  HIGH);
  }  
  if(count == 9) {//write 1001
    digitalWrite(A,  HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D,  HIGH);
  } 
}