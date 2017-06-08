#include <SerialLCD.h>
#include <SoftwareSerial.h> //this is a must

//joystick
int xPin = A1;
int yPin = A0;
int buttonPin = 2;
int buzzer = 10;

int var = 1;

#define trigPin 9
#define echoPin 8


String str;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

// initialize the LCD 
SerialLCD slcd(11,12);//this is a must, assign soft serial pins

void setup() {
  // inicializar las comunicaciones en serie a 9600 bps:
  Serial.begin(9600); 
  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buzzer, OUTPUT);
  
  //activar resistencia pull-up en el pin pulsador 
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

    pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  slcd.begin();
  slcd.print("System Ready!");
}

void loop() {
   readJoystickState();
   readSerialInput();
   proximity();
  // Serial.flush();
}

int treatValue(int data) {
  return (data * 9 / 1024) + 48;
}

void readSerialInput(){
 if (Serial.available() > 0) {

   //read the incoming byte:
   buttonState = Serial.read();

  if(buttonState==1){
    digitalWrite(LED_BUILTIN, HIGH); 
  } 
  else if(buttonState==2){
    digitalWrite(LED_BUILTIN, LOW); 
  }
  else{
      //Errorcodes for the LCD screen
      displayOnLCD(buttonState);
  }
 }
}

void displayOnLCD(int code){
  
  switch(code){
      case 'a':
          lcdClear();
          slcd.print("System Failure");
      break;

      case 'b':
          lcdClear();
          slcd.print("System Ready!");
      break;
      case 'c':
          lcdClear();
          slcd.print("oui haha!! :D");
      break;
      case 'd':
          beep(200,500);
      break;
  }
   /* str = Serial.read();
    *  //slcd.print((long unsigned)code, DEC);
    slcd.println(str);*/
//slcd.setCursor(0, 1);
}

void beep(int freq,int tim){
   analogWrite(buzzer, freq );
   delay(tim);               
   analogWrite(buzzer, 0);   
}

void lcdClear(){
  int i;
  slcd.setCursor(0, 0);
  for(i=0;i<16;i++){
      slcd.print(" ");
  }
   slcd.setCursor(0, 1);
   for(i=0;i<16;i++){
      slcd.print(" ");
  }
  slcd.setCursor(0,0);
}

void readJoystickState(){
  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  buttonState = digitalRead(buttonPin);
  Serial.print(treatValue(xPosition));
  Serial.println(treatValue(yPosition));

  delay(10); // añadir un poco de retraso entre lecturas
}

void proximity()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delay(2); // Added this line
  digitalWrite(trigPin, HIGH);

  delay(2); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29;

  if(distance<150 && var==0){
   lcdClear();
   slcd.print("Out of range");
   //beep(200,500);
   var=1;
  }
  if(distance>150 && var==1){
   lcdClear();
   slcd.print("System Ready");
    var=0;
  }

}
