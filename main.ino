// IR Sensors
int leftIR = 2;
int centerIR = 3;
int rightIR = 4;

// Motor Driver Pins
int IN1 = A0;
int IN2 = A1;
int IN3 = A2;
int IN4 = A3;

// Enable Pins (IMPORTANT)
int ENA = 9;
int ENB = 10;

void setup() {
  // IR Sensors
  pinMode(leftIR, INPUT);
  pinMode(centerIR, INPUT);
  pinMode(rightIR, INPUT);

  // Motor Pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Enable Pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Enable motors at full speed
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void loop() {
  int left = digitalRead(leftIR);
  int center = digitalRead(centerIR);
  int right = digitalRead(rightIR);

  // Move Forward (on line)
  if (left == HIGH && center == LOW && right == HIGH) {
    forward();
  }

  // Turn Right
  else if (left == HIGH && center == HIGH && right == LOW) {
    rightTurn();
  }

  // Turn Left
  else if (left == LOW && center == HIGH && right == HIGH) {
    leftTurn();
  }

  // All sensors on black (junction)
  else if (left == LOW && center == LOW && right == LOW) {
    forward();
  }

  // Lost line
  else {
    stopMotors();
  }
}

// FUNCTIONS

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void leftTurn() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void rightTurn() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}