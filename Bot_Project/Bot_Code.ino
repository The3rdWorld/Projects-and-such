//Initial Setup
  //Motors
int RIn1 = 2;
int RIn2 = 3;
int LIn1 = 4;
int LIn2 = 7;
int RSpd = 6;
int LSpd = 5;
  //QRD1114 Sensors
const int SR2 = A0;
const int SR1 = A1;
const int SMid = A2;
const int SL1 = A3;
const int SL2 = A4;

  //Additional Constants
//Constant used for adjusting sensor output
int Sensitivity = 750.0;
//The value which establishes on/off the line
int LineSense = 4.0;
//Motor speed
int Spd = 75;
// Setup code here, to run once:
void setup() {
  pinMode(RIn1, OUTPUT);
  pinMode(RIn2, OUTPUT);
  pinMode(RSpd, OUTPUT);
  pinMode(LIn1, OUTPUT);
  pinMode(LIn2, OUTPUT);
  pinMode(LSpd, OUTPUT);

  Serial.begin(9600);
  pinMode(SR2, INPUT);
  pinMode(SR1, INPUT);
  pinMode(SMid, INPUT);
  pinMode(SL1, INPUT);
  pinMode(SL2, INPUT);
}


//Define 
void RMForward() {
  digitalWrite(RIn1, LOW);
  digitalWrite(RIn2, HIGH);
  analogWrite(RSpd,Spd);
}

void RMReverse() {
  digitalWrite(RIn1, HIGH);
  digitalWrite(RIn2, LOW);
  analogWrite(RSpd,Spd);
}

void LMForward() {
  digitalWrite(LIn1, LOW);
  digitalWrite(LIn2, HIGH);
  analogWrite(LSpd,Spd);
}

void LMReverse() {
  digitalWrite(LIn1, HIGH);
  digitalWrite(LIn2, LOW);
  analogWrite(LSpd,Spd);
}

void RMStop() {
  digitalWrite(RIn1, LOW);
  digitalWrite(RIn2, LOW);
}

void LMStop() {
  digitalWrite(LIn1, LOW);
  digitalWrite(LIn2, LOW);
}

// Main code here, to run repeatedly:
void loop() {
  //Read and print each sensor 
  int lineR2 = analogRead(SR2);
  int lineR1 = analogRead(SR1);
  int lineMid = analogRead(SMid);
  int lineL1 = analogRead(SL1);
  int lineL2 = analogRead(SL2);
  
  float lineR2V = (float)lineR2 * 5.0 / Sensitivity;
  float lineR1V = (float)lineR1 * 5.0 / Sensitivity;
  float lineMidV = (float)lineMid * 5.0 / Sensitivity;
  float lineL1V = (float)lineL1 * 5.0 / Sensitivity;
  float lineL2V = (float)lineL2 * 5.0 / Sensitivity;
  Serial.print("Right2: ");
  Serial.println(lineR2V);
  Serial.print("Right1: ");
  Serial.println(lineR1V);
  Serial.print("Middle: ");
  Serial.println(lineMidV);
  Serial.print("Left1: ");
  Serial.println(lineL1V);
  Serial.print("Left2: ");
  Serial.println(lineL2V);
  Serial.println();

  //Start creating If statements for conditions
    //If in the void, move until line is found
    if ((lineL2V < LineSense) && (lineL1V < LineSense) && (lineMidV < LineSense) && (lineR1V < LineSense) && (lineR2V < LineSense)) {
      Serial.print("No Line Found! \r");
      LMForward();
      RMForward();
      delay(50);
    }
    //If at a crossroad
    else if ((lineL2V > LineSense) && (lineR2V > LineSense)) {
      Serial.print("At a Junction \r");
      RMForward();
      LMForward();
      delay(50);
    }
    //Turn left condition
    else if ((lineL2V > LineSense) || ((lineL1V > LineSense) && (lineL2V > LineSense))) {
      Serial.print("Turning Left \r");
      RMForward();
      LMReverse();
      delay(60);
    }
    //Turn right condition
    else if ((lineR2V > LineSense) || ((lineR1V > LineSense) && (lineR2V > LineSense))) {
      Serial.print("Turning Right \r");
      RMReverse();
      LMForward();
      delay(60);
    }
    //Else move forward
    else {
      Serial.print("Moving Forward \r");
      RMForward();
      LMForward();
      delay(45);
    }
  RMStop();
  LMStop();
}
