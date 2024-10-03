#include <TFT_eSPI.h> 
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI(); 

void setup() {
  tft.init();
  tft.setRotation(1);
  Serial.begin(115200);
}

int gh;  
int posX;
int posY;

void loop() {
  tft.fillScreen(TFT_BLACK);
  int rand = random(1,3);
  appleFall();
  if (rand == 1){
    ground();
    appleBounce();
  }
  else{
    basket();
  }
}

void ground(){
  uint16_t color = TFT_GREEN;
  for (int16_t x = 0; x < tft.height()/3; x += 10) {
    tft.fillRect(-1, 0, tft.width()+2, x, color);
    delay(10);
    gh = x;
  }
}

void basket(){
  uint16_t c = TFT_BROWN;
  for (int16_t x = 0; x < tft.height()/2; x += 10){
    drawBasket(x);
    delay(30);
  }
  for (int16_t x = 10; x < tft.width(); x+=5) {
    tft.drawCircle(tft.width()/2, tft.height() / 3 + 15, x, TFT_ORANGE);
    delay(10);
  }
  delay(500);

  // }
}

void appleFall(){
  for (int i = 0; i < tft.width()/3 - 50; i++){ 
    tft.fillScreen(TFT_BLACK);
    drawApple(tft.width()-50-i,tft.height()-50 + i/4);
    delay(10);
    posX = tft.width()-50-i;
    posY = tft.height()-50+i/3;
  }
  for (int i = 0; i < tft.height()/3; i++){ 
    tft.fillScreen(TFT_BLACK);
    drawApple(posX - i, posY - i);
    delay(10);
  }
  for (int j = 0; j >= tft.height()/3; j++){ //free fall
    tft.fillScreen(TFT_BLACK);
    //tft.fillCircle(posX, posY - j, 10, TFT_RED);
    drawApple(posX, posY - j);
    delay(10);
  }
}

void appleBounce(){
  int x;
  for (int i = 0; i <= tft.width()/4; i++){ 
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(-1, 0, tft.width()+2, gh, TFT_GREEN);
    drawApple(tft.width()/2 - i, tft.height()/2 + i/3);
    delay(10);
    posX = tft.width()/2 - i;
    posY = tft.height()/2 + i/3;
    x = posX;
  }
  for (int i = 0; i <= tft.width()/4+10; i++){ 
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(-1, 0, tft.width()+2, gh, TFT_GREEN);
    drawApple(posX - i, posY - i/3);
    delay(10);
    x = posX -i;
  }
}

void drawBasket(int32_t x){
  tft.fillRect(tft.width()/2-50, 0, 100, x, TFT_BROWN);
  tft.fillRect(tft.width()/2+45, 15, 5, x+15, TFT_BROWN);
  tft.fillRect(tft.width()/2-50, 15, 5, x+15, TFT_BROWN); 
  for(int i = tft.width()/2 + 30; i <= tft.width()/2-35; i=i+15){
    tft.fillRect(i, 0, 2, x, TFT_RED);
  }
}

void drawApple(int32_t a, int32_t b){
  tft.fillRect(a, b+10, 3, 5, TFT_BROWN);
  tft.fillCircle(a, b, 10, TFT_RED);
  tft.fillTriangle(a, b+10, a+2, b+11, a+1, b+12, TFT_GREEN);
  tft.fillTriangle(a+2, b+11, a+1, b+12, a+5, b+11, TFT_GREEN);
}