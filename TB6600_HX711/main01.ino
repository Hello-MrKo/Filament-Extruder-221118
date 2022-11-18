// 핀설정
 //  GND (HX711)        -      GND (arduino)        
 //  DT  (HX711)        -       2  (arduino)
 //  SCk (HX711)        -       3  (arduino) 
 //  VCC (HX711)        -      5V  (arduino)
 //  PUL+(TB6600)       -       10 (arduino)        
 //  PUL-(TB6600)       -      GND (arduino)
 //  DIR+               -       11 (arduino) 





#include <TimerOne.h>
#include "HX711.h"

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define LOADCELL_DOUT_PIN  2
#define LOADCELL_SCK_PIN  3
HX711 scale;

int M1PUL=10;                                               //motor 1  Pulse pin
int M1DIR=11;                                               //motor 1  Direction pin
long M1speed=1000;                                         // 모터1  속도 초기화 

void setup()
{
  Serial.begin(115200);
  Timer1.initialize(1000000);                         // 인터럽 시간 초기화 마이크로초 (Loadcell 데이터 수집 속도 )
  Timer1.attachInterrupt(timerIsr);                  // timeIsr 설정
    
  pinMode (M1PUL, OUTPUT);                           // motor 출력 설정
  pinMode (M1DIR, OUTPUT);                           // motor 출력 설정 

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
}

 
void loop() {
        noInterrupts();
        digitalWrite(M1DIR,LOW);              // 모터 1 방향 설정 
        digitalWrite(M1PUL,HIGH);
        delayMicroseconds(M1speed);              // 모터 1 속도 설정
        digitalWrite(M1PUL,LOW); 
        delayMicroseconds(M1speed);              // 모터 1 속도 설정 
        interrupts();
        }

void timerIsr()
{
  float a=scale.get_units();                      // a 변수에 로드셀 데이터 값 입력  
  Serial.print("L: ");                                                           
  Serial.println(a);                             // Loadcell 값 출력
  Serial.print("M: ");
  Serial.println(M1speed);                      // 모터 속도 출력
  if (a>=20){
  M1speed=10000;  
  }
  else if(a>=10 && a<20){                                     // 로드셀 설정값  
  M1speed=2000;                                 //  로드셀 설정값 이상이면 모터1 속도 천천히 
  }
  else if (a>=5 && a<10) {
  M1speed=1000;                                  // 로드셀 설정값 이하면 모터1 속도 빠르게    
  }
  else {
  M1speed=500;
  }  
}


