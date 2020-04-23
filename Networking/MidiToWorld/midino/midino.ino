// Midino

#include<Servo.h>

int servoPin2 = 2;
int servoPin3 = 3;
int servoPin4 = 4;

Servo upDown;
Servo leftRight;
Servo inOut;

void setup() 
{
    Serial.begin(9600);
    while(!Serial)
        ;
    upDown.attach(servoPin2);
    leftRight.attach(servoPin3);
    inOut.attach(servoPin4);
    upDown.write(75);
    leftRight.write(45);
    inOut.write(75);
}

void loop() 
{
    while(Serial.available() > 0)
    {
        int value = Serial.readStringUntil('|').toInt();
        int note = Serial.readStringUntil('|').toInt();
        int velocity = Serial.readStringUntil('|').toInt();

        if(note == 74)
        {
            velocity = (velocity * 1.023) + 20;
            upDown.write(velocity);
        }
        if(note == 71)
        {
            velocity == velocity * 1.416;
            leftRight.write(velocity);
        }
        if(note == 91)
        {
            velocity = (velocity * 1.023);
            inOut.write(velocity);
        }
    }
}
