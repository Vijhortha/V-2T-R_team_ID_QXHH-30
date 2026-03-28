// ----------- SENSOR CONNECTIONS -------------
#define leftSensor  34   // LEFT IR Sensor OUT
#define rightSensor 35   // RIGHT IR Sensor OUT

// ----------- MOTOR CONNECTIONS -------------
// LEFT MOTOR (connected to OUT3 & OUT4)
#define IN3  14    // L298N IN3 → ESP32 D14 (Left motor direction 1)
#define IN4  12    // L298N IN4 → ESP32 D12 (Left motor direction 2)

// RIGHT MOTOR (connected to OUT1 & OUT2)
#define IN1  26    // L298N IN1 → ESP32 D26 (Right motor direction 1)
#define IN2  27    // L298N IN2 → ESP32 D27 (Right motor direction 2)

#define ENA  33
#define ENB  32 
void setup() {

  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

}

void loop() {

  int leftStatus  = digitalRead(leftSensor);
  int rightStatus = digitalRead(rightSensor);

  if (leftStatus == HIGH && rightStatus == HIGH) {
    moveForward();
  }
  else if (leftStatus == HIGH && rightStatus == LOW) {
    turnLeft();
  }
  else if (leftStatus == LOW && rightStatus == HIGH) {
    turnRight();
  }
  else {
    stopMotors();
  }
}

// ----------- MOVEMENT FUNCTIONS ----------------

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 45);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 45);
}

void turnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 60);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 50);
}
void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 65);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 70);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 60);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 40);
}