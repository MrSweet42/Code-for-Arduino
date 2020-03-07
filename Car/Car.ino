int leftLinePin = 10;
int rightLinePin = 11;

int leftDirPin=4;
int leftSpeedPin = 5;

int rightDirPin = 7;
int rightSpeedPin = 6;

int runSpeed = 50;

void setupMotorShield() {
  pinMode(leftDirPin, OUTPUT);
  pinMode(leftSpeedPin, OUTPUT);
  pinMode(rightDirPin, OUTPUT);
  pinMode(rightSpeedPin, OUTPUT);
}

void go() {
  analogWrite(leftSpeedPin, runSpeed);
  analogWrite(rightSpeedPin, runSpeed);
}

void stop() {
  analogWrite(leftSpeedPin, 0);
  analogWrite(rightSpeedPin, 0);
}

void goForward() {
  digitalWrite(leftSpeedPin, HIGH);
  digitalWrite(rightSpeedPin, HIGH);
  go();
}

void turnLeft() {
  digitalWrite(leftSpeedPin, LOW);
  digitalWrite(rightSpeedPin, HIGH);
  go();
}

void turnRight() {
  digitalWrite(leftSpeedPin, HIGH);
  digitalWrite(rightSpeedPin, LOW);
  go();
}

void setup() {
  setupMotorShield();
}

void loop() {
  boolean whiteLeft = digitalRead(leftLinePin);
  boolean whiteRight = digitalRead(rightLinePin);

  if(whiteLeft && whiteRight) {
    goForward();
  } else if (!whiteLeft && !whiteRight) {
    stop();
  } else if (whiteRight) {
    turnLeft();
  } else {
    turnRight();
  }
}
