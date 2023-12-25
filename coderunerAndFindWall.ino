#include <Servo.h>

Servo ultrasonicServo; // تعریف یک شیء از کلاس Servo برای کنترل سرووموتور
const int trigPin = 7; // پین تریگر سنسور اولتراسونیک
const int echoPin = 8; // پین اکو سنسور اولتراسونیک
const int motor1Pin1 = 2; // پین اتصال موتور 1
const int motor1Pin2 = 3; // پین اتصال موتور 2
const int enB =5; 
const int enA =10;
bool wallDetected = false; // تعریف یک متغیر برای ذخیره وضعیت شناسایی دیوار

void setup() {
  ultrasonicServo.attach(9); // متصل کردن سرووموتور به پین 9
  pinMode(trigPin, OUTPUT); // تنظیم پین تریگر به عنوان خروجی
  pinMode(echoPin, INPUT); // تنظیم پین اکو به عنوان ورودی
  pinMode(motor1Pin1, OUTPUT); // تنظیم پین‌های موتورها به عنوان خروجی
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  analogWrite(enA, 150); 
	analogWrite(enB, 150);

  Serial.begin(9600); // شروع ارتباط با سریال برای نمایش اطلاعات
}

void loop() {
  moveForwardUntilNoWall(); // حرکت به جلو تا زمانی که دیواری رو به رو نباشد
  delay(2000); // توقف به مدت 2 ثانیه
  moveBackward(); // حرکت به عقب
  delay(2000); // توقف به مدت 2 ثانیه
  stopRobot(); // توقف حرکت ربات
  delay(2000); // توقف به مدت 2 ثانیه
}

void checkDistance() {
  long duration, distance;

  for (int servoAngle = 90; servoAngle >= 0; servoAngle -= 10) {
    ultrasonicServo.write(servoAngle); // چرخش سرووموتور به زاویه مورد نظر
    delay(500); // تاخیر برای رسیدن سرووموتور به زاویه مورد نظر

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration * 0.034) / 2;

    Serial.print("Angle: ");
    Serial.print(servoAngle);
    Serial.print(" degrees, Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance <= 10) {
      Serial.println("Wall detected at angle: " + String(servoAngle) + " degrees");
      stopRobot(); // توقف حرکت ربات در صورت نزدیک شدن به دیوار
      delay(1000); // تاخیر برای انجام عملیات بعدی

      wallDetected = true;
      break;
    }
  }

  if (!wallDetected) {
    Serial.println("No wall detected");
  }
  
  delay(1000); // تاخیر بین اندازه‌گیری‌ها
}

void moveForward() {
  digitalWrite(motor1Pin1, HIGH); // حرکت موتور 1 به جلو
  digitalWrite(motor1Pin2, LOW); // توقف حرکت موتور 2
}

void moveBackward() {
  digitalWrite(motor1Pin1, LOW); // توقف حرکت موتور 1
  digitalWrite(motor1Pin2, HIGH); // حرکت موتور 2 به عقب
}

void stopRobot() {
  digitalWrite(motor1Pin1, LOW); // توقف حرکت موتور 1
  digitalWrite(motor1Pin2, LOW); // توقف حرکت موتور 2
}

void moveForwardUntilNoWall() {
  wallDetected = false; // تنظیم مجدد وضعیت شناسایی دیوار

  while (true) {
    checkDistance(); // بررسی فاصله از دیوار
    moveForward(); // حرکت به جلو

    // اگر دیوار رو به رو نبود، ادامه حرکت
    if (!wallDetected) {
      continue;
    } else {
      break; // اگر دیوار رو به رو بود، خروج از حلقه و توقف حرکت به جلو
    }
  }
}
