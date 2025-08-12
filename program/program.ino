int miliseconds = 0;
int seconds = 0;
int minutes = 14;
int hours = 13;
bool secondBeep = false;
bool minutesArray[] = { false, false, false, false, false, false };
bool hoursArray[] = { false, false, false, false, false, false };
unsigned long lastTime = 0;
int secondsInAMinute = 60;     //60
int minutesInAnHour = 60;      //60
int hoursInADay = 24;          //24
int milisecondsInASecond = 1000;  //1000
bool debug = false;
void setup() {
  // put your setup code here, to run once:
  initPins();
  runDiag();
  //coolThing();
  startSerial();
}

void initPins()
{
  for (int i = 2; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
}
void startSerial()
{
  if(debug)
  {
    Serial.begin(9600);
    Serial.print("Begin Run");
  }
}

void runDiag()
{
  setAll(false);
  delay(20);
  setAll(true);
  delay(20);
  setAll(false);
  delay(20);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();
  if (hasBeenASecond(currentTime)) 
  {
    lastTime += milisecondsInASecond;
    incrementTime();
    setSeconds();
    setMinutes();
    setHours();
    setSecondBeep();
    setHourBeeps();
    setMinuteBeeps();
  }
}

bool hasBeenASecond(unsigned long now) {
  return (now - lastTime) >= milisecondsInASecond;
}
void dumpArray()
{
  if(debug)
  {
    Serial.print("{");
    for (int i = 0; i <= 5; i++)
    { 
      Serial.print(minutesArray[i]);
      if(i < 5) Serial.print(",");
    }
    Serial.print("}");
  }
}

void incrementTime() {  
  seconds++;
  if (seconds >= secondsInAMinute) {
    seconds = 0;
    minutes++;
  }
  if (minutes >= minutesInAnHour) {
    if(debug) Serial.print(minutes);
    dumpArray();
    minutes = 0;
    hours++;
  }
  if (hours >= hoursInADay) {
    hours = 0;
  }
}

void setAll(bool val) {
  for (int i = 2; i < 7; i++) {
    setBeep(i, val);
    delay(100);
  }
  for (int i = 13; i >= 7; i--) {
    setBeep(i, val);
    delay(100);
  }
}

void coolThing() {
  for (int j = 0; j < 100; j++) {
    for (int i = 2; i < 10; i++) {
      if (i < 7) {
        setBeep(i, HIGH);
      }
      delay(100);
      setBeep(i - 3, LOW);
    }
    for (int i = 13; i >= 4; i--) {
      if (i >= 7) {
        setBeep(i, HIGH);
      }
      delay(100);
      setBeep(i + 3, LOW);
    }
  }
}


void setBeep(int pin, bool val) {
  if (val) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}

void setSecondBeep() {
  setBeep(13, secondBeep);
}
void setHourBeeps() {
  setBeep(2, hoursArray[0]);  //1
  setBeep(3, hoursArray[1]);  //2
  setBeep(4, hoursArray[2]);  //4
  setBeep(5, hoursArray[3]);  //8
  setBeep(6, hoursArray[4]);  //16
  //setBeep(7, hoursArray[4])
}

void setMinuteBeeps() {
  setBeep(7, minutesArray[0]);  
  setBeep(8, minutesArray[1]);  
  setBeep(9, minutesArray[2]);  
  setBeep(10, minutesArray[3]); 
  setBeep(11, minutesArray[4]); 
  setBeep(12, minutesArray[5]); 
  //setBeep(13, minutesArray[5]);   //64 DONT USE 13 - OVERRIDES L
}

void setSeconds() {
  secondBeep = !secondBeep;
}

void setMinutes() {
  int workingValue = minutes;
  for (int i = 5; i >= 0; i--) {
    int bitVal = 1 << i;
    if (workingValue >= bitVal) {
      workingValue -= bitVal;
      minutesArray[i] = true;
    } else {
      minutesArray[i] = false;
    }
  }
}
void setHours() {
  int workingValue = hours;  //1
  for (int i = 4; i >= 0; i--) {
    int bitVal = 1 << i;
    if (workingValue >= bitVal) 
    {
      workingValue -= bitVal;
      hoursArray[i] = true;
    } else {
      hoursArray[i] = false;
    }
  }
}