const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>ESP32 Counter</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin-top: 50px;
        }

        h1 {
            font-size: 3rem;
        }

        button {
            font-size: 2rem;
            width: 80px;
            height: 60px;
            margin: 10px;
        }
    </style>
</head>
<body>
    <h1>Counter: <span id="counter">0</span></h1>

    <button onclick="updateCounter('inc')">+</button>
    <button onclick="updateCounter('dec')">-</button>

    <script>
        function updateCounter(action) {
            fetch('/' + action)
                .then(response => response.text())
                .then(value => {
                    document.getElementById('counter').innerText = value;
                });
        }

        // Load current value when page opens
        fetch('/value')
            .then(response => response.text())
            .then(value => {
                document.getElementById('counter').innerText = value;
            });
    </script>
</body>
</html>
)rawliteral";

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "WIFI";
const char* password = "PASSWORD";

WebServer server(80);

int counter = 0;

void handleRoot() {
    server.send(200, "text/html", index_html);
}

void handleInc() {
    counter++;
    server.send(200, "text/plain", String(counter));
}

void handleDec() {
    counter--;
    server.send(200, "text/plain", String(counter));
}

void handleValue() {
    server.send(200, "text/plain", String(counter));
}

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/inc", handleInc);
    server.on("/dec", handleDec);
    server.on("/value", handleValue);

    server.begin();
}

void loop() {
    server.handleClient();
}