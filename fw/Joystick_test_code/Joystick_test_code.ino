#define VERTICAL    A1
#define HORIZONTAL  A2
#define SELECT      A3 

#define UP      8 
#define DOWN    5
#define LEFT    7
#define RIGHT   6

 
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
    
  pinMode(SELECT, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
        
//  digitalWrite(SELECT, HIGH);
  Serial.begin(115200);

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)    
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second
 
}
 
void loop() {

  Serial.print("Select:  ");
  Serial.println(digitalRead(SELECT));
  
  Serial.print("X-axis: ");
  // Serial.println(analogRead(HORIZONTAL));
  int tmp = analogRead(HORIZONTAL);
  byte X_Pot = map(tmp, 0, 1023, 0, 255);
  Serial.println(X_Pot);

  Serial.print("Y-axis: ");
  // Serial.println(analogRead(VERTICAL));
  tmp = analogRead(VERTICAL);
  byte Y_Pot = map(tmp, 0, 1023, 0, 255);
  Serial.println(Y_Pot);

  Serial.print("UP:  ");
  Serial.println(digitalRead(UP));
  Serial.print("DOWN:  ");
  Serial.println(digitalRead(DOWN));
  Serial.print("LEFT:  ");
  Serial.println(digitalRead(LEFT));
  Serial.print("RIGHT:  ");
  Serial.println(digitalRead(RIGHT));
  Serial.print("\n");

  delay(200);                       // wait for a second  
  
}
