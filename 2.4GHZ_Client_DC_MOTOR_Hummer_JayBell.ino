// CLIENT Code HUMMER By Jay Bell
#include <RF24.h>
#include<SPI.h>
#include<Servo.h>
RF24 radio(9,10);
const byte address[6] = "00001";

int in1 = 5;
int in2 = 3;
int PWM1;
int MotorSpeed1 = 0;
int MotorSpeed2 = 0;
// Packet Length: payload of up to 32 bytes at a time (8 byte payload much higher success rate)

char input[8] = "";                 //began at "32"
const char var1[8] = "motor";      //began at "32"

//////////// Set up Train Horn
int horn = 7;
int PWM2 = 0;
const char var2[8] = "horn";//((These must be same as Transmit}}

Servo servo;//For Man waving
//int motor = 6;
int angle2 = 0;
const char var3[8]="wave";//Jay changed to 6 began at 32
//////////// Set up Hummer Lights
#define led 2
int on = 0;
const char var4[8] = "light";//((These must be same as Transmit}}

//////////// Set up Sound   ///////////////////////////////////////////
int sound = 8;
int soundon = 0;
const char var5[8] = "sound";//((These must be same as Transmit}}

void setup(){
Serial.begin(9600);
servo.attach(6);
pinMode(in1,OUTPUT);//H bridge
pinMode(in2,OUTPUT);//H Bridge

pinMode(horn,OUTPUT);//Set uo Train Horn
pinMode(2, OUTPUT);

radio.begin();
radio.openReadingPipe(0, address);
radio.setChannel(100);        //Channels (0 -125) 1Mhz wide start at 2400Mhz-2525Mhz
radio.setDataRate(RF24_250KBPS);//(RF24_250KBPS); //nRF24 supports 250kbps, 1Mbs,2Mbps (250kbps most error free)
radio.enableAckPayload();
radio.enableDynamicPayloads();//Jay added 
radio.setPALevel(RF24_PA_MAX);
radio.startListening();
}

void loop(){
while(!radio.available());
radio.setRetries(15, 15);
radio.read(&input, sizeof(input));

//MOTOR CONTROL
if((strcmp(input,var1) == 0))
  {
while(!radio.available());
radio.read(&PWM1, sizeof(PWM1));
  if (PWM1 < 125){
   MotorSpeed1 = map(PWM1, 124,0, 0, 255);//Limit Reverse? by using (80, 0, 0, 255)?
   analogWrite(in1, MotorSpeed1);
   digitalWrite(in2, LOW);
}
  else if (PWM1 >125){
   MotorSpeed2 = map(PWM1, 125,255, 0, 255);                              
   analogWrite(in2, MotorSpeed2);
   digitalWrite(in1,LOW);
 }
Serial.println(input);
Serial.print("PWM1 Value:");
Serial.println(PWM1);
Serial.println("--------------------------------");
Serial.println("MotorSpeed1");
Serial.println(MotorSpeed1);
Serial.println("MotorSpeed2");
Serial.println(MotorSpeed2);
}
//Set up Train Horn 
else if((strcmp(input,var2) == 0))
  {
while(!radio.available());
radio.read(&PWM2, sizeof(PWM2));
analogWrite(horn,PWM2);
Serial.println(input);
Serial.print("PWM Value:");
Serial.println(PWM2);
Serial.println("--------------------------------");
 }
//SERVO CONTROL  
 else if((strcmp(input,var3) == 0))
 {
while(!radio.available());
radio.read(&angle2, sizeof(angle2));
servo.write(angle2);
Serial.println(input);
Serial.print("Angle:");
Serial.println(angle2);
Serial.println("--------------------------------");
}
//Set up Hummer Lights 
else if((strcmp(input,var4) == 0))
{
while(!radio.available());
radio.read(&on, sizeof(on));
if(on==HIGH){digitalWrite(led, HIGH);
}
else {digitalWrite(led, LOW);
}
Serial.println(input);
Serial.print("on Value:");
Serial.println(on);
Serial.println("--------------------------------");
}
//Set up Sound
else if((strcmp(input,var5) == 0))
  {
while(!radio.available());
radio.read(&soundon, sizeof(soundon));
analogWrite(sound,soundon);
if(soundon==HIGH){digitalWrite(sound, HIGH);
}
else {digitalWrite(sound, LOW);
}
Serial.println(input);
Serial.print("soundon Value:");
Serial.println(soundon);
Serial.println("--------------------------------");
 }
}
