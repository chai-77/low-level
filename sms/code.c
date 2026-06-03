// sim t0 nano
// | sim900a | arduino nano       |
// | ------- | ------------------ |
// | tx      | d10                |
// | rx      | d11                |
// | gnd     | gnd                |
// | vcc     | 5v (stable supply) |
//
// relay to nano
// | relay | nano |
// | ----- | ---- |
// | in    | d7   |
// | vcc   | 5v   |
// | gnd   | gnd  |

#include <SoftwareSerial.h>

SoftwareSerial sim900(10, 11); // rx, tx

String msg = "";
int relayPin = 7;

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  Serial.begin(9600);
  sim900.begin(9600);

  delay(1000);

  Serial.println("starting sim900a...");

  sim900.println("AT");
  delay(1000);

  sim900.println("AT+CMGF=1"); //sms textmode
  delay(1000);

  sim900.println("AT+CNMI=1,2,0,0,0"); //show sms 
  delay(1000);
}


// send sms function
void sendSMS(String msg) {
  sim900.println("AT+CMGF=1");
  delay(100);

  sim900.println("AT+CMGS=\"+90<PHONE_NUMBER>\"");
  delay(100);

  sim900.print(msg);
  delay(100);

  sim900.write(26); //ascii code for ctrl+z to send
}

void loop() {

  // check if sim900a sent anything
  if (sim900.available()) {

    // read full incoming message first
    msg = sim900.readString();
    msg.toUpperCase();   // make it case-insensitive

    Serial.println("received:");
    Serial.println(msg);

    // if on command
    if (msg.indexOf("ON") != -1) {
      digitalWrite(relayPin, HIGH);
      Serial.println("relay on");

      sendSMS("relay is on, hello from arduino");
    }

    // if off command
    else if (msg.indexOf("OFF") != -1) {
      digitalWrite(relayPin, LOW);
      Serial.println("relay off, bye from arduinooo");

      sendSMS("relay is off");
    }

    //ignore other messages
    else {
      Serial.println("unknown command");
    }

    // clear old sms from module
    sim900.println("AT+CMGD=1,4");

    //clear variable 
    msg = "";
    delay(500);
  }
}