#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PING_A 12
#define ECHO_PIN 11

#define TRIGGER_PING_B 7
#define ECHO_PIN_B 6
#define MAX_DISTANCE 15

int degree = 0;
const int ALERT_ESQ = 2;
const int ALERT_SUL = 3;
const int ALERT_NOR = 5;
const int ALERT_DIR = 4;
const int DEBUG = 0;

NewPing sonarA(TRIGGER_PING_A, ECHO_PIN, MAX_DISTANCE);
NewPing sonarB(TRIGGER_PING_B, ECHO_PIN_B, MAX_DISTANCE);

Servo myservo; 

void scanSonar();
void offSensors();

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(ALERT_DIR, OUTPUT);
  pinMode(ALERT_SUL, OUTPUT);
  pinMode(ALERT_NOR, OUTPUT);
  pinMode(ALERT_ESQ, OUTPUT);
}

void loop() {
  int pos = 0;  
  for (pos = 0; pos <= 180; pos += 1) { 
    myservo.write(pos);    
    degree = pos;          
    scanSonar();
    delay(10);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);              
    degree = pos;     
    scanSonar();
    delay(10);
  }
}

void scanSonar() {
  offSensors();
  

  int distanceA = sonarA.ping_cm();
  int distanceB = sonarB.ping_cm();

  if(DEBUG){
    Serial.print("\n ping B: ");
    Serial.print(distanceA);
    Serial.print("cm, ");
    Serial.print(distanceB);
    Serial.print("cm, degree ");
    Serial.print(degree);
  }
  
  if(distanceA < 15 && distanceA > 0){
    if(degree <= 60){
      digitalWrite(ALERT_ESQ, HIGH);
    } 
    if(degree > 60 && degree <= 120){
      digitalWrite(ALERT_SUL, HIGH);
    }
    if(degree > 120){
      digitalWrite(ALERT_DIR, HIGH);
    }
  }

  if(distanceB < 15 && distanceB > 0){
    if(degree <= 60){
      digitalWrite(ALERT_DIR, HIGH);
    } 
    if(degree > 60 && degree <= 120){
      digitalWrite(ALERT_NOR, HIGH);
    }
    if(degree > 120){
      digitalWrite(ALERT_ESQ, HIGH);
    }
  }
}

void offSensors() {
  digitalWrite(ALERT_NOR, LOW);
  digitalWrite(ALERT_ESQ, LOW);
  digitalWrite(ALERT_SUL, LOW);
  digitalWrite(ALERT_DIR, LOW);
}


