/*
Cảm biến dò line 5 line với Arduino:

Các chân tín hiệu của cảm biến dò line sẽ được kết nối với các chân digital trên Arduino. Ví dụ:
Sensor 1 (cảm biến ngoài cùng bên trái): Kết nối với chân số 2 trên Arduino
Sensor 2 (cảm biến giữa bên trái): Kết nối với chân số 3 trên Arduino
Sensor 3 (cảm biến giữa): Kết nối với chân số 4 trên Arduino
Sensor 4 (cảm biến giữa bên phải): Kết nối với chân số 5 trên Arduino
Sensor 5 (cảm biến ngoài cùng bên phải): Kết nối với chân số 6 trên Arduino
VCC: Kết nối với chân 5V trên Arduino
GND: Kết nối với chân GND trên Arduino
Motor Driver (L298N) với Arduino và động cơ DC:

IN1: Kết nối với chân số 7 trên Arduino
IN2: Kết nối với chân số 8 trên Arduino
IN3: Kết nối với chân số 9 trên Arduino
IN4: Kết nối với chân số 10 trên  Arduino
ENA: Kết nối với chân số 11 trên Arduino
ENB: Kết nối với chân số 12 trên Arduino
VCC của Motor Driver: Kết nối với nguồn cấp cho động cơ (thường là pin 12V)
GND của Motor Driver: Kết nối với GND của nguồn cấp và GND của Arduino
OUT1 và OUT2: Kết nối với động cơ DC trái
OUT3 và OUT4: Kết nối với động cơ DC phải
*/

// giải thích
/*
Hàm điều khiển động cơ: moveForward, turnLeft, turnRight, stopRobot để điều khiển động cơ di chuyển robot tiến tới, quay trái, quay phải và dừng lại.
Vòng lặp loop: Liên tục đọc giá trị từ các cảm biến dò line. Dựa trên giá trị đọc được, robot sẽ di chuyển tiến tới, quay trái, quay phải hoặc dừng lại.
Lưu ý:
Các giá trị LOW và HIGH sẽ phụ thuộc vào cách mà cảm biến của bạn phát hiện màu sắc. Nếu vạch đen là LOW và nền trắng là HIGH, bạn sẽ sử dụng logic như trên. Nếu ngược lại, bạn cần điều chỉnh các điều kiện trong mã.
Bạn có thể cần điều chỉnh giá trị PWM (điều chỉnh tốc độ động cơ) trong hàm analogWrite cho phù hợp với động cơ và môi trường hoạt động.
Đảm bảo cảm biến dò line được gắn chính xác và song song với mặt đất để đạt hiệu quả tốt nhất trong việc dò đường. 
*/
#define sensor1Pin 2
#define sensor2Pin 3
#define sensor3Pin 4
#define sensor4Pin 5
#define sensor5Pin 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10
#define ENA 11
#define ENB 12

void setup() {
    pinMode(sensor1Pin, INPUT);
    pinMode(sensor2Pin, INPUT);
    pinMode(sensor3Pin, INPUT);
    pinMode(sensor4Pin, INPUT);
    pinMode(sensor5Pin, INPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    Serial.begin(9600);
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

    Serial.print("Sensors: ");
    Serial.print(sensor1);
    Serial.print(sensor2);
    Serial.print(sensor3);
    Serial.print(sensor4);
    Serial.println(sensor5);

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

    delay(100);
}
