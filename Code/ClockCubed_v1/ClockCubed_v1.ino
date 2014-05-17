//battery level/voltage display
//setting time, date
//audio feedback, 'clicking'
//

#include <Wire.h>
#include "font.h"

#define POT 0
#define LIGHT 1
#define BATT 2
#define SPKR 13
#define RCLK 6
#define CLK 8
#define CLEAR 9
#define ENABLE 12
#define COM 4
#define RD 11
#define GR 5
#define BL 10
#define ACCEL_ADDRESS 0x4C
#define CLOCK_ADDRESS 0x68

#define RED 0x01
#define GREEN 0x02
#define YELLOW 0x03
#define BLUE 0x04
#define MAGENTA 0x05
#define TEAL 0x06
#define WHITE 0x07
#define OFF 0x00

int temp = 1;

char colors[7] = {0x01,0x03,0x02,0x06,0x04,0x05,0x07};

char redFrame[2][8] =     {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
char greenFrame[2][8] =   {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
char blueFrame[2][8] =    {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};

char redFlip[2][8] =      {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
char greenFlip[2][8] =    {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
char blueFlip[2][8] =     {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};

unsigned char lastTime = 0;
int val = 0;          //pot level
int light = 0;        //light level
int calPot = 0;       //calibrate pot
int calLight = 0;     //calibrate light
double batVal = 0;    //battery voltage

int color = 0x02;     //default color is green
int tiltReg = 0x18;   //default is upright, no tap or shake
int xreg = 0x00;      //accelerometer values
int yreg = 0x00;
int zreg = 0x00;

int maxBright = 32;   //brightness on-time in microseconds
int minBright = 0;    //brightness off-time in microseconds

char seconds = 0x00;
char minutes = 0x00;
char hours = 0x00;

char day = 0x00;
char dow = 0x00;
char month = 0x00;
char year = 0x00;

int alarmSec = 0;
char alarmMin = 0x00;
char alarmHour = 0x00;
char alarmDay = 0x00;
char alarmDow = 0x00;
char alarmFlag = 0x01;

char mode = 0;
char lastMode = 0;
unsigned long lastMillis = 0;
int setCount = 0;
char tapFlag = 0;
char awake = 0;
char awakeSec = 0;
char fadeLevel = 0;


void setup(){
  Serial.begin(115200);
  
  digitalWrite(ENABLE, HIGH);
  digitalWrite(CLK, LOW);
  digitalWrite(RCLK, LOW);
  digitalWrite(CLEAR, LOW);
  
  digitalWrite(COM, HIGH);
  digitalWrite(RD, LOW);
  digitalWrite(GR, LOW);
  digitalWrite(BL, LOW);
  
  pinMode(RCLK, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(CLEAR, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  
  pinMode(COM, OUTPUT);
  pinMode(RD, OUTPUT);
  pinMode(GR, OUTPUT);
  pinMode(BL, OUTPUT);
  
  delayMicroseconds(100);
  digitalWrite(CLEAR, HIGH);
  
  Serial.print("I2C init");
  Wire.begin();
  accelInit();
  clockInit();
  //setTime(17,32,00,6,5,16,14);
  delay(1000);
  calPot = analogRead(POT);
  //calPot = 512;
  calLight = analogRead(LIGHT);
  
  
  Serial.println("hello world");
}

void loop(){
  int temp = 0;
  char achar = 0x00;
  updateSensors();
  clearFrame();
  
  if(lastMode != mode) awakeSec = 0;
  
  if((hours == alarmHour) && (minutes == alarmMin) && (seconds == 0x00)){
    alarmFlag = 0x01;
  }
  lastMode = mode;
  mode = (tiltReg&0x1c)>>2;  //portrait/landscape/inverted/upright
  if((lastMode == 6) && (mode != 6)){
    alarmFlag = 0x00;
  }
  if((lastMode != 1) && (mode == 1)){
    calPot = analogRead(POT);
  }
  
  switch (mode){     
    case 1:                 //right viewed from front, potentiomenter      
      /*for(int i=7; i>=0; i--){    
        if(i==0) achar = 0x07;
        else achar = colors[i-1];
        if(val>calPot){
          temp = (val-calPot);
          temp -= (8*i);
        
          if(temp > 8){
              column(0xFF,i,achar);
              column(0xFF,i+8,achar);
          }
          else if(temp < 0){
              column(0x00,i,achar);
              column(0x00,i+8,achar);
          }
          else{
            column(~(0xFF<<temp),i,achar);
            column(~(0xFF>>temp),i+8,achar);
          }
        }
        else{
          temp = (calPot-val);
          temp -= (8*i);
        
          if(temp > 8){
            column(0xFF,15-i,achar);
            column(0xFF,7-i,achar);
          }
          else if(temp < 0){
            column(0x00,15-i,achar);
            column(0x00,7-i,achar);
          }
          else{
            column(~(0xFF<<temp),15-i,achar);
            column(~(0xFF>>temp),7-i,achar);
          }
        }
      }*/
      
      if(month > 9) character1(month/10,0,0x02,4);
      character1(month%10,4,0x02,4);
      character1(day/10,8,0x02,4);
      character1(day%10,12,0x02,4);
      
      //character1((val/1000)%10,0,0x01,4);
      //character1((val/100)%10,4,0x01,4);
      //character1((val/10)%10,8,0x01,4);
      //character1((val/1)%10,12,0x01,4);
      //400-340 min
      //600-660 max
      //520 neutral
      
        
      
      break;
    case 2:                 //left viewed from front, binary, RPI      
      //column(seconds%10,7,colors[0]);
      //column(seconds/10,6,colors[1]);
      //column(minutes%10,5,colors[2]);
      //column(minutes/10,4,colors[3]);
      //column(hours%10,3,colors[4]);
      //column(hours/10,2,colors[5]);
      
      character(27, 8, WHITE, 4);      //R
      character(25, 11, RED, 4);       //P
      character(18, 13, WHITE, 4);     //I
      
      character(25, 0, TEAL, 4);      //P
      character(13, 3, MAGENTA, 4);     //D
      character(18, 5, YELLOW, 4);        //I
      
      break;
    case 5:                 //upside down, time, alarm set
      if(millis()-lastMillis > 100){
        lastMillis = millis();
        
        //400-340 min
        //600-660 max
        //520 neutral
      
        if(val > calPot+80){
          alarmSec -= (val-calPot-80)*5;
        }
        
        if(val < calPot-120){
          alarmSec += (calPot-val-120)*5;
        }
        
        while(alarmSec >= 60){
          alarmSec -= 60;
          alarmMin++;
        }        
        while(alarmMin >= 60){
          alarmMin -= 60;
          alarmHour++;
        }
        if(alarmHour >= 24){
          alarmHour = 0;
        }
        while(alarmSec < 0){
          alarmSec += 60;
          alarmMin--;
        }
        while(alarmMin < 0){
          alarmMin += 60;
          alarmHour--;
        }
        if(alarmHour < 0){
          alarmHour = 23;
        }       
      }
      
      color = 0x04;
      if(alarmHour/10 != 0) 
        character1(alarmHour/10, 0, color, 4);
      character1(alarmHour%10, 4, color, 4);
      character1(alarmMin/10, 8, color, 4);
      character1(alarmMin%10, 12, color, 4);
      break;
    case 6:                 //upright, normal, time set
      color = 0x06;
      
      if(millis()-lastMillis > 100){
        lastMillis = millis();
        
        //400-340 min
        //600-660 max
        //520 neutral
      
        if(val > calPot+80){
          seconds -= (calPot-val-80)*10;
          
          while(seconds < 0){
            seconds += 60;
            minutes--;
          }
          while(minutes < 0){
            minutes += 60;
            hours--;
          }
          if(hours < 0){
            hours = 23;
          }
          setTime(hours,minutes,seconds,dow,month,day,year);
        }
        
        if(val < calPot-120){
          seconds += (val-calPot-120)*10;          
          
          while(seconds >= 60){
            seconds -= 60;
            minutes++;
          }        
          while(minutes >= 60){
            minutes -= 60;
            hours++;
          }
          if(hours >= 24){
            hours = 0;
          }
          setTime(hours,minutes,seconds,dow,month,day,year);
        }
      }
      
      if(alarmFlag && seconds%2){
        for(int i=0; i<16; i++) column(0x80,i,0x05);
        if(hours/10 != 0){
          character1(hours/10, 0, OFF, 4);
          character1(hours/10, 0, color, 4);
        }
        character1(hours%10, 4, OFF, 4);
        character1(minutes/10, 8, OFF, 4);
        character1(minutes%10, 12, OFF, 4);
        character1(hours%10, 4, color, 4);
        character1(minutes/10, 8, color, 4);
        character1(minutes%10, 12, color, 4);
      }
      else if(alarmFlag && (seconds+1)%2){
        //for(int i=0; i<16; i++) column(0x80,i,0x04);
        if(hours/10 != 0){
          character1(hours/10, 0, OFF, 4);
          character1(hours/10, 0, color, 4);
        }
        character1(hours%10, 4, OFF, 4);
        character1(minutes/10, 8, OFF, 4);
        character1(minutes%10, 12, OFF, 4);
        character1(hours%10, 4, color, 4);
        character1(minutes/10, 8, color, 4);
        character1(minutes%10, 12, color, 4);
      }
      else{
        if(hours/10 != 0) 
          character1(hours/10, 0, color, 4);
        character1(hours%10, 4, color, 4);
        character1(minutes/10, 8, color, 4);
        character1(minutes%10, 12, color, 4);
      }
      break;
    default:                //unknkown
      break;
  }
  
  if(awake){
    if(fadeLevel < 31*2) fadeLevel++;
    disp(fadeLevel/2, mode);
  }
  if(!awake){
    if(fadeLevel >= 1){
      fadeLevel-=2;
      disp(fadeLevel/2, mode);
    }
  }
    
  //printFrame();

}

//************************************************************\\
// printFrame
//    print the current frame for debugging

void printFrame(){
  unsigned char temp = 0;
  unsigned char temp1 = 0;
  for(int k=0; k<3; k++){
    
    if(k==0) Serial.print("red: ");
    else if(k==1) Serial.print("green: ");
    else Serial.print("blue: ");
    Serial.print("\t");
    
    for(int j=0; j<2; j++){
      for(int i=0; i<8; i++){
        
        if(k==0) temp = redFlip[j][i];
        else if(k==1) temp = greenFlip[j][i];
        else temp = blueFlip[j][i];
        
        Serial.print("0x");
        
        temp1 = (temp&0xF0);
        temp1 /= 0x10;
        if(temp1 < 0x0A)
          temp1 += 0x30;
        else
          temp1 += 0x37;
        Serial.write(temp1);
        
        temp1 = temp&0x0F;
        if(temp1 < 0x0A)
          temp1 += 0x30;
        else
          temp1 += 0x37;
        Serial.write(temp1);
        Serial.print(", ");
      }
    Serial.print("   ");
    }
    Serial.println();
  }
}

//************************************************************\\
// updateSensors
//    check the clock for new data
//    check the accelerometer for new data
//    check the potentiometer for new data
//    check the light sensor for new data

void updateSensors(){
  unsigned char c = 0x00;
  //check pot value
  val = analogRead(POT);
  //check light sensor value
  light = analogRead(LIGHT);
  //check battery voltage
  batVal = analogRead(BATT);
  //check accel data
  
  accelQueue(0x00,4);
  xreg = Wire.read();            //get x
  yreg = Wire.read();            //get y
  zreg = Wire.read();            //get z
  c = Wire.read();               //get tilt
  if(!(c & 0x40)){               //check bad read
    tiltReg = c;
    if(tiltReg & 0x20){
      tapFlag = 1;
      awake = 1;
      awakeSec = 0;
    }
  }
  
  //check clock data
  Wire.beginTransmission(CLOCK_ADDRESS);
  Wire.write(0x03);            //seconds register 0x03
  Wire.endTransmission();
  Wire.requestFrom(CLOCK_ADDRESS, 7);
  while(!Wire.available());    //wait for data
  seconds = Wire.read();       //seconds
  minutes = Wire.read();       //minutes
  hours = Wire.read();         //hours
  day = Wire.read();           //day
  dow = Wire.read();           //DOW
  month = Wire.read();         //month
  year = Wire.read();          //year
  
  //alarmMin = Wire.read();      //alarm minute
  //alarmHour = Wire.read();     //alarm hour
  //alarmDay = Wire.read();      //alarm day
  //alarmDow = Wire.read();      //alarm DOW
  
  seconds = seconds/16*10 + seconds%16;
  minutes = minutes/16*10 + minutes%16;
  hours = hours/16*10 + hours%16;
  day = day/16*10 + day%16;
  month = month/16*10 + month%16;
  year = year/16*10 + year%16;
  
  //alarmMin = (alarmMin&0x7F)/16*10 + (alarmMin&0x7F)%16;
  //alarmHour = (alarmHour&0x7F)/16*10 + (alarmHour&0x7F)%16;
  //alarmDay = (alarmDay&0x7F)/16*10 + (alarmDay&0x7F)%16;
  //alarmDow = alarmDow&0x7F;
  
  if(lastTime != seconds){
          //serial debugging
    if(hours<10) Serial.print("0");
    Serial.print(hours, DEC);   //hours
    Serial.print(":");
    if(minutes<10) Serial.print("0");
    Serial.print(minutes, DEC); //minutes
    Serial.print(":");
    if(seconds<10) Serial.print("0");
    Serial.print(seconds, DEC); //seconds
    Serial.print(" ");
    if     (dow == 0) Serial.print("Sun");
    else if(dow == 1) Serial.print("Mon");
    else if(dow == 2) Serial.print("Tue");
    else if(dow == 3) Serial.print("Wed");
    else if(dow == 4) Serial.print("Thu");
    else if(dow == 5) Serial.print("Fri");
    else if(dow == 6) Serial.print("Sat");
    Serial.print(" ");
    if(month<10) Serial.print("0");
    Serial.print(month, DEC);   //months
    Serial.print("/");
    if(day<10) Serial.print("0");
    Serial.print(day, DEC);     //days
    Serial.print("/");
    Serial.print("20");
    if(year<10) Serial.print("0");
    Serial.print(year, DEC);    //years
    Serial.print(" ");
    
    if(tiltReg & 0x80){
      Serial.print("SHAKE ");
    }
    else Serial.print("      ");
    if(tapFlag){
      Serial.print("TAP ");
      tapFlag = 0;
      awake = 1;
    }
    else Serial.print("    ");
    
    if     ((tiltReg & 0x1C)>>2 == 0x01) Serial.print("RIGHT ");
    else if((tiltReg & 0x1C)>>2 == 0x02) Serial.print("LEFT  ");
    else if((tiltReg & 0x1C)>>2 == 0x05) Serial.print("DOWN  ");
    else if((tiltReg & 0x1C)>>2 == 0x06) Serial.print("UP    ");
    else                                 Serial.print("      ");
    
    if     ((tiltReg & 0x03) == 0x01) Serial.print("FRONT ");
    else if((tiltReg & 0x03) == 0x02) Serial.print("BACK  ");
    else                              Serial.print("      "); 
    
    Serial.print("Twist: ");
    Serial.print(val-calPot, DEC);
    
    Serial.print(" setCount: ");
    Serial.print(setCount, DEC);
    
    Serial.print(" Batt:");
    Serial.print((double)(batVal*5/1023));
    Serial.print("V");
    
    Serial.println("");
    
    if((val > calPot+40) || (val < calPot-80)){
      awakeSec = 0;
      awake = 1;
    }
    
    if(alarmFlag){
      awake = 1;
      awakeSec = 0;
    }
    
    if(awakeSec > 20){
      awake = 0;
      //fadeLevel = 0;
    }
    if(awake) awakeSec++;
    lastTime = seconds;
  }/**/
}

//************************************************************\\
// character
//   Draw a character from a font set at a specified position
//   and with a specified color.  Width is required, but can 
//   be added to the font pack to help with automation.

void character(char num, char pos, char color, char width){
  //color: 0-off 1-red 2-green 3-yellow 4-blue 5-magenta 6-cyan 7-white
  //pos: 0-15
  //num: character index in the font pack
  //width: width of character, typically 3 or 4, not counting 0
  
  if(color & 0x01){    //red on
    for(int i=0; i<width; i++){
      redFrame[pos/8][pos%8+i] &= ~font[num][i];
    }
  }
  if(color & 0x02){    //green on
    for(int i=0; i<width; i++){
      greenFrame[pos/8][pos%8+i] &= ~font[num][i];
    }
  }
  if(color & 0x04){    //blue on
    for(int i=0; i<width; i++){
      blueFrame[pos/8][pos%8+i] &= ~font[num][i];
    }
  }
  if(color == 0){      //off
    for(int i=0; i<width; i++){
      redFrame[pos/8][pos%8+i] |= font[num][i];
      greenFrame[pos/8][pos%8+i] |= font[num][i];
      blueFrame[pos/8][pos%8+i] |= font[num][i];
    }
  }
}

void character1(char num, char pos, char color, char width){
  //color: 0-off 1-red 2-green 3-yellow 4-blue 5-magenta 6-cyan 7-white
  //pos: 0-15
  //num: character index in the font pack
  //width: width of character, typically 3 or 4, not counting 0
  
  if(color & 0x01){    //red on
    for(int i=0; i<width; i++){
      redFrame[pos/8][pos%8+i] &= ~font1[num][i];
    }
  }
  if(color & 0x02){    //green on
    for(int i=0; i<width; i++){
      greenFrame[pos/8][pos%8+i] &= ~font1[num][i];
    }
  }
  if(color & 0x04){    //blue on
    for(int i=0; i<width; i++){
      blueFrame[pos/8][pos%8+i] &= ~font1[num][i];
    }
  }
  if(color == 0){      //off
    for(int i=0; i<width; i++){
      redFrame[pos/8][pos%8+i] |= font1[num][i];
      greenFrame[pos/8][pos%8+i] |= font1[num][i];
      blueFrame[pos/8][pos%8+i] |= font1[num][i];
    }
  }
}

void character2(char num, char pos, char color, char width){
  //color: 0-off 1-red 2-green 3-yellow 4-blue 5-magenta 6-cyan 7-white
  //pos: 0-15
  //num: character index in the font pack
  //width: width of character, typically 3 or 4, not counting 0
  
  if(color & 0x01){    //red on
    for(int i=0; i<width; i++){
      redFrame[pos/8][pos%8+i] &= ~font2[num][i];
    }
  }
  if(color & 0x02){    //green on
    for(int i=0; i<width; i++){
      greenFrame[pos/8][pos%8+i] &= ~font2[num][i];
    }
  }
  if(color & 0x04){    //blue on
    for(int i=0; i<width; i++){
      blueFrame[pos/8][pos%8+i] &= ~font2[num][i];
    }
  }
  if(color == 0){      //off
    for(int i=0; i<width; i++){
      redFrame[pos/8][pos%8+i] |= font2[num][i];
      greenFrame[pos/8][pos%8+i] |= font2[num][i];
      blueFrame[pos/8][pos%8+i] |= font2[num][i];
    }
  }
}

//************************************************************\\
// column
//   Draw a specified column of a specified color and a 
//   specified position

void column(char achar, char pos, char color){
  //color: 0-off 1-red 2-green 3-yellow 4-blue 5-magenta 6-cyan 7-white
  //pos: 0-15
  //achar: binary representation of the pixels in the column that should be on
  
  if(color & 0x01){    //red on
    redFrame[pos/8][pos%8] &= ~achar;
  }
  if(color & 0x02){    //green on
    greenFrame[pos/8][pos%8] &= ~achar;
  }
  if(color & 0x04){    //blue on
    blueFrame[pos/8][pos%8] &= ~achar;
  }
  if(color == 0){      //off
    redFrame[pos/8][pos%8] |= achar;
    greenFrame[pos/8][pos%8] |= achar;
    blueFrame[pos/8][pos%8] |= achar;
  }
}

//************************************************************\\
// clearFrame
//    replace all current pixels with 'off' pixels

void clearFrame(){
  for(int i=0; i<8; i++){
    redFrame[0][i] = 0xFF;
    redFrame[1][i] = 0xFF;
    greenFrame[0][i] = 0xFF;
    greenFrame[1][i] = 0xFF;
    blueFrame[0][i] = 0xFF;
    blueFrame[1][i] = 0xFF;
    
    redFlip[0][i] = 0xFF;
    redFlip[1][i] = 0xFF;
    greenFlip[0][i] = 0xFF;
    greenFlip[1][i] = 0xFF;
    blueFlip[0][i] = 0xFF;
    blueFlip[1][i] = 0xFF;
  }
}

//************************************************************\\
// clockInit
//    call once at the beginning of the program.  Initializes
//    the settings of the RTC

void clockInit(){
  Wire.beginTransmission(CLOCK_ADDRESS);
  Wire.write(0x00);              //start at register 0
  Wire.write(0x00);              //(0x00)control register 1: 3-12/24 2-seconds_INT_en 1-alarm_INT_en
  Wire.write(0x00);              //(0x01)control register 2: 6-cntdwnA_IRQ 5-cntdwnB_IRQ 4-seconds_IRQ 3-alarm_IRQ 1-cntdwnA_INT_en 0-cntdwnB_INT_en
  Wire.write(0x00);              //(0x02)control register 3: 7:5-battery control (T11) 3-batt_IRQ 2-lowBatt_IRQ 1-batt_INT_en 0-lowBatt_INT_en
  Wire.endTransmission();
}

//************************************************************\\
// setTime
//    set the time on the RTC.  All fields required

void setTime(unsigned char hours, unsigned char minutes, unsigned char seconds, unsigned char dow, unsigned char month, unsigned char day, unsigned char year){
  hours = (hours/10%10)*16 + hours%10;
  minutes = (minutes/10%10)*16 + minutes%10;
  seconds = (seconds/10%10)*16 + seconds%10;
  day = (day/10%10)*16 + day%10;
  month = (month/10%10)*16 + month%10;
  year = (year/10%10)*16 + year%10;
  
  Wire.beginTransmission(CLOCK_ADDRESS);
  Wire.write(0x03);            //start at register 3, seconds
  Wire.write(seconds);         //seconds
  Wire.write(minutes);         //minutes
  Wire.write(hours);           //hours
  Wire.write(day);             //day
  Wire.write(dow);             //day of week
  Wire.write(month);           //month
  Wire.write(year);            //year
  Wire.endTransmission();
}

//************************************************************\\
// setAlarm
//    set the alarm on the RTC.  Hours and Minutes only

void setAlarm(unsigned char hours, unsigned char minutes){
  hours = (hours/10%10)*16 + hours%10;
  minutes = (minutes/10%10)*16 + minutes%10;
  
  Wire.beginTransmission(CLOCK_ADDRESS);
  Wire.write(0x0A);            //start at register A, alarm minutes
  Wire.write(minutes);         //minutes
  Wire.write(hours);           //hours
  Wire.endTransmission();
}

//************************************************************\\
// accelSend
//    send one byte to the accelerometer.  It's not standard

void accelSend(unsigned char ADDRESS, unsigned char DATA){
  Wire.beginTransmission(ACCEL_ADDRESS);
  Wire.write(ADDRESS);
  Wire.write(DATA);
  Wire.endTransmission();
}

//************************************************************\\
// accelQueue
//    this function may not be finished...not sure what is does

void accelQueue(unsigned char ADDRESS, int dataBytes){
  Wire.beginTransmission(0x4C);
  Wire.write(ADDRESS);
  Wire.endTransmission();
  Wire.requestFrom(0x4C, dataBytes);
  if(Wire.available())
    return;
}

//************************************************************\\
// accelInit
//    initialize the accelerometer.  Call once during setup

void accelInit(){
  accelSend(0x07,0x00);    //set mode to standby
  accelSend(0x06,0xE7);    //interrupt setup register bits: 7-f/b 6-p/l 5-tap 2:0-shake
  accelSend(0x08,0xE0);    //sample rate register, 8 samples match for tilt, 120 samples/sec
  accelSend(0x09,0x0E);    //tap detection config1
  accelSend(0x0A,0x06);    //tap detection config2
  accelSend(0x07,0x01);    //active mode starts measurements
}

//************************************************************\\
// flipFrame
//    rotate all frames 90 degrees

void flipFrame(){  
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      redFlip[0][i] &= ~(((redFrame[0][j]>>(7-i)) & 0x01)<<j);
      redFlip[1][i] &= ~(((redFrame[1][j]>>(7-i)) & 0x01)<<j);
      
      greenFlip[0][i] &= ~(((greenFrame[0][j]>>(7-i)) & 0x01)<<j);
      greenFlip[1][i] &= ~(((greenFrame[1][j]>>(7-i)) & 0x01)<<j);
      
      blueFlip[0][i] &= ~(((blueFrame[0][j]>>(7-i)) & 0x01)<<j);
      blueFlip[1][i] &= ~(((blueFrame[1][j]>>(7-i)) & 0x01)<<j);
    }
    
    redFlip[0][i] = ~redFlip[0][i];
    redFlip[1][i] = ~redFlip[1][i];
    greenFlip[0][i] = ~greenFlip[0][i];
    greenFlip[1][i] = ~greenFlip[1][i];
    blueFlip[0][i] = ~blueFlip[0][i];
    blueFlip[1][i] = ~blueFlip[1][i];
  }
}


//************************************************************\\
// disp
//    send the current frames to the matrices

void disp(unsigned char brightness, unsigned char orient){
  if(brightness <= minBright)
    brightness = minBright + 1;
  if(brightness >= maxBright)
    brightness = maxBright - 1;
    
  flipFrame();
  
  for(int i=0; i<8; i++){        //8 columns
    switch(orient){
      case 1:
        shiftChars(redFlip[0][i], redFlip[1][i], greenFlip[0][i], greenFlip[1][i], blueFlip[0][i], blueFlip[1][i], ~(0x01<<i), ~(0x01<<i));
        break;
      case 2:
        shiftCharsRev(redFlip[1][i], redFlip[0][i], greenFlip[1][i], greenFlip[0][i], blueFlip[1][i], blueFlip[0][i], ~(0x01<<i), ~(0x01<<i));
        break;
      case 5:
        shiftCharsRev(redFrame[1][i], redFrame[0][i], greenFrame[1][i], greenFrame[0][i], blueFrame[1][i], blueFrame[0][i], ~(0x01<<i), ~(0x01<<i));
        break;
      case 6:
        shiftChars(redFrame[0][i], redFrame[1][i], greenFrame[0][i], greenFrame[1][i], blueFrame[0][i], blueFrame[1][i], ~(0x01<<i), ~(0x01<<i));
        break;
      default:
        break;
    }
      digitalWrite(ENABLE, LOW);            //enable output
      delayMicroseconds(brightness);        //high time
      digitalWrite(ENABLE, HIGH);           //disable output
      delayMicroseconds(maxBright-brightness);    //low time
  }
}

//************************************************************\\
// shiftChars
//    called by disp, shifts data into the shift registers'
//    output flip-flops

void shiftChars(char red1, char red2, char green1, char green2, char blue1, char blue2, char com1, char com2){
  com1 = ((com1&0x55)<<1)|((com1&0xAA)>>1);    //do this because the common lines are interlaced on board
  com2 = ((com2&0x55)<<1)|((com2&0xAA)>>1);    //do this because the common lines are interlaced on board
  
  for(int i=0; i<8; i++){
    digitalWrite(RD, red2 & (0x01 << i));
    digitalWrite(GR, green2 & (0x80 >> i));    //green shift register is backwards on board
    digitalWrite(BL, blue2 & (0x01 << i));
    digitalWrite(COM, com2 & (0x01 << i));
    
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
  
  for(int i=0; i<8; i++){
    digitalWrite(RD, red1 & (0x01 << i));
    digitalWrite(GR, green1 & (0x80 >> i));    //green shift register is backwards on board
    digitalWrite(BL, blue1 & (0x01 << i));
    digitalWrite(COM, com1 & (0x01 << i));
    
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
  
  digitalWrite(RCLK, HIGH);
  digitalWrite(RCLK, LOW);
}

//************************************************************\\
// shiftChars rev
//    called by dispFlip, shifts data into the shift registers'
//    output flip-flops but flipping the bytes

void shiftCharsRev(char red1, char red2, char green1, char green2, char blue1, char blue2, char com1, char com2){
  com1 = ((com1&0x55)<<1)|((com1&0xAA)>>1);    //do this because the common lines are interlaced on board
  com2 = ((com2&0x55)<<1)|((com2&0xAA)>>1);    //do this because the common lines are interlaced on board
  
  for(int i=7; i>=0; i--){
    digitalWrite(RD, red2 & (0x01 << i));
    digitalWrite(GR, green2 & (0x80 >> i));    //green shift register is backwards on board
    digitalWrite(BL, blue2 & (0x01 << i));
    digitalWrite(COM, com2 & (0x01 << i));
    
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
  
  for(int i=7; i>=0; i--){
    digitalWrite(RD, red1 & (0x01 << i));
    digitalWrite(GR, green1 & (0x80 >> i));    //green shift register is backwards on board
    digitalWrite(BL, blue1 & (0x01 << i));
    digitalWrite(COM, com1 & (0x01 << i));
    
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
  
  digitalWrite(RCLK, HIGH);
  digitalWrite(RCLK, LOW);
}
