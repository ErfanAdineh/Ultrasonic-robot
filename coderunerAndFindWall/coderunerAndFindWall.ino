#include <Servo.h>

Servo ultrasonicServo; // تعریف یک شیء از کلاس Servo برای کنترل سرووموتور
const int trigPin = 7; // پین تریگر سنسور اولتراسونیک
const int echoPin = 8; // پین اکو سنسور اولتراسونیک
const int motor1Pin1 = 2; // پین اتصال موتور 1
const int motor1Pin2 = 3; // پین اتصال موتور 2
const int enB = 5;
const int enA = 10;
bool wallDetected = false; // تعریف یک متغیر برای ذخیره وضعیت شناسایی دیوار

void setup() {
  ultrasonicServo.attach(9); // متصل کردن سرووموتور به پین 9
  pinMode(trigPin, OUTPUT); // تنظیم پین تریگر به عنوان خروجی
  pinMode(echoPin, INPUT); // تنظیم پین اکو به عنوان ورودی
  pinMode(motor1Pin1, OUTPUT); // تنظیم پین‌های موتورها به عنوان خروجی
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  analogWrite(enA, 150);
  analogWrite(enB, 150);

  Serial.begin(9600); // شروع ارتباط با سریال برای نمایش اطلاعات
}

void loop() {
  moveForwardUntilNoWall(); // حرکت به جلو تا زمانی که دیواری رو به رو نباشد
}

void checkForceDistance() {
    for (int servoAngle = 0; servoAngle <= 180; servoAngle += 10) {
        ultrasonicServo.write(servoAngle); // چرخش سرووموتور به زاویه مورد نظر
        delay(500); // تاخیر برای رسیدن سرووموتور به زاویه مورد نظر
    }
}


void moveForward() {
  digitalWrite(motor1Pin1, HIGH); // حرکت موتور 1 به جلو
  digitalWrite(motor1Pin2, HIGH); //  به جلو حرکت  موتور 2
  delay(10000);
}

void stopRobot() {
  digitalWrite(motor1Pin1, LOW); // توقف حرکت موتور 1
  digitalWrite(motor1Pin2, LOW); // توقف حرکت موتور 2
}

void moveForwardUntilNoWall() {

    checkForceDistance(); // بررسی فاصله از دیوار
    moveForward(); // حرکت به جلو

}
