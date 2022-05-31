#include "Config.h"
#include "WIFI.h"
#include "MQTT.h"


void setup(){
  Serial.begin(9600);
  pinMode(led, 0);
  WIFI_init(false);
  MQTT_init();
  mqtt_cli.publish("xitowzys-stm32-to-esp/state", "Start ESP8266");
  pinMode(led, 1);
}

void loop(){               
  // mqtt_cli.loop();

  if (Serial.available() > 0) {     

    // while (Serial.available()) {
    //   int symbol = Serial.read();
    //   Serial.println(symbol);
    //   mqtt_cli.publish("xitowzys-stm32-to-esp/state", String(symbol).c_str()); 
    //   delay(500);
    // }

    int symbol = Serial.read();
    Serial.println(String(symbol).c_str());
    mqtt_cli.publish("xitowzys-stm32-to-esp/brightness", String(symbol).c_str()); 
    // delay(500);

    symbol = Serial.read();
    Serial.println(String(symbol).c_str());
    mqtt_cli.publish("xitowzys-stm32-to-esp/status", String(symbol).c_str()); 

    // delay(500);

    // delay(1000);
  }
}