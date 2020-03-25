void setup() 
{
    Serial.begin(9600);
    while(!Serial)
        ;
}

void loop() 
{
    if(Serial.available() > 0)
    {
        message = Serial.read();
    }
}
