#include <ArduinoJson.h>
#include <Servo.h>

#define SERIAL_BAUD 115200

Servo myservo;

const int led_pin = 13;

String receivedCommand = "";
bool dataIn = false;

int preRed = 0;
int preGreen = 0;
int preBlue = 0;
int preServo = 0;

void setup()
{
	// put your setup code here, to run once:

	Serial.begin(SERIAL_BAUD); //same as ESP baud
  pinMode(13, OUTPUT);
	pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  myservo.attach(7);
}

void loop()
{  
	// put your main code here, to run repeatedly:

	while (Serial.available())
	{
    char c = Serial.read(); //read it

    if (c == '[')
    {
      //this is the start of the command string
      receivedCommand = "";
      dataIn = true;
    }
    //otherwise, we are still reading the command string:
    else if (dataIn && c != ']')
    {
      if (c == '0' || c == '1' || c == '2' || c == '3' ||c == '4' ||c == '5' ||c == '6' ||c == '7' ||c == '8' ||c == '9' || c==',' || c=='\"')
        receivedCommand += c;
      else  
        dataIn = false;
      
        
    }

    else if (dataIn && c == ']')
    {
      DynamicJsonDocument doc(1024);

      receivedCommand = "[" + receivedCommand + "]";
      deserializeJson(doc, receivedCommand);
      
      int r = doc[0];
      int g = doc[1];
      int b = doc[2];
      int servo = doc[3];

//      if (preRed != r && r != 0) analogWrite(4, r);       
//      if (preGreen != g && g != 0) analogWrite(5, g);
//      if (preBlue != b && b != 0) analogWrite(6, b);
//      if (preServo != servo && servo !=0) myservo.write(servo);

      if (preRed != r) analogWrite(4, r);       
      if (preGreen != g) analogWrite(5, g);
      if (preBlue != b) analogWrite(6, b);
      if (preServo != servo) myservo.write(servo);

      preRed = r;
      preGreen = g;
      preBlue = b;
      preServo = servo;
    }
	}
}
