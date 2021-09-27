#include <Adafruit_NeoPixel.h>
#define NEO_PIN   13
#define NUM_LEDS  24

const int  pinForward = 8;
const int  pinBack = 7;

const int  pinLeftForward = 12;
const int  pinLeftBack = 11;
const int  pinRightForward = 10;
const int  pinRightBack = 9;
int bMotorDic = 0;

const int pinRGB = A0;

int val;
uint32_t colorValue;
int ledBright = 255;
Adafruit_NeoPixel funnyNeo = Adafruit_NeoPixel(NUM_LEDS, NEO_PIN, NEO_GRB + NEO_KHZ800);

int ConvertRange(int val, int a, int b, int tarA, int tarB);
void setup()
{
  Serial.begin(9600);
  pinMode(pinRGB, INPUT);
  pinMode(pinForward, INPUT);
  pinMode(pinBack, INPUT);

  funnyNeo.setBrightness(ledBright);
  funnyNeo.begin();
}

void loop()
{
  int RED = 0;

  val = analogRead(pinRGB) - 177;
  funnyNeo.clear();
  int ledCnt = ConvertRange(val, 0, 690, 0, 16);
  Serial.print(val);
  Serial.print("  ");
  for (int i = 0; i <= ledCnt; i++)
  {
    RED = ConvertRange(val, 43 * i, 43 * (i + 1), 0, 43);

    colorValue = funnyNeo.Color(ConvertRange(RED, 0, 43, 0, 255), 0, 0);
    funnyNeo.setPixelColor(i + 7, colorValue);
  }
  Serial.println();
  funnyNeo.show();

  
}

int ConvertRange(int val, int a, int b, int tarA, int tarB)
{
  int res = tarA + (val - a) * (((float)tarB - tarA) / (b - a));
  if (res > tarB) res = tarB;
  else if (res < tarA) res = tarA;
  return res;
}
