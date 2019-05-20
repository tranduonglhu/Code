#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2019-05-17 17:50:47

#include "Arduino.h"
#include <avr/interrupt.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SerialCommand.h>
extern SerialCommand sCmd;
#include <SimpleTimer.h>
#include <DS3231.h>

void CreateCharLCD(void) ;
void reScanUART() ;
void reScanRTC() ;
void reScanSensor() ;
void lcdViewTime(void) ;
void lcdViewDay(void) ;
void lcdViewSensor(void) ;
void lcdViewAlarm(void) ;
void lcdView(char mode) ;
void checkI2cCommunicate(void) ;
void setup() ;
void loop() ;
void led();
void lcdMode();
void textviewer();
void ledLCD();
void reset();

#include "Clock_Uart_Computer.ino"


#endif
