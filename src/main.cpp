#include <Arduino.h>
// #include <time.h>

#define LEFT_FRONT_DIGITAL_INPUT_PIN 9
#define RIGHT_FRONT_DIGITAL_INPUT_PIN 8
#define LEFT_REAR_DIGITAL_INPUT_PIN 11
#define RIGHT_REAR_DIGITAL_INPUT_PIN 10

#define DELAY_TIME 1000

void turnLeft(); // Deactivate turnMode upon completion
void turnRight();
void forward();

unsigned char turnMode = 0;
int msec = 0;
// clock_t before = NULL, end = NULL;

void setup() {
  Serial.begin(9600); // initialize serial for debugging. not necessary when ready
  pinMode(LEFT_FRONT_DIGITAL_INPUT_PIN, INPUT);
  pinMode(RIGHT_FRONT_DIGITAL_INPUT_PIN, INPUT);
  pinMode(LEFT_REAR_DIGITAL_INPUT_PIN, INPUT);
  pinMode(RIGHT_REAR_DIGITAL_INPUT_PIN, INPUT);
}

void loop() {
  int read = digitalRead(LEFT_REAR_DIGITAL_INPUT_PIN);
  if(read == HIGH && turnMode == 0){
    turnMode = 1;
    delay(DELAY_TIME);
  }
  else if(read == HIGH && turnMode == 1){
    turnMode = 0;
    delay(DELAY_TIME);
  }

  if(turnMode == 1){
    if(digitalRead(RIGHT_FRONT_DIGITAL_INPUT_PIN) == HIGH){
      turnRight();
    }
    else if(digitalRead(LEFT_FRONT_DIGITAL_INPUT_PIN) == HIGH){
      turnLeft();
    }
  }
  else{
    if (digitalRead(RIGHT_REAR_DIGITAL_INPUT_PIN) == HIGH){
      // if(!before){
      //   before = clock();
      // }
      // else{
      //   end = clock() - before;
      //   msec = end * 1000 / CLOCKS_PER_SEC;

      //   Serial.print("Time taken: seconds %d milliseconds");
      //   Serial.println(msec/1000, msec%1000);

      //   return;
      // }
    }
  }

  forward();
}

void turnLeft(){
  // Serial.println("Turning left");
}

void turnRight(){
  // Serial.println("Turning right");
}

void forward(){
  // Serial.println("Moving forward");
}
