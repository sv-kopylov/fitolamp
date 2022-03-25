#include <iarduino_RTC.h>
#include <TimerOne.h>

// 0 объявляем константы
  // 0.1 для режимов
#define NIGHT 0
#define MORNING 1
#define DAY 2
#define EVENING 3
#define MINUTES_PER_DAY 1440

// 0.2 Для пинов
#define DRIVER 2 // отключать блок питания от 220
#define REDS1 9 // 30w
#define REDS2  6 // 30w
#define BLUES 5 // 20w
#define WITES 3 // 40w
#define FULL1 4 // 20w
#define FULL2 7 // 40w
#define FULL3 8 // 40w

// 0.3 объявляем мапу (таблицу) для время против режима 

// четный индекс номер минуты в сутках, следующий нечетный индекс - режим работы начиная с этой минуты и до следующего индекса, или до следующего дня
// всего минут в сутках 1440
int timeTable[] = { 
  0,   NIGHT, // с начала новых суток
  240, MORNING, // 4*60+0 c 4х утра
  255, DAY, // 4*60+15 c 4:15х утра
  1065,EVENING, // 18*60 -15 до 17:45 вечера
  1080,NIGHT // 18*60 световой день с 4 утра до 18 вечера,   всего 14 часов

  
};
// размер таблицы
int ttSize(){
    return sizeof(timeTable)/sizeof(int);
}

// 0.4 режимы работы
 //drv, r1, r2, b, w, f1, f2, f2
int TOTAL_MODES = 4;
int modes[] = {
  0,  0,  0,  0,  0,  0,  0,  0, // NIGHT, выключить все
  1,255,255,  0,  0,  0,  0,  0, // MORNING красное 60 w
  1,255,255,255,  0,  0,  0,  0,  // DAY  80 w
  1,255,255,  0,  0,  0,  0,  0 // EVENING 
};

int getMode(int m, int h){
    int minuteSinseMidnight = h*60+m;
    if(minuteSinseMidnight>MINUTES_PER_DAY){
        minuteSinseMidnight= MINUTES_PER_DAY;
    }
    for(int i =0; i <ttSize()-3; i+=2){
        if(minuteSinseMidnight >=timeTable[i] && minuteSinseMidnight <timeTable[i+2]){
            return timeTable[i+1];
        }
    }
    return NIGHT;

}

// 1 управлени ардуином

// 1.0 глобальные константы
iarduino_RTC time(RTC_DS1307);


// 1.1  инициализация
void setup() {
  pinMode(DRIVER, OUTPUT);
  pinMode(REDS1, OUTPUT);
  pinMode(REDS2, OUTPUT);
  pinMode(BLUES, OUTPUT);
  pinMode(WITES, OUTPUT);
  pinMode(FULL1, OUTPUT);
  pinMode(FULL2, OUTPUT);
  pinMode(FULL3, OUTPUT);
  
  delay(1000);
  Serial.begin(9600);
  time.begin();

  delay(1000);


  
//  time.settime(0, 21, 15, 24, 03, 22); //settime( СЕК [, МИН [, ЧАС [, ДЕНЬ [, МЕС [, ГОД [, ДН ]]]]]] ); 
 }


void loop() {
 // testLights();
  chechAndUpdate(true);
  delay(30000);
}

void chechAndUpdate(bool verbose){
  time.gettime();
  uint8_t m = time.minutes;;
  uint8_t h = time.Hours;
  int mode = getMode(m, h);
  setMode(mode);

  if(verbose){
    
      Serial.println("time: "+String(h)+ ":"+ String(m));
      Serial.println("mode: "+String(mode));
      Serial.println(time.gettime("d-m-Y, H:i:s, D")); 
  }
 

  
}

// установка режима в зависимости от номера режима
void setMode(int m){
 m = m*8;
 digitalWrite(DRIVER, modes[m]);
 analogWrite(REDS1, modes[m+1]);
 analogWrite(REDS2, modes[m+2]);
 analogWrite(BLUES, modes[m+3]);
 analogWrite(WITES, modes[m+4]);
 
 digitalWrite(FULL1, modes[m+5]);
 digitalWrite(FULL2, modes[m+6]);
 digitalWrite(FULL3, modes[m+7]);
}

void testLights(){
  for(int i=0; i<TOTAL_MODES; i++){
    setMode(i);
    delay(20000);
  }
}
