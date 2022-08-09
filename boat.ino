#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <NewPing.h>

#define IN1 3    //PWM   правый
#define IN2 2
#define IN3 9    //PWM   левый
#define IN4 10
#define Rtrig 5
#define Recho 4
#define Ltrig 7
#define Lecho 6

char way1;
int i;
int Rcm;
int Lcm;
int color;
uint16_t r, g, b, c;
uint16_t r1, g1, b1, c1;

NewPing Rsonar(Rtrig, Recho, 300);
NewPing Lsonar(Ltrig, Lecho, 300);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
}

void loop() {

delay(30000);

motorz('F');
motorz('E');
way1 = sonars();
motorz(way1);
delay(30000);
way1 = colorSensor();
motorz(way1);
motorz('F');

if (way1 == 'R'){
  way1 = 'L';
}else{
  way1 = 'R';
}

motorz(way1);
motorz('F');
motorz('F');
}


void motorz(char way){
  switch(way){
    case 'F':  //Вперед
  digitalWrite(IN2, 1);
  analogWrite(IN1, 200);

  delay(200);

  digitalWrite(IN2, 1);
  analogWrite(IN1, 150);

  digitalWrite(IN4, 0);
  analogWrite(IN3, 105);

  delay(1500);

  digitalWrite(IN2, 0);
  analogWrite(IN1, 150);

  digitalWrite(IN4, 1);
  analogWrite(IN3, 105);

  delay(500);
  
  analogWrite(IN1, 0);
  analogWrite(IN3, 0);
    break;

    case 'R':
  digitalWrite(IN2, 0);
  analogWrite(IN1, 100);

  delay(800);

  analogWrite(IN1, 0); 
    break;

    case 'L':
  digitalWrite(IN4, 0);
  analogWrite(IN3, 100);
  
  delay(800);
 
  analogWrite(IN3, 0);
    break;

    case 'E': //right 05
  digitalWrite(IN2, 0);
  analogWrite(IN1, 180);

  delay(500);

  digitalWrite(IN2, 1);
  analogWrite(IN1, 150);

  delay(200);
  
  analogWrite(IN1, 0); 
    break;

    case 'K': //left 05
  digitalWrite(IN4, 0);
  analogWrite(IN3, 150);
  
  delay(500);

  digitalWrite(IN4, 1);
  analogWrite(IN3, 100);

  delay(200);
 
  analogWrite(IN3, 0);
    break;

    case 'S':
      analogWrite(IN1, 0);
      analogWrite(IN3, 0);
      delay(3000);
    break;
  }
  return 0;
}

char sonars(){

  for(i=0; i<3; i++){
    Rcm = Rcm + Rsonar.ping_cm();
    Lcm = Lcm + Lsonar.ping_cm();
    delay(200);
  }

  if (Rcm/3 > 70) return 'E';
  if (Lcm/3 > 70) return 'K';
  if (Rcm/3 < 70) return 'L';
  if (Lcm/3 < 70) return 'R';
}

char colorSensor(){

  for (i=0; i<3; i++){
  tcs.getRawData(&r, &g, &b, &c);

  r1=r;
  g1=g;
  b1=b;

 if (r1>g1+50 && r1>b1+50){ 
   color=color+1;
    g1=g;
    b1=b;
    
}else if (g1>r1+50 && g1>b1+50){
  color=color+2;
  r1=r;
  b1=b;
  
}else{
  color=0;
}
delay(200);
  }

  if (color == 3) return 'L';
  if (color == 6) return 'R';
  if (color < 3) return 'S';
}


##comment
