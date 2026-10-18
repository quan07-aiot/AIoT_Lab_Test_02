#include "history.h"

String lines[10];   
int n = 0;         

void historyAdd(String dir, int speed) {
  if (n == 10) {                      
    for (int i = 0; i < 9; i++) {
      lines[i] = lines[i + 1];        
    }
    n = 9;
  }
  lines[n] = "DIR: " + dir + " SPEED: " + String(speed);
  n++;
}

String historyGet() {
  String out = "";
  for (int i = n - 1; i >= 0; i--) {   
    out += lines[i] + "\n";            
  }
  return out;
}