const int  pinForward = 8;
const int  pinBack = 7;

const int  pinLeftForward = 12;
const int  pinLeftBack = 11;
const int  pinRightForward = 10;
const int  pinRightBack = 9;
int bMotorDic = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pinForward, INPUT);
  pinMode(pinBack, INPUT);
  pinMode(pinLeftForward, OUTPUT);
  pinMode(pinLeftBack, OUTPUT);
  pinMode(pinRightForward, OUTPUT);
  pinMode(pinRightBack, OUTPUT);  
}

void loop() {
  if (digitalRead(pinForward) == HIGH) bMotorDic = 1;
  else if (digitalRead(pinBack) == HIGH) bMotorDic = -1;
  else bMotorDic = 0;
  Serial.print(String(digitalRead(pinForward)));
  Serial.print("  ");
  Serial.print(digitalRead(pinBack));
  Serial.print("  ");
  Serial.println (bMotorDic);
  
  if (bMotorDic == 0
  ) {
    digitalWrite(pinLeftForward, HIGH);
    digitalWrite(pinRightForward, HIGH);
    digitalWrite(pinLeftBack, HIGH);
    digitalWrite(pinRightBack, HIGH);
  }
  if (bMotorDic == 1) {
    digitalWrite(pinLeftForward, LOW);
    digitalWrite(pinRightForward, LOW);
    digitalWrite(pinLeftBack, HIGH);
    digitalWrite(pinRightBack, HIGH);
  }
  if (bMotorDic == -1) {
    digitalWrite(pinLeftForward, HIGH);
    digitalWrite(pinRightForward, HIGH);
    digitalWrite(pinLeftBack, LOW);
    digitalWrite(pinRightBack, LOW);
  }
}
