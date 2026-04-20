// ----------- IR Sensor Pins -----------------
int leftIR = 3;
int rightIR = 2;
int sideIR = 12;   //  NEW SIDE SENSOR

// ----------- ULTRASONIC ---------------------
#define trigPin 4
#define echoPin 5

// ----------- RGB + BUZZER -------------------
#define buzzer A4
#define redPin A1
#define greenPin A2
#define bluePin A3

// ----------- MOTOR DRIVER -------------------
int IN1 = 6;
int IN2 = 7;
int IN3 = 8;
int IN4 = 11;

int ENA = 9;
int ENB = 10;

// ----------- VARIABLES ----------------------
int roomCount = 0;
int urgentCount = 0;
int noRequestCount = 0;

bool wallDetected = false;

int speedForward = 90;
int speedTurn = 220;

// ----------- SETUP --------------------------
void setup() {
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
  pinMode(sideIR, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);
}

// ----------- LOOP ---------------------------
void loop() {

  int left = digitalRead(leftIR);
  int right = digitalRead(rightIR);
  int side = digitalRead(sideIR);

  float distance = getDistance();

  //  WALL DETECTION START
  if (side == LOW && !wallDetected) {
    wallDetected = true;

    stopMotors();

    //  beep when wall starts
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);

    delay(300);
  }

  // ? DOOR DETECTED (wall ends)
  if (side == HIGH && wallDetected) {

    wallDetected = false;

    stopMotors();
    delay(200);

    roomCount++;

    Serial.print("Room ");
    Serial.println(roomCount);

    //  ULTRASONIC CHECK
    if (distance >= 8 && distance <= 17) {
      noRequestCount++;

      Serial.println("Door: CLOSED");
      Serial.println("Request: NONE");

      blinkLED(0, 255, 0); // 
    }
    else if (distance > 17 && distance <= 19) {
      urgentCount++;

      Serial.println("Door: OPEN");
      Serial.println("Request: URGENT");

      blinkLED(255, 0, 0); // 
    }
    else {
      Serial.println("Invalid distance");
    }

    // SUMMARY
    Serial.print("Total Rooms: ");
    Serial.println(roomCount);

    Serial.print("No Request: ");
    Serial.println(noRequestCount);

    Serial.print("Urgent: ");
    Serial.println(urgentCount);

    Serial.println("----------------------");

    delay(800);
  }

  // -------- LINE FOLLOWING --------

  if (left == LOW && right == LOW) {
    forward();
  }
  else if (left == LOW && right == HIGH) {
    rightTurn();
  }
  else if (left == HIGH && right == LOW) {
    leftTurn();
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

// ----------- LED FUNCTIONS ------------------
void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void blinkLED(int r, int g, int b) {
  setColor(r, g, b);
  delay(300);
  setColor(0, 0, 0);
}

// ----------- MOVEMENT FUNCTIONS -------------

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

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
