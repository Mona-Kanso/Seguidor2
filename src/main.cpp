#include <Arduino.h>
// #include <time.h>

#define LEFT_FRONT_DIGITAL_INPUT_PIN 9
#define RIGHT_FRONT_DIGITAL_INPUT_PIN 8
#define LEFT_REAR_DIGITAL_INPUT_PIN 11
#define RIGHT_REAR_DIGITAL_INPUT_PIN 10

#define LEFT_WHEEL_OUPUT_PIN_A 2
#define LEFT_WHEEL_OUTPUT_PIN_B 3
#define RIGHT_WHEEL_OUTPUT_PIN_A 4
#define RIGHT_WHEEL_OUTPUT_PIN_B 5

#define RELAY_INPUT 6
#define LED_OUPUT 7

#define DELAY_TIME 1000

void turnLeft(); // Deactivate turnMode upon completion
void turnRight();
void forward();
void stop();

unsigned char turnMode = 0;
int left_rear_value;
int msec = 0;
int led;
int relay_value;
// clock_t before = NULL, end = NULL;

void setup() {
    Serial.begin(9600); // initialize serial for debugging. not necessary when ready
    pinMode(LEFT_FRONT_DIGITAL_INPUT_PIN, INPUT);
    pinMode(RIGHT_FRONT_DIGITAL_INPUT_PIN, INPUT);
    pinMode(LEFT_REAR_DIGITAL_INPUT_PIN, INPUT);
    pinMode(RIGHT_REAR_DIGITAL_INPUT_PIN, INPUT);

    pinMode(LEFT_WHEEL_OUPUT_PIN_A, OUTPUT);
    pinMode(RIGHT_WHEEL_OUTPUT_PIN_B, OUTPUT);

    pinMode(RELAY_INPUT, INPUT_PULLUP);
    pinMode(LED_OUPUT, OUTPUT);
}

void loop() {

    relay_value = digitalRead(RELAY_INPUT);
    if(relay_value == HIGH){
        
        digitalWrite(LED_OUPUT, HIGH);
        left_rear_value = digitalRead(LEFT_REAR_DIGITAL_INPUT_PIN);
        if(left_rear_value == HIGH && turnMode == 0){
            turnMode = 1;
            delay(DELAY_TIME);
        }

        else if(left_rear_value == HIGH && turnMode == 1){
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

        else if(digitalRead(RIGHT_REAR_DIGITAL_INPUT_PIN) == HIGH){
            stop();
        }

            // else{
            // if (digitalRead(RIGHT_REAR_DIGITAL_INPUT_PIN) == HIGH){
            //     // if(!before){
            //     //   before = clock();
            //     // }
            //     // else{
            //     //   end = clock() - before;
            //     //   msec = end * 1000 / CLOCKS_PER_SEC;

            //     //   Serial.print("Time taken: seconds %d milliseconds");
            //     //   Serial.println(msec/1000, msec%1000);

            //     //   return;
            //     // }
            // }
        forward();
    }

    else{
        stop();
        digitalWrite(LED_OUPUT, LOW);
    }
}



void turnLeft(){
    digitalWrite(RIGHT_WHEEL_OUTPUT_PIN_B, 1);
    digitalWrite(LEFT_WHEEL_OUPUT_PIN_A, 0);
}

void turnRight(){
    digitalWrite(LEFT_WHEEL_OUPUT_PIN_A, 1);

    digitalWrite(RIGHT_WHEEL_OUTPUT_PIN_B, 0);
}

void forward(){
    digitalWrite(RIGHT_WHEEL_OUTPUT_PIN_B, 1);
    digitalWrite(LEFT_WHEEL_OUPUT_PIN_A, 1);
}

void stop(){
    digitalWrite(RIGHT_WHEEL_OUTPUT_PIN_B, 0);
    digitalWrite(LEFT_WHEEL_OUPUT_PIN_A, 0);
}
