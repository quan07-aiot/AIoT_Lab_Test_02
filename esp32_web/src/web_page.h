#pragma once
#include <Arduino.h>

const char PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Car</title>
</head>
<body style="text-align:center; font-family:sans-serif">
  <h2>Điều khiển xe</h2>

  <button onclick="send('UP')">TRÊN</button><br>
  <button onclick="send('LEFT')">TRÁI</button>
  <button onclick="send('STOP')">DỪNG</button>
  <button onclick="send('RIGHT')">PHẢI</button><br>
  <button onclick="send('DOWN')">DƯỚI</button>

  <p>Tốc độ: <b id="val">50</b></p>
  <input type="range" id="speed" min="0" max="100" value="50" oninput="changeSpeed()">

  <p><input type="checkbox" id="show" onchange="toggle()"> Hiển thị 10 lệnh gần nhất</p>
  <pre id="log" style="display:none"></pre>

<script>
  var dir = 'STOP';

  function send(d) {
    dir = d;
    var s = document.getElementById('speed').value;
    fetch('/control?dir=' + dir + '&speed=' + s).then(loadLog);
  }

  function changeSpeed() {
    document.getElementById('val').innerText = document.getElementById('speed').value;
    send(dir);
  }

  function loadLog() {
    if (!document.getElementById('show').checked) return;
    fetch('/history').then(r => r.text()).then(t => {
      document.getElementById('log').innerText = t;
    });
  }

  function toggle() {
    var on = document.getElementById('show').checked;
    document.getElementById('log').style.display = on ? 'block' : 'none';
    loadLog();
  }
</script>
</body>
</html>
)rawliteral";