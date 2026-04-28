#include <Arduino.h>
// #include <time.h>

#define LEFT_FRONT_DIGITAL_INPUT_PIN 9
#define RIGHT_FRONT_DIGITAL_INPUT_PIN 8
#define LEFT_REAR_DIGITAL_INPUT_PIN 11
#define RIGHT_REAR_DIGITAL_INPUT_PIN 10

#define LEFT_WHEEL_OUTPUT A0
#define RIGHT_WHEEL_OUTPUT A1

#define DELAY_TIME 1000

void turnLeft(); // Deactivate turnMode upon completion
void turnRight();
void forward();
void stop();

int count_start = 0;

unsigned char turnMode = 0;
int left_rear_value;


void setup() {
    Serial.begin(9600); // initialize serial for debugging. not necessary when ready
    pinMode(LEFT_FRONT_DIGITAL_INPUT_PIN, INPUT);
    pinMode(RIGHT_FRONT_DIGITAL_INPUT_PIN, INPUT);
    pinMode(LEFT_REAR_DIGITAL_INPUT_PIN, INPUT);
    pinMode(RIGHT_REAR_DIGITAL_INPUT_PIN, INPUT);

    pinMode(LEFT_WHEEL_OUTPUT, OUTPUT);
    pinMode(RIGHT_WHEEL_OUTPUT, OUTPUT);

}

void loop() {

    left_rear_value = digitalRead(LEFT_REAR_DIGITAL_INPUT_PIN);
    if(left_rear_value == LOW && turnMode == 0){
        turnMode = 1;
        delay(DELAY_TIME);
    }
    else if(left_rear_value == LOW && turnMode == 1){
        turnMode = 0;
        delay(DELAY_TIME);
    }

    if(turnMode == 1){
        if(digitalRead(RIGHT_FRONT_DIGITAL_INPUT_PIN) == LOW){
            turnRight();
        }
        else if(digitalRead(LEFT_FRONT_DIGITAL_INPUT_PIN) == LOW){
            turnLeft();
        }
    }
    
    if(digitalRead(RIGHT_REAR_DIGITAL_INPUT_PIN) == LOW){
        delay(DELAY_TIME);
        count_start=!count_start;
    }

    if(!count_start){
        stop();
    }
    else{
        forward();
    }

}





void turnLeft(){
    digitalWrite(RIGHT_WHEEL_OUTPUT, 120);
    digitalWrite(LEFT_WHEEL_OUTPUT, 60);
}

void turnRight(){
    digitalWrite(LEFT_WHEEL_OUTPUT, 120);

    digitalWrite(RIGHT_WHEEL_OUTPUT, 60);
}

void forward(){
    analogWrite(RIGHT_WHEEL_OUTPUT, 120);
    analogWrite(LEFT_WHEEL_OUTPUT, 120);
}

void stop(){
    analogWrite(RIGHT_WHEEL_OUTPUT, 0);
    analogWrite(LEFT_WHEEL_OUTPUT, 0);
}
