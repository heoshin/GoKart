// motor control pin
const int motorDirPin = 8; // L298 Input 1
const int motorPWMPin = 9; // L298 Input 2

// encoder pin
const int encoderPinA = 2;
const int encoderPinB = 3;

int encoderPos = 0;

const int motorGearRatio = 131;
const int motorEncoderPulse = 64;
const float ratio = 360./ motorGearRatio / motorEncoderPulse;

// P control
float Kp = 30;
float targetDeg = 0;

void doEncoderA(){  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?1:-1;}
void doEncoderB(){  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?-1:1;}

void doMotor(bool dir, int vel){
  digitalWrite(motorDirPin, dir);
  analogWrite(motorPWMPin, dir ? (255 - vel) : vel);
}

void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
 
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);
 
  pinMode(motorDirPin, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  float motorDeg = float(encoderPos)*ratio;
  float error = targetDeg - motorDeg;
  float control = Kp*error;

  //targeDeg 입력
  if (Serial.available() > 1) {
    Serial.println(Serial.available());
    targetDeg = Serial.parseInt();
  }

  if (motorDeg > 180)
  {
    targetDeg = 180;
    doMotor( (control>=0) ? HIGH : LOW, min(abs(control), 255));
  }
  else if (motorDeg < -180)
  {
    targetDeg = -180;
    doMotor( (control>=0) ? HIGH : LOW, min(abs(control), 255));
  }

  Serial.print("encoderPos : ");
  Serial.print(encoderPos);
  Serial.print("   motorDeg : ");
  Serial.print(float(encoderPos)*ratio);
  Serial.print("   error : ");
  Serial.print(error);
  Serial.print("    control : ");
  Serial.print(control);
  Serial.print("    motorVel : ");
  Serial.println(min(abs(control), 255));
}