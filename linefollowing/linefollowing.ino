#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();


// Select the ports for both motors (M1 and M2)
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

int vspeed = 25;
int leftreading;
int rightreading;

int IrLeft = A3;
int IrRight = A1;

//Set the threshold of left and right IR sensor value
uint16_t leftthreshold = 800;
uint16_t rightthreshold = 600;

  
void setup() {

  Serial.begin(9600);

  AFMS.begin();
  leftMotor ->setSpeed(vspeed);
  leftMotor ->run(BACKWARD);
  rightMotor ->setSpeed(vspeed);
  rightMotor ->run(BACKWARD);
  
  // put your setup code here, to run once:
  pinMode(IrLeft, INPUT);
  pinMode(IrRight, INPUT);

   // turn on motor
  leftMotor->run(RELEASE);
  rightMotor ->run(RELEASE);


}

void loop() {

  //Get the serial input and set as the new speed
  if (Serial.available() > 0) {
    int new_speed = Serial.parseInt();
    if (new_speed != 0){
      vspeed = new_speed;
    }
  }
 
  
  leftreading = analogRead(IrLeft);
  rightreading = analogRead(IrRight);
  

  Serial.print(leftreading);
  Serial.print(" ");

  Serial.print(rightreading);
  Serial.print(" ");

  //if both sensor doesn't detect black line, go forward
  if(leftreading < leftthreshold && rightreading < rightthreshold){

    rightMotor ->setSpeed(vspeed);
    leftMotor ->setSpeed(vspeed);
    
    leftMotor ->run(BACKWARD);
    rightMotor -> run(BACKWARD);
    Serial.print(vspeed);
    Serial.print(" ");
    Serial.print(vspeed);
    Serial.print(" ");
  }
  
  //if both sensor detect black line, still go forward
  if(leftreading >= leftthreshold && rightreading >= rightthreshold){

    rightMotor ->setSpeed(vspeed);
    leftMotor ->setSpeed(vspeed);
    leftMotor ->run(BACKWARD);
    rightMotor -> run(BACKWARD);

    Serial.print(vspeed);
    Serial.print(" ");
    Serial.print(vspeed);
    Serial.print(" ");
  }
  
  //if right sensor detect black line, turn right (move left motor)
  if(leftreading < leftthreshold && rightreading >= rightthreshold){

    rightMotor ->setSpeed(vspeed);
    leftMotor ->setSpeed(vspeed);
    
    leftMotor ->run(BACKWARD);
    rightMotor -> run(RELEASE);

    Serial.print(vspeed);
    Serial.print(" ");
    Serial.print(0);
    Serial.print(" ");
    
  }
  
  //if left sensor detect black line, turn left (move right motor)
  if(leftreading >= leftthreshold && rightreading < rightthreshold){

    rightMotor ->setSpeed(vspeed);
    leftMotor ->setSpeed(vspeed);

    leftMotor ->run(RELEASE);
    rightMotor -> run(BACKWARD);

    Serial.print(0);
    Serial.print(" ");
    Serial.print(vspeed);

  }
  Serial.println();
  delay(500);

}
