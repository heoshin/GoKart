int input = 1;

void setup() {
    
    Serial.begin(115200);
}

void loop() {
    Serial.println(input);
    if (Serial.available() > 1) {
        Serial.println(Serial.available());
        input = Serial.parseInt();
    }
}