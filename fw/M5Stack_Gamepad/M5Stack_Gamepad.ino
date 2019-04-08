#include <Wire.h>

#define I2C_ADDR  0x52

#define VERTICAL    A1
#define HORIZONTAL  A2
#define SELECT      A3 

#define UP      8 
#define DOWN    5
#define LEFT    7
#define RIGHT   6

byte X_Pot, Y_Pot;
byte Select_state;
byte Button_state;
volatile byte recvAddr; 

//Turn on interrupt for the button
void setupInterrupts()
{
  attachInterrupt(digitalPinToInterrupt(SELECT), buttonInterrupt, CHANGE);  
}

//Called any time the pin changes state
void buttonInterrupt()
{
//  if (digitalRead(SELECT) == LOW) 
//  {
//    Select_state = 0;
//  }else  {
//    Select_state = 1;
//  }
}

void updateJoystick() 
{
  int tmp;
//  byte btn;

  // swap x & y
  // mapping
  tmp = analogRead(VERTICAL);
  X_Pot = map(tmp, 0, 1023, 0, 255);  
  tmp = analogRead(HORIZONTAL);
  Y_Pot = map(tmp, 0, 1023, 0, 255);  

  Select_state = digitalRead(SELECT);

  // read button
  Button_state = 0;
  Button_state = digitalRead(UP);
  Button_state |= digitalRead(DOWN) << 1;
  Button_state |= digitalRead(LEFT) << 2;
  Button_state |= digitalRead(RIGHT) << 3; 
  Button_state |= 0xF0; 
  Button_state = ~Button_state;
  
} 


void receiveEvent(int numberOfBytesReceived)
{
  recvAddr = Wire.read();

  for (byte x = 0 ; x < numberOfBytesReceived - 1 ; x++)
  {
    byte c = Wire.read(); 
    Serial.print(c);
  }
}


//Respond to GET commands
void requestEvent()
{
  updateJoystick();
//  Select_state = digitalRead(SELECT);

  Wire.write(X_Pot);
  Wire.write(Y_Pot);
  Wire.write(Select_state);
  Wire.write(Button_state);  
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
    
  pinMode(SELECT, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);

  setupInterrupts(); //Enable pin change interrupts for I2C and button

  Wire.begin(I2C_ADDR); //Start I2C and answer calls using address from EEPROM

  //The connections to the interrupts are severed when a Wire.begin occurs. So re-declare them.
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

//  digitalWrite(SELECT, HIGH);
  Serial.begin(115200);

//  digitalWrite(LED_BUILTIN, HIGH);
//  delay(500);
//  digitalWrite(LED_BUILTIN, LOW);
//  delay(500);                       
}
 
void loop() {

  updateJoystick();
  
  Serial.print("X-axis: ");
  Serial.println(X_Pot);
  Serial.print("Y-axis: ");
  Serial.println(Y_Pot);
  Serial.print("Select:  ");
  Serial.println(Select_state);
  Serial.print("Button:  ");
  Serial.println(Button_state, BIN);

  if (Button_state & 0x01) Serial.println("UP");
  if (Button_state & 0x02) Serial.println("DOWN");
  if (Button_state & 0x04) Serial.println("LEFT");
  if (Button_state & 0x08) Serial.println("RIGHT");                


  delay(200);                      
}
