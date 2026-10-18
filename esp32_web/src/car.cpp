#include "car.h"

// Chân an toàn trên ESP32-S3 N16R8 (nối với L298N)
const int L_EN = 4,  L_IN1 = 5,  L_IN2 = 6;    // bánh trái
const int R_EN = 7,  R_IN1 = 15, R_IN2 = 16;   // bánh phải

// Kênh PWM (chỉ dùng cho core 2.x)
const int L_CH = 0, R_CH = 1;

// Điều khiển 1 bánh: speed từ -100 đến 100
void setWheel(int en, int ch, int in1, int in2, int speed) {
  if (speed > 0) {            // tiến
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (speed < 0) {     // lùi
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else {                    // dừng
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }

  int duty = map(abs(speed), 0, 100, 0, 255);   // đổi 0-100 thành 0-255
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcWrite(en, duty);        // core 3.x: ghi theo chân
#else
  ledcWrite(ch, duty);        // core 2.x: ghi theo kênh
#endif
}

void carInit() {
  pinMode(L_IN1, OUTPUT);  pinMode(L_IN2, OUTPUT);
  pinMode(R_IN1, OUTPUT);  pinMode(R_IN2, OUTPUT);

#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcAttach(L_EN, 1000, 8);
  ledcAttach(R_EN, 1000, 8);
#else
  ledcSetup(L_CH, 1000, 8);   ledcAttachPin(L_EN, L_CH);
  ledcSetup(R_CH, 1000, 8);   ledcAttachPin(R_EN, R_CH);
#endif
}

void carMove(String dir, int speed) {
  int slow = speed * 2 / 5;          // 2/5 tốc độ
  int fast = speed * 8 / 5;          // 8/5 tốc độ
  if (fast > 100) fast = 100;        // không vượt quá 100

  int left = 0, right = 0;           // mặc định: dừng

  if      (dir == "UP")    { left = speed;  right = speed;  }
  else if (dir == "DOWN")  { left = -speed; right = -speed; }
  else if (dir == "LEFT")  { left = slow;   right = fast;   }
  else if (dir == "RIGHT") { left = fast;   right = slow;   }

  setWheel(L_EN, L_CH, L_IN1, L_IN2, left);
  setWheel(R_EN, R_CH, R_IN1, R_IN2, right);

  Serial.printf("Banh trai = %d, Banh phai = %d\n", left, right);
}