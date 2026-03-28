// IR Sensor Pins
int leftIR = 2;
int centerIR = 12;
int rightIR = 3;

// Motor Driver Pins
int IN1 = 6;
int IN2 = 7;
int IN3 = 8;
int IN4 = 11;

// Enable Pins (PWM)
int ENA = 9;
int ENB = 10;

// Speed values (0–255)
int speedForward = 150;
int speedTurn = 120;

void setup() {
  pinMode(leftIR, INPUT);
  pinMode(centerIR, INPUT);
  pinMode(rightIR, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  int left = digitalRead(leftIR);
  int center = digitalRead(centerIR);
  int right = digitalRead(rightIR);

  // Move Forward
  if (left == HIGH && center == HIGH && right == HIGH) {
    forward();
  }

  // Turn Right
  else if (left == HIGH && center == LOW && right == LOW) {
    rightTurn();
  }

  // Turn Left
  else if (left == LOW && center == LOW && right == HIGH) {
    leftTurn();
  }

  // Thick line / junction
  else if (left == LOW && center == HIGH && right == LOW) {
    forward();
  }

  // Reverse condition
  else if (left == HIGH && center == LOW && right == HIGH) {
    reverse();
  }

  // Stop (lost line)
  else {
    stopMotors();
  }
}

// ================= FUNCTIONS =================

void forward() {
  analogWrite(ENA, speedForward);
  analogWrite(ENB, speedForward);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void leftTurn() {
  analogWrite(ENA, speedTurn);
  analogWrite(ENB, speedForward);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void rightTurn() {
  analogWrite(ENA, speedForward);
  analogWrite(ENB, speedTurn);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void reverse() {
  analogWrite(ENA, speedForward);
  analogWrite(ENB, speedForward);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}