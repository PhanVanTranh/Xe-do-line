#define sensor1Pin 2
#define sensor2Pin 3
#define sensor3Pin 4
#define sensor4Pin 5
#define sensor5Pin 6
#define trigPin 9
#define echoPin 10
#define IN1 7
#define IN2 8
#define IN3 11
#define IN4 12
#define ENA 13
#define ENB A0

void setup() {
    pinMode(sensor1Pin, INPUT);
    pinMode(sensor2Pin, INPUT);
    pinMode(sensor3Pin, INPUT);
    pinMode(sensor4Pin, INPUT);
    pinMode(sensor5Pin, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    Serial.begin(9600);
}

long readUltrasonicDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    long distance = duration * 0.034 / 2;
    return distance;
}

void moveForward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
}

void turnLeft() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
}

void turnRight() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
}

void stopRobot() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}

void loop() {
    int sensor1 = digitalRead(sensor1Pin);
    int sensor2 = digitalRead(sensor2Pin);
    int sensor3 = digitalRead(sensor3Pin);
    int sensor4 = digitalRead(sensor4Pin);
    int sensor5 = digitalRead(sensor5Pin);
    long distance = readUltrasonicDistance();

    Serial.print("Distance: ");
    Serial.println(distance);

    if (distance < 20) { // Nếu có vật cản ở khoảng cách nhỏ hơn 20cm
        stopRobot();
        delay(500);
        turnRight();
        delay(500);
    } else {
        if (sensor3 == LOW) { // Đường thẳng
            moveForward();
        } else if (sensor2 == LOW && sensor3 == HIGH && sensor4 == HIGH) { // Quẹo trái nhẹ
            turnLeft();
        } else if (sensor1 == LOW && sensor2 == HIGH && sensor3 == HIGH && sensor4 == HIGH && sensor5 == HIGH) { // Quẹo trái nhiều
            turnLeft();
        } else if (sensor4 == LOW && sensor3 == HIGH && sensor2 == HIGH) { // Quẹo phải nhẹ
            turnRight();
        } else if (sensor5 == LOW && sensor4 == HIGH && sensor3 == HIGH && sensor2 == HIGH && sensor1 == HIGH) { // Quẹo phải nhiều
            turnRight();
        } else {
            stopRobot();
        }
    }

    delay(100);
}
