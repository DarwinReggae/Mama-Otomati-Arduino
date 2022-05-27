#include <virtuabotixRTC.h>
#include <AFMotor.h>

#define sensorPower 10
#define sensorPin A5

AF_DCMotor motor(1,MOTOR12_64KHZ);
AF_DCMotor motor2(2,MOTOR12_64KHZ);

virtuabotixRTC Saat(A1, A2, A3);                                //CLK -> A1, Data -> A2, RST -> A3

//7 segment pinleri
int A = 3;
int B = 2;
int C = 4;
int D = 5;
int E = 6;
int F = 8;
int G = 9;

int switchUpPin = 7;

int buttonUpState = 0;
int lastButtonUpState = 0;

int counter = 1;                                                // Ekranda yazan sayı

int val=0;                                                      // su seviyesi

void setup() 
{
  Serial.begin(9600);

  motor2.setSpeed(254);
  motor.setSpeed(254);
  
  pinMode(LED_BUILTIN, OUTPUT);
  Saat.setDS1302Time(0,0,0,0,0,0,0);
  
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
   
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
}

void loop() 
{
  int level = readSensor();
  Serial.print("Su Seviyesi: ");
  Serial.println(level);

  //Su seviyesine göre dalgıç motoru çalıştırma
  if(level <= 450){
    motor.run(FORWARD);
    delay(1000);    
  }

  buttonUpState = digitalRead(switchUpPin);
  
  //Butonun basılma yada normal durumunda olduğunun kontrolu
  if (buttonUpState != lastButtonUpState) 
  {
    if (buttonUpState == HIGH) 
    {
      //Ekrandaki değeri 1'e resetleme
      if(counter == 9)
      {
        counter = 0;
      }
      counter++;
      Serial.println(counter);
      changeNumber(counter);
      delay(250);
    }
   delay(50);
  }
  
  changeNumber(counter);

  Saat.updateTime();
  Serial.print(Saat.hours);  //Saat
  Serial.print(":");
  Serial.print(Saat.minutes);  //Dakika
  Serial.print(":");
  Serial.print(Saat.seconds); 
  Serial.print("\n");
  delay(1000);
   
  //Ekranda yazan sayı kadar her vakit geçtiğinde mama motorunu çalıştırma
  if(counter==Saat.minutes)
  {
    motor2.setSpeed(254);
    motor2.run(FORWARD);
    delay(3000);
    motor2.run(RELEASE);
    delay(60000);
  }
  
}

//Bu fonksiyon sensörden okunan değeri almak için
int readSensor() {
  digitalWrite(sensorPower, HIGH);  
  delay(10);             
  val = analogRead(sensorPin);    
  digitalWrite(sensorPower, LOW);   
  return val;             
}

//7 segment display sayılarını oluşturma fonksiyonu
void changeNumber(int buttonPress)
{
  switch (buttonPress)
  {    
    case 1:
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    
    case 2:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      break;
    
    case 3:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      break;
  
    case 4:
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    //number 5
    case 5:
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
   
    case 6:
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    
    case 7:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
 
    case 8:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
  
    case 9:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
  }
}
