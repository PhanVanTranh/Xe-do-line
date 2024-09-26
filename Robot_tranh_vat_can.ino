/*
Cảm biến siêu âm HC-SR04 với Arduino:

VCC: Kết nối với chân 5V trên Arduino
GND: Kết nối với chân GND trên Arduino
Trig: Kết nối với chân số 9 trên Arduino
Echo: Kết nối với chân số 10 trên Arduino
Motor Driver (L298N) với Arduino và động cơ DC:

IN1: Kết nối với chân số 2 trên Arduino
IN2: Kết nối với chân số 3 trên Arduino
IN3: Kết nối với chân số 4 trên Arduino
IN4: Kết nối với chân số 5 trên Arduino
ENA: Kết nối với chân số 6 trên Arduino
ENB: Kết nối với chân số 7 trên Arduino
VCC của Motor Driver: Kết nối với nguồn cấp cho động cơ (thường là pin 12V)
GND của Motor Driver: Kết nối với GND của nguồn cấp và GND của Arduino
OUT1 và OUT2: Kết nối với động cơ DC trái
OUT3 và OUT4: Kết nối với động cơ DC phải
*/


// giải thích  
/* Hàm readUltrasonicDistance: Gửi tín hiệu từ chân Trig của cảm biến siêu âm, 
đợi tín hiệu Echo phản hồi, và tính toán khoảng cách dựa trên thời gian phản hồi.
 Hàm moveForward, stopRobot, turnRight: Điều khiển động cơ để di chuyển robot tiến tới, dừng lại, và quay phải.
 Vòng lặp loop: Liên tục đọc khoảng cách từ cảm biến siêu âm. Nếu khoảng cách nhỏ hơn giá trị an toàn (ví dụ, 20 cm), 
robot sẽ dừng lại và quay phải. Nếu khoảng cách an toàn, robot sẽ tiếp tục di chuyển tiến tới.
*/

#include<Arduino.h>

#define trigPin 9
#define echoPin 10
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define ENA 6
#define ENB 7

void setup() {
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

void stopRobot() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}

void turnRight() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
}

void loop() {
    long distance = readUltrasonicDistance();
    Serial.print("Distance: ");
    Serial.println(distance);
    
    if (distance < 20) { // Khoảng cách an toàn để tránh vật cản
        stopRobot();
        delay(500);
        turnRight();
        delay(500);
    } else {
        moveForward();
    }
    
    delay(100);
}
