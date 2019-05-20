#include <avr/interrupt.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SerialCommand.h> // Thêm vào sketch thư viện Serial Command
SerialCommand sCmd; // Khai báo biến sử dụng thư viện Serial Command
#include <SimpleTimer.h>
#include <DS3231.h>
SimpleTimer timer;
char modeLcd = 1;
DS3231 clock;
RTCDateTime dt;


  float temperature;
  float humidity;

const int LED_13 = 13;
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);
//
uint8_t bell[8]  = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
uint8_t note[8]  = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};
uint8_t clocki[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
uint8_t duck[8]  = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0};
uint8_t check[8] = {0x0, 0x1 ,0x3, 0x16, 0x1c, 0x8, 0x0};
uint8_t cross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0};
uint8_t retarrow[8] = {  0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};


byte thermo_icon[8] = {
	0b00100,
	0b01010,
	0b01010,
	0b01110,
	0b01110,
	0b11111,
	0b11111,
	0b01110
};
byte humi_icon[8] = {
	B00100,
	B00100,
	B01010,
	B01010,
	B10001,
	B10001,
	B10001,
	B01110,
};
void(* resetFunc) (void) = 0;//cài đặt hàm reset

void CreateCharLCD(void)
{

  lcd.createChar(2, note);
  lcd.createChar(3, heart);
  lcd.createChar(4, duck);
  lcd.createChar(5, check);
  lcd.createChar(6, bell);
  lcd.createChar(7, retarrow);
  lcd.createChar(8, thermo_icon);
  lcd.createChar(9, humi_icon);
  //lcd.home();
}

void reScanUART() {
    sCmd.readSerial();
}

void reScanRTC() {
	 dt = clock.getDateTime();

}
void reScanSensor() {
     temperature = (float)random(28,29);
     humidity = (float)random(730, 750)/10;
     lcd.setCursor(0,3);
     //lcd.print("          ");
}

void lcdViewTime(void)
{
	  lcd.setCursor(1,0);
	  lcd.print(dt.hour);
	  lcd.print(":");
	  lcd.print(dt.minute);
	  lcd.print(":");
	  lcd.print(dt.second);
	  lcd.print(" ");
}
void lcdViewDay(void)
{
	  lcd.setCursor(10,0);
	  lcd.print(dt.day);
	  lcd.print("/");
	  lcd.print(dt.month);
	  lcd.print("/");
	  lcd.print(dt.year);
	  lcd.print(" ");
}
void lcdViewSensor(void)
{
	  lcd.setCursor(1, 1);
	  lcd.write(8);
	  lcd.setCursor(3, 1);
	  lcd.print((float)temperature, 0);
	  lcd.setCursor(5, 1);
	  lcd.print((char)223); //degree sign
	  lcd.print("C ");

	  lcd.setCursor(1, 2);
	  lcd.write(9);
	  lcd.setCursor(3, 2);
	  lcd.print((float)humidity, 0);
	  lcd.print("% ");
}
void lcdViewAlarm(void)
{
	  lcd.setCursor(10, 1);
	  lcd.write(6);
	  lcd.setCursor(10, 2);
	  lcd.write(2);

}
void lcdView(char mode)
{
	if(mode == 1)
	{
	 lcdViewTime();
	 lcdViewDay();
	 lcdViewSensor();
	 lcdViewAlarm();
	}
	if(mode == 2)
	{
		 lcdViewSensor();
		 lcdViewAlarm();
	}

}

void checkI2cCommunicate(void)
{
	  byte error;
	  bool reSetModul = false;
	  	  //39/87

	    Wire.beginTransmission(39);
	    error = Wire.endTransmission();

	    if(error == 0 && reSetModul == true)
	    {
	    	for(int i = 0; i < 2; i++)
	    	{
	    		resetFunc();//tiến hành reset
	    		delay(1000);
	    	}
	    	reSetModul = false;
	    }
	    else if( error==1 ||error==2 || error== 3 || error==4)
	    {
	      Serial.println("Khong tim thay LCD");

	      reSetModul = true;
	    }


}
void setup()
{
	  clock.begin();

	  // Set sketch compiling time
	  clock.setDateTime(__DATE__, __TIME__);


	 pinMode(LED_13, OUTPUT);
	 pinMode(2, INPUT_PULLUP);
	 lcd.begin();

	 lcd.backlight();
	 CreateCharLCD();
	 sCmd.addCommand("led",   led);
	 sCmd.addCommand("ledLCD",  ledLCD);
	 sCmd.addCommand("view",   lcdMode);
	 sCmd.addCommand("reset", reset);
	 sCmd.addCommand("TEXT", textviewer);


	 timer.setInterval(50, reScanUART);
	 timer.setInterval(1000, reScanRTC);
	 timer.setInterval(2000, checkI2cCommunicate);
	 timer.setInterval(4000, reScanSensor);
	 Serial.begin(9600);
	 Serial.println("Scanning...");
	 lcd.clear();
}

void loop()
{

  timer.run();
  lcdView(modeLcd);

}
void led(){
  //Đoạn code này dùng để đọc TỪNG tham số. Các tham số mặc định có kiểu dữ liệu là "chuỗi"
  char *arg;
  arg = sCmd.next();

  int value = atoi(arg); // Chuyển chuỗi thành số
  digitalWrite(LED_13, value);
  if(value == HIGH)
  {

	lcd.backlight();
    lcd.setCursor(12,2);
    lcd.print("LED ON ");


  }
  else
  {

	lcd.backlight();
    lcd.setCursor(12,2);
    lcd.print("LED OFF");


  }
  free(arg);
}
void lcdMode(){

  char *arg;
  arg = sCmd.next();

  int value = atoi(arg);
  lcd.clear();
  if(value == 1){ modeLcd = 1; lcd.noBacklight();}
  if(value == 2){ modeLcd = 2; lcd.noBacklight();}

  free(arg);
}
void textviewer(){

  char *arg;
  arg = sCmd.next();

  lcd.clear();
  lcd.setCursor(1,3);
  lcd.print(arg);

  free(arg);
}
void ledLCD(){

  char *arg;
  arg = sCmd.next();

  int value = atoi(arg);
  if(value == 0){lcd.noBacklight();}
  if(value == 1){lcd.backlight();}

  free(arg);
}
void reset(){

  char *arg;
  arg = sCmd.next();
  lcd.setCursor(8,3);
  lcd.print("Reseting...");
  lcd.print(arg);
  free(arg);
  resetFunc();//tiến hành reset
}
