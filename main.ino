// ----------- SENSOR CONNECTIONS -------------
#define leftSensor  2   // LEFT IR Sensor OUT
#define rightSensor 3   // RIGHT IR Sensor OUT

// ----------- ULTRASONIC ---------------------
#define trigPin 7
#define echoPin 6

// ----------- MOTOR CONNECTIONS -------------
// LEFT MOTOR (connected to OUT3 & OUT4)
#define IN3  10    // L298N IN3 → ESP32 D14 (Left motor direction 1)
#define IN4  11    // L298N IN4 → ESP32 D12 (Left motor direction 2)

// RIGHT MOTOR (connected to OUT1 & OUT2)
#define IN1  8    // L298N IN1 → ESP32 D26 (Right motor direction 1)
#define IN2  9    // L298N IN2 → ESP32 D27 (Right motor direction 2)

#define ENA  5
#define ENB  3

int urgentCount = 0;
int normalCount = 0;

void setup() {

  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  int leftStatus  = digitalRead(leftSensor);
  int rightStatus = digitalRead(rightSensor);

  float distance = getDistance();

  // -------- REQUEST DETECTION --------
  if (distance > 0 && distance < 10) {
    urgentCount++;
    Serial.println("URGENT REQUEST");
    delay(500);
  }
  else if (distance >= 10 && distance < 20) {
    normalCount++;
    Serial.println("NORMAL REQUEST");
    delay(500);
  }

  // -------- LINE FOLLOWING --------
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


// ----------- ULTRASONIC FUNCTION ------------
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 20000);
  float distance = duration * 0.034 / 2;

  return distance;
}
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 120);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 120);
}

void turnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 130);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 110);
}

void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 110);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 130);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
