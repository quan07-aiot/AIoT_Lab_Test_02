#include <WebServer.h>
#include "web_server.h"
#include "web_page.h"
#include "car.h"
#include "history.h"

WebServer server(80);

void handleRoot() {                     
  server.send(200, "text/html", PAGE);
}

void handleControl() {                  
  String dir = server.arg("dir");
  int speed = constrain(server.arg("speed").toInt(), 0, 100);

  carMove(dir, speed);                  
  historyAdd(dir, speed);                
  server.send(200, "text/plain", "OK");
}

void handleHistory() {               
  server.send(200, "text/plain", historyGet());
}

void serverInit() {
  server.on("/", handleRoot);
  server.on("/control", handleControl);
  server.on("/history", handleHistory);
  server.begin();
}

void serverRun() {
  server.handleClient();
}