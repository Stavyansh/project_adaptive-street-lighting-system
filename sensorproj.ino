int ldrPin = A0;
int ir1 = 10;
int ir2 = 9;
int ir3 = 8;
int led1 = 6;   
int led2 = 5;  
int led3 = 3;   
int threshold = 500;  

void setup() {
  Serial.begin(9600);

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}
void loop() {
  int ldrValue = analogRead(ldrPin);
  Serial.print("LDR: ");
  Serial.println(ldrValue);
  if (ldrValue < threshold) {
    int ir1State = digitalRead(ir1);
    int ir2State = digitalRead(ir2);
    int ir3State = digitalRead(ir3);
    if (ir1State == LOW) analogWrite(led1, 255);
    else analogWrite(led1, 80);

    if (ir2State == LOW) analogWrite(led2, 255);
    else analogWrite(led2, 80);

    if (ir3State == LOW) analogWrite(led3, 255);
    else analogWrite(led3, 80);
  } 
  else {
    analogWrite(led1, 0);
    analogWrite(led2, 0);
    analogWrite(led3, 0);
  }
  delay(200);
}