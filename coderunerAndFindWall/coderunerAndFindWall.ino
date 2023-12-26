#include <Servo.h>

Servo ultrasonicServo; // تعریف یک شیء از کلاس Servo برای کنترل سرووموتور
const int trigPin = 7; // پین تریگر سنسور اولتراسونیک
const int echoPin = 8; // پین اکو سنسور اولتراسونیک
const int IN1 = 12; // پین اتصال موتور 1
const int IN2 = 8; // پین اتصال موتور 2
const int IN3 = 11; // پین اتصال موتور 1
const int IN4 = 2; // پین اتصال موتور 2
const int enB = 5;
const int enA = 6;
bool wallDetected = false; // تعریف یک متغیر برای ذخیره وضعیت شناسایی دیوار

void setup() {
  ultrasonicServo.attach(9); // متصل کردن سرووموتور به پین 9
  pinMode(trigPin, OUTPUT); // تنظیم پین تریگر به عنوان خروجی
  pinMode(echoPin, INPUT); // تنظیم پین اکو به عنوان ورودی
  pinMode(IN1, OUTPUT); // تنظیم پین‌های موتورها به عنوان خروجی
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); // تنظیم پین‌های موتورها به عنوان خروجی
  pinMode(IN4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  Serial.begin(9600); // شروع ارتباط با سریال برای نمایش اطلاعات
}

void loop() {
  moveForwardUntilNoWall(); // حرکت به جلو تا زمانی که دیواری رو به رو نباشد
  delay(2000); 
  moveToLeft(); 
  delay(2000); 
  moveToRight();
  delay(2000); 
}

//==================================== check left

void checkDistanceLeft() {
  long duration, distance;

  wallDetected = false; // تنظیم مجدد وضعیت شناسایی دیوار

  for (int servoAngle = 0; servoAngle < 90; servoAngle += 10) {
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
    } else {
      wallDetected = false;
    }
    ultrasonicServo.write(90);
  }

  if (!wallDetected) {
    Serial.println("No wall detected");
  }

  delay(1000); // تاخیر بین اندازه‌گیری‌ها
}

//=================================== check right
void checkDistanceRight() {
  long duration, distance;

  wallDetected = false; // تنظیم مجدد وضعیت شناسایی دیوار

  for (int servoAngle = 91; servoAngle <= 180; servoAngle += 10) {
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
    } else {
      wallDetected = false;
    }
    ultrasonicServo.write(90);
  }

  if (!wallDetected) {
    Serial.println("No wall detected");
  }

  delay(1000); // تاخیر بین اندازه‌گیری‌ها
}

//================================check  force
void checkForceDistance() {
  long duration, distance;
  int servoAngle =90;
  wallDetected = false; // تنظیم مجدد وضعیت شناسایی دیوار

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

      Serial.println("Wall detected at angle: " + String(servoAngle) + " degrees");
      stopRobot(); // توقف حرکت ربات در صورت نزدیک شدن به دیوار
      delay(1000); // تاخیر برای انجام عملیات بعدی

    ultrasonicServo.write(90);


  if (!wallDetected) {
    Serial.println("No wall detected");
  }

  delay(1000); // تاخیر بین اندازه‌گیری‌ها
}


void moveForward() {
  digitalWrite(IN1, HIGH); // حرکت موتور 1 به جلو
  digitalWrite(IN2, HIGH); //  به جلو حرکت  موتور 2
}

// void moveBackward() {
//   digitalWrite(IN1, LOW); // توقف حرکت موتور 1
//   digitalWrite(IN2, HIGH); // حرکت موتور 2 به عقب
// }

void moveToRight() {
      wallDetected = false;
      checkDistance();
     if (!wallDetected) {
        {
            digitalWrite(IN1, HIGH); //   موتور 1
            digitalWrite(IN2, LOW); //  موتور 2     
        }

    }
}

void moveToLeft() {
      wallDetected = false;
      checkDistanceLeft();
     if (!wallDetected) {
        {
           digitalWrite(IN1, HIGH); // موتور راست
           digitalWrite(IN2, LOW); // موتور چپ 
        }


    }
}

void stopRobot() {
  digitalWrite(IN1, LOW); // توقف حرکت موتور 1
  digitalWrite(IN2, LOW); // توقف حرکت موتور 2
}

void moveForwardUntilNoWall() {
  wallDetected = false; // تنظیم مجدد وضعیت شناسایی دیوار

  while (true) {
    checkForceDistance(); // بررسی فاصله از دیوار
    moveForward(); // حرکت به جلو

    // اگر دیوار رو به رو نبود، ادامه حرکت
    if (!wallDetected) {
      continue;
    } else {
      stopRobots();
      break; // اگر دیوار رو به رو بود، خروج از حلقه و توقف حرکت به جلو
    }
  }
}
