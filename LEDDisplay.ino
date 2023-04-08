const int incBut = 12;
const int countBut = 13;

const int minLED = 2;
const int maxLED = 11;

int butDelay = 750; //how long between checks to see if both are pressed
int countDelay = 1000;

int curNum = -1; //negative one means no number
void setup() {
  // put your setup code here, to run once:
  for (int i = minLED; i <= maxLED; i++) { //for each LED
    pinMode (i, OUTPUT);       // set as output
  }
  pinMode(incBut, INPUT);
  pinMode(countBut, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
butVal = getButVals();
switch(butVal):
  case 1:
    incNum();
    break;
  case 2:
    count(countDelay); //count up to nine 
    break;
  case 3:
    typeNum();
    break;
  default:
    break;    
}

//get button inputs and return a binary value from 0 to 3
int getButVals(){
  //take values at two different times to account for not pressing down at the same time
  int incVal0 = digitalRead(incBut);
  int countVal0 = digitalRead(countBut);
  delay(butDelay);
  int incVal1 = digitalRead(incBut);
  int countVal1 = digitalRead(countBut);

  int incVal = incVal0||incVal1; //uses how HIGH and LOW are also 1 and 0 or true and false
  int countVal = countVal0||countVal1;  

  return pow(1,incVal)+pow(2,countVal);
}

void incNum(){ //increases/loops back to next number
  int next;  
  if(curNum == 9)
    next = 0;
  else
    next = curNum+1;
  setNum(next);
}

void count(int time){ //counts from 0 or current number to 9
  for(int i = max(0,curNum); i <= 9; i++){
    setNum(i);
    delay(time);
  }
}

void typeNum(){
  while (Serial.available() == 0) {
  }
  int num = Serial.parseInt();
  if(num < 0 || num > 9)
    error();
  else
    setNum(num);
}

void setNum(int num){
  switch(num){
    case 0:
      zero();
      break;
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    case 7:
      seven();
      break;
    case 8:
      eight();
      break;
    case 9:
      nine();
      break;
    default:
      error(); //maybe change this to blank
      break;
  }
}

void zero(){
  blank();
  for (int i = minLED; i <= 8; i++) { //for each LED
    digitalWrite(i, HIGH);
  }
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  curNum = 0;
}

void one(){
  blank();
  digitalWrite(2, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(11, HIGH);
  curNum = 1;
}

void two(){
  blank();
  for (int i = minLED; i <= 5; i++) { //for each LED
    digitalWrite(i, HIGH);
  }
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  curNum = 2;
}

void three(){
  one(); //already blanks
  for (int i = 3; i <= 5; i++) { //for each LED
    digitalWrite(i, HIGH);
  }
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  curNum = 3; 
}

void four(){
  one();  //already blanks
  digitalWrite(4, HIGH);
  digitalWrite(6, HIGH);  
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  curNum = 4;
}

void five(){
  blank();
  for (int i = minLED; i <= 6; i++) { //for each LED
    digitalWrite(i, HIGH);
  }
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);  
  digitalWrite(11, HIGH);
  curNum = 5;
}

void six(){
  five(); //already blanks
  digitalWrite(10, HIGH);  
  curNum = 6;
}

void seven(){
  one(); //already blanks
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  curNum = 7;
}

void eight(){
  zero(); //already blanks
  digitalWrite(9, HIGH);
  curNum = 8;
}

void nine(){
  four();//already blanks
  digitalWrite(5, HIGH);  
  curNum = 9;
}

void blank(){
  for (int i = minLED; i <= maxLED; i++) { //for each LED
    digitalWrite(i, LOW);
  }
  curNum = -1;
}

void error(){ //make exclamation mark
  blank(); //sets current number to -1
  digitalWrite(2, HIGH);
  digitalWrite(7, HIGH);
  
}