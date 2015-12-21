#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>


// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     9
#define TFT_RST    7  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     8

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
#define centerX tft.width()/2
#define centerY tft.height()/2


int j1 = centerX;
int j2 = centerY;
int jo1 = j1;
int jo2 = j2;
int px = 0;
int py = 0;
bool ox = true;
bool oy = true;
int g1 = 0;
int g2 = 0;

void setup() {
  // put your setup code here, to run once:
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  pinMode(2, OUTPUT);
  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  marcador();
 if(abs(j1-jo1) > 1)
    tft.fillRect(0, 0, 5, tft.height(), ST7735_BLACK);
 if(abs(j2-jo2) > 1)
    tft.fillRect(tft.width()-5, 0, 5, tft.height(), ST7735_BLACK);

    
  jo1 = j1;
  jo2 = j2;  
  j1 = map(analogRead(A0), 0, 1023, 0, tft.height());
  j2 = map(analogRead(A1), 0, 1023, 0, tft.height());
  tft.fillRect(0, j1, 5, 30, ST7735_GREEN);
  tft.fillRect(tft.width()-5, j2, 5, 30, ST7735_GREEN);
 
  tft.fillRect(px, py, 5, 5, ST7735_BLACK);
  if(px <= 5)
  {
    if(py >= j1 && py <= j1+30)
    {
      ox = !ox;
      oy = bound(j1, py);
    }
    else
      gol(1);
    //Serial.println("Cambio de ox");
  }
  if(px+5 >= tft.width() -5)
  {
    if(py >= j2-5 && py <= j2+30)
    {
      ox = !ox;
      oy = bound(j2, py);
    }
    else
      gol(2);
    //Serial.println("Cambio de ox");
  }
  
//  if(px > tft.width()-5)
//  {
//    ox = !ox;
//    //Serial.println("Cambio de oy");
//  }
  if(py < 0 || py > tft.height()-5)
  {
    oy = !oy;
    //Serial.println("Cambio de oy");
  }

  if(ox)
    px++;
  else
    px--;

  if(oy)
    py++;
  else
    py--;
  tft.fillRect(px, py, 5, 5, ST7735_BLUE);
  delay(30);
}

void gol(int q)
{
  tft.fillRect(centerX-30, 0, centerX + 30, 30, ST7735_BLACK);
  px = centerX;
  py = centerY;
  if(q == 1)
    g1++;
  if(q == 2)
    g2++;
  
  if(g1 > 9 || g2 > 9)
    gameOver();
}

bool bound(int j, int py)
{
    if(py > j+15 && py < j+30)
      return(true);
    else
      return(false);

}

void marcador()
{
  tft.setCursor(centerX-30, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(3);
  tft.println(g1);
  tft.setCursor(centerX+10, 0);
  tft.println(g2);
}

void gameOver()
{
  tft.setCursor(centerX-30, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(3);
  tft.println("GAME");
  tft.setCursor(centerX-30, 30);
  tft.println("OVER");
  while(1)
    delay(7000);
  
}
