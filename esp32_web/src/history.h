#pragma once
#include <Arduino.h>

void historyAdd(String dir, int speed);   // thêm 1 lệnh
String historyGet();                      // lấy chuỗi 10 lệnh để hiển thị