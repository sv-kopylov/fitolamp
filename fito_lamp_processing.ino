#include <iarduino_RTC.h>
#include <TimerOne.h>

iarduino_RTC time(RTC_DS1307);

uint8_t minu;
uint8_t hour;

//

int DRIVER = 2;// отключать блок питания от 220
int REDS1 = 9;
int REDS2 = 6;
int BLUES = 5;
int WITES = 3;

int FULL1 = 4;
int FULL2 = 7;
int FULL3 = 8;

int currentMode = 0;
int MODES_NUM = 8;
int modes[] = {

  0,  0,  0,  0,  0,  0,  0,  0, // ночь, выключить все
  1,255,  0,  0,  0,  0,  0,  0, 
  1,255,255,  0,  0,  0,  0,  0, 
  1,255,255,255,  0,  0,  0,  0, 
  1,255,255,255,  255,0,  0,  0, 
  0,255,255,255,  255,0,  0,  0,
  1,255,255,255,  255,0,  0,  0
//  1,255,255,  0,0,0,0,0, // утро
  
//  0,0,0,0,0,0,0,0, // день
  
//  0,0,0,0,0,0,0,0, // вечер
 
};



void setup() {
//  delay(3000);
  Serial.begin(9600);
  time.begin();
  Timer1.initialize(30000000); // тридцать секунда
  Timer1.attachInterrupt(checktime);
  updateLights();
//  time.settime(0, 20, 21, 19, 01, 22); //settime( СЕК [, МИН [, ЧАС [, ДЕНЬ [, МЕС [, ГОД [, ДН ]]]]]] ); 
 
// put your setup code here, to run once:

}
void checktime(){
  //    time.gettime("d-m-Y, H:i:s, D ");
  
    time.gettime();
    Serial.println(time.gettime("d-m-Y, H:i:s, D "));
    minu = time.minutes;
    hour = time.Hours;
    Serial.println(String(hour)+ ":"+ String(minu));
    updateLights();
}

void updateLights(){
 int mode = getMode();
 digitalWrite(DRIVER, modes[mode]);
 
 analogWrite(REDS1, modes[mode+1]);
 analogWrite(REDS2, modes[mode+2]);
 analogWrite(BLUES, modes[mode+3]);
 analogWrite(WITES, modes[mode+4]);
 
 digitalWrite(FULL1, modes[mode+5]);
 digitalWrite(FULL2, modes[mode+6]);
 digitalWrite(FULL3, modes[mode+7]);
}

int getMode(){
  if(currentMode>=MODES_NUM-1){
    currentMode=0;
  }
  int resp = currentMode*8;
  currentMode ++;
  return resp;
  
}



void loop() {

  // put your main code here, to run repeatedly:

}