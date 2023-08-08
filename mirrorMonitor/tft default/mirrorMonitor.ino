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

// Original values
//#define TS_MINX 150
//#define TS_MINY 120
//#define TS_MAXX 920
//#define TS_MAXY 940

// Calibrate values
#define TS_MINX 125
#define TS_MINY 85
#define TS_MAXX 965
#define TS_MAXY 905

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);





void setup() {
  tft.begin(0x9341); 
  tft.setRotation(3);
  tft.fillScreen(BLACK);
  Serial.begin(115200);

  
}
#define MINPRESSURE 10
#define MAXPRESSURE 1000
void loop() {
digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
    
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        p.x = map(p.x, TS_MINX, TS_MAXX,0, tft.width());
        p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
        if(p.x< tft.width()/4){
          
          tft.fillCircle(p.x, p.y, 3, YELLOW);
          tft.fillScreen(BLACK);
          Serial.print("\n");          
        }
        else{
          tft.fillCircle(p.x, p.y, 3, RED);    
          Serial.print("(");
          Serial.print( p.x/tft.width());
          Serial.print(",");
          Serial.print(p.y/tft.height())      
          Serial.print(")"); 
        }

      }


}
