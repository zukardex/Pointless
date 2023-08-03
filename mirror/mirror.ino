#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define YP A1 
#define XM A2  
#define YM 7   
#define XP 6 

// Calibrate values
#define TS_MINX 125
#define TS_MINY 85
#define TS_MAXX 965
#define TS_MAXY 905
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define  BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define MINPRESSURE 10
#define MAXPRESSURE 1000



void setup() {
  tft.begin(0x9341); 
  tft.setRotation(3);
  tft.fillScreen(BLACK);
  Serial.begin(115200);

  
}
#define limit 250
TSPoint collection[limit]; 
int d=0;
int count=0;
void loop() {

   
  digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        p.x = map(p.x, TS_MINX, TS_MAXX,0, tft.width());
        p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
        tft.fillCircle(p.x, p.y, 3, RED);
        collection[count]=p;
        count++;

      }
      if(count==limit){
              delay(500);
              tft.fillScreen(BLACK);
              int i=0;
            while(i<count){

                  tft.fillCircle(tft.width() - collection[i].x, tft.height() - collection[i].y, 3, RED);              
                  i++;   
            }
            i=0;
              
              delay(500); 
              count=0;
      }
    
    



}
