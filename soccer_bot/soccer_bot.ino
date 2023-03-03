
int duty_cycle = 100;
bool falling_edge = 1;
bool rising_edge = 1;

//define Analog input pins for the        receiver
const int speedInputUp = A4;
const int speedInputDown = A5;
const int rightWheelInputUp = A0;
const int rightWheelInputDown = A1;
const int leftWheelInputUp = A2;
const int leftWheelInputDown = A3;

//define output pins to right motor
const int motorSpeedPinR = 5;
const int motorForwardPinR = 8; //used to be 8
const int motorBackwardPinR = 7;

//define output pins to left motor
const int motorSpeedPinL = 6;
const int motorForwardPinL = 4;
const int motorBackwardPinL = 3;

//define LED pins
const int redPin = 12;
const int greenPin = 11;
const int bluePin = 10; //used to be 2

//create variable for data to be used right
int motorSpeedValR = 0;
bool motorForwardR = false;
bool motorBackwardR = false;

//create variable for data to be used left
int motorSpeedValL = 0;
bool motorForwardL = false;
bool motorBackwardL = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(speedInputUp, INPUT);
  pinMode(speedInputDown, INPUT);
  pinMode(rightWheelInputUp, INPUT);
  pinMode(rightWheelInputDown, INPUT);
  pinMode(leftWheelInputUp, INPUT);
  pinMode(leftWheelInputDown, INPUT);

  pinMode(motorSpeedPinR, OUTPUT);
  pinMode(motorForwardPinR, OUTPUT);
  pinMode(motorBackwardPinR, OUTPUT);

  pinMode(motorSpeedPinL, OUTPUT);
  pinMode(motorForwardPinL, OUTPUT);
  pinMode(motorBackwardPinL, OUTPUT);
  
  
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  speedControl();
  
  if (digitalRead(rightWheelInputUp)) {
      motorForwardR = true;
      motorBackwardR = false;
      Serial.println("Right Wheel Forward... ");
      Serial.print(motorSpeedValR);
    }
  else if (digitalRead(rightWheelInputDown)) {
      motorForwardR = false;
      motorBackwardR = true;
      Serial.println("Right Wheel Backward... ");
      Serial.print(motorSpeedValR);
    }
  else  {
      motorForwardR = false;
      motorBackwardR = false;
  }

    
  if (digitalRead(leftWheelInputUp)) {
      motorForwardL = true;
      motorBackwardL = false;
      Serial.println("Left Wheel Forward... ");
      Serial.print(motorSpeedValL);
    }
  else if (digitalRead(leftWheelInputDown)) {
      motorForwardL = false;
      motorBackwardL = true;
      Serial.println("Left Wheel Backward... ");
      Serial.print(motorSpeedValL);
    }
  else  {
      motorForwardL = false;
      motorBackwardL = false;
  }

    updateMotors();
}

int speedControl()  {

  
  if (digitalRead(speedInputUp)) {
    if (rising_edge == 1) {
      rising_edge = 0;
      digitalWrite(8, HIGH);
      Serial.println("UP");
      if (duty_cycle >= 100) {
        duty_cycle = 100;
      }
      else duty_cycle += 10;
      Serial.print("duty cycle: ");
      Serial.println(duty_cycle);
    }
  }
  else {
    rising_edge = 1;
    digitalWrite(8, LOW);
  }


  if (digitalRead(speedInputDown)) {
    if (falling_edge == 1) {
      falling_edge = 0;
      digitalWrite(9, HIGH);
      Serial.println("DOWN");
      if (duty_cycle <= 0) {
        duty_cycle = 0;
      }
      else duty_cycle -= 10;
      Serial.print("duty cycle: ");
      Serial.println(duty_cycle);
    }
  }
  else {
    falling_edge = 1;
    digitalWrite(9, LOW);
  }

  //Assign speed value based on duty cycle
  motorSpeedValL = map(duty_cycle, 0, 100, 100, 255);
  motorSpeedValR = map(duty_cycle, 0, 100, 100, 255);

  //Light up LED color based on current motor speed
  switch (duty_cycle)   {
    case 30:
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    case 60:
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    case 100:
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);    
  }
}


void updateMotors(){
  //using digitalwrite for direction pins
  digitalWrite(motorForwardPinR, motorForwardR);
  digitalWrite(motorBackwardPinR, motorBackwardR);
  
  //using digitalwrite for direction pins
  digitalWrite(motorForwardPinL, motorForwardL);
  digitalWrite(motorBackwardPinL, motorBackwardL);

  
  //using analogWrite for motor speed pins
  analogWrite(motorSpeedPinR, motorSpeedValR);
  
  //using analogWrite for motor speed pins
  analogWrite(motorSpeedPinL, motorSpeedValL);
  
}
