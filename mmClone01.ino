/*
  mmClone
  Used with expansion board to enable high impedance inputs
  
  Needs Atmel 16U2 reprogramming with HID profile after code upload
 
  Maps digital pins to following keystrokes
  2 - A
  3 - S
  4 - D
  5 - F
  6 - K
  7 - L
  8 - <space>
  9 - <enter>
  
  Active high LED on pin 13 to indicate keystroke send
 */
 
int led = 13;
uint8_t buf[8] = { 0 };
int Akey = 2;
int Skey = 3;
int Dkey = 4;
int Fkey = 5;
int Kkey = 6;
int Lkey = 7;
int Space = 8;
int Enter = 9;
int keyRepeat = 200; //milisecond delay before looking for next 'keypress'
char Pr;
boolean Pressed = false;

void pressKey(char key){
  switch (key){
    case 'A':
      buf[2] = 0x04;
      break;
    case 'S':
      buf[2] = 0x16;
      break;
    case 'D':
      buf[2] = 0x07;
      break;
    case 'F':
      buf[2] = 0x09;
      break;
    case 'K':
      buf[2] = 0x0E;
      break;
    case 'L':
      buf[2] = 0x0F;
      break;
    case 's':
      buf[2] = 0x2C;
      break;
    case 'e':
      buf[2] = 0x28;
      break;
  }
  digitalWrite(led, HIGH);
  Serial.write(buf, 8);
  delay(keyRepeat / 2);
  releaseKey();
  delay(keyRepeat / 2);
  digitalWrite(led, LOW);
}

void releaseKey()
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);
}

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(Akey, INPUT);
  pinMode(Skey, INPUT);
  pinMode(Dkey, INPUT);
  pinMode(Fkey, INPUT);
  pinMode(Kkey, INPUT);
  pinMode(Lkey, INPUT);
  pinMode(Space, INPUT);
  pinMode(Enter, INPUT);
  Serial.begin(9600);
  for (int i = 0; i<5; i++) {
    digitalWrite(led, HIGH);
    delay(20);
    digitalWrite(led, LOW);
    delay(20);
  }
   
}

// the loop routine runs over and over again forever:
void loop() {
  Pressed = true;
  if (digitalRead(Akey) == LOW) Pr = 'A';
  else if (digitalRead(Skey) == LOW) Pr = 'S';
  else if (digitalRead(Dkey) == LOW) Pr = 'D';
  else if (digitalRead(Fkey) == LOW) Pr = 'F';
  else if (digitalRead(Kkey) == LOW) Pr = 'K';
  else if (digitalRead(Lkey) == LOW) Pr = 'L';
  else if (digitalRead(Space) == LOW) Pr = 's';
  else if (digitalRead(Enter) == LOW) Pr = 'e';
  else Pressed = false;
  
  if (Pressed) {
    pressKey(Pr);
  }
  
}
