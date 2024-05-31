// SERVER Hummer by Jay Bell
#include <nRF24L01.h>
#include <RF24.h>
#include<SPI.h>

RF24 radio(9,10);

const byte address[6] = "00001";
const int threshold = 20;

#define pot1 A0 
int potValue1 = 0;
int pwmValue1 = 0;
int check1 = 0;
// Packet Length: payload of up to 32 bytes at a time (8 byte payload much higher success rate)
const char var1[8] = "motor";//began at "32" ((names in transmit and receive
//                                                must be thesame!!!!!))))

#define horn A1
int hornValue2 = 0;
int pwmValue2 = 0;
int check2 = 0;
const char var2[8] = "horn";//began at "32"

#define pot2 A2
int potValue2 = 0;
int angleValue = 0;
int check3 = 0; 
const char var3[8] = "wave";//same as client "wave"

#define button 2
boolean buttonValue2 = 0;
int onValue2 = 0;
int check4 = 0;
const char var4[8] = "light";//began at "32"

#define sound 3
boolean soundValue2 = 0;
int soundonValue2 = 0;
int check5 = 0;
const char var5[8] = "sound";//began at "32"

void setup() {
Serial.begin(9600);
pinMode(button, INPUT);
radio.begin();
radio.openWritingPipe(address);
radio.setChannel(100);        //Channels (0 -125) 1Mhz wide start at 2400Mhz-2525Mhz
radio.setDataRate(RF24_250KBPS); //nRF24 supports 250kbps, 1Mbs,2Mbps (250kbps most error free)
radio.enableAckPayload();
radio.enableDynamicPayloads();//Jay added 
radio.setPALevel(RF24_PA_HIGH);//MAX, HIGH, , MIN
radio.stopListening();
}

void loop() {
potValue1 = analogRead(pot1);
if(potValue1 > check1 + threshold || potValue1 < check1 - threshold)
{
  radio.write(&var1, sizeof(var1));
  pwmValue1 = map(potValue1, 0, 1023, 0, 255);
  radio.write(&pwmValue1, sizeof(pwmValue1));
  check1 = potValue1;
Serial.print("PWM Value1:");
Serial.println(pwmValue1);
}

hornValue2 = analogRead(horn);
if(hornValue2 > check2 + threshold || hornValue2 < check2 - threshold)
{
  radio.write(&var2, sizeof(var2));
  pwmValue2 = map(hornValue2, 0, 1023, 0, 255);
  radio.write(&pwmValue2, sizeof(pwmValue2));
  check2 = hornValue2;
Serial.print("PWM Value:");
Serial.println(pwmValue2);
}

potValue2 = analogRead(pot2);
if(potValue2 > check3 + threshold || potValue2 < check3 - threshold)
{
  radio.write(&var3, sizeof(var3));
  angleValue =map(potValue2, 0, 1023, 180,0);// CW or CCW (180, 0) (0, 180)
  radio.write(&angleValue, sizeof(angleValue));
  check3 = potValue2;
Serial.print("Angle Value:");
Serial.println(angleValue);
}

buttonValue2 = digitalRead(button);
{
  radio.write(&var4, sizeof(var4));
  onValue2 =buttonValue2;
  radio.write(&onValue2, sizeof(onValue2));
  check4 = buttonValue2;
Serial.print("on:");
Serial.println(onValue2);
}

soundValue2 = digitalRead(sound);
{
  radio.write(&var5, sizeof(var5));
  soundonValue2 =soundValue2;
  radio.write(&soundonValue2, sizeof(soundonValue2));
  check5 = soundValue2;
Serial.print("soundon:");
Serial.println(soundonValue2);
}
}
