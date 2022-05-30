#include "Config.h"
#include "WIFI.h"
#include "MQTT.h"


void setup(){
  Serial.begin(9600);
  pinMode(led, 0);
  // for(int i=0; i< 3; i++) {
  //   digitalWrite(led, !digitalRead(led));
  //   delay(500);
  // }
  // leds_init();
  WIFI_init(false);
  MQTT_init();
  mqtt_cli.publish("xitowzys-stm32-to-esp/state", "Start ESP8266");
  // mqtt_cli.subscribe("isu8266-00/lab/leds/strip/set_leds");
  // mqtt_cli.subscribe("isu8266-00/lab/leds/strip/set_leds_bytes");
  // mqtt_cli.subscribe("isu8266-00/lab/leds/strip/rotate_leds");
  pinMode(led, 1);
}

void loop(){               
  // mqtt_cli.loop();

  if (Serial.available() > 0) {     
    // delay(50);
    // Serial.println("Echo from ESP");
    
    while (Serial.available()) {
      int symbol = Serial.read();
      Serial.println(symbol);
      mqtt_cli.publish("xitowzys-stm32-to-esp/state", String(symbol).c_str()); 
      delay(500);
    }

    // int symbol = Serial.read();
    // Serial.println(symbol);
    // mqtt_cli.publish("xitowzys-stm32-to-esp/state", String(symbol).c_str()); 

    delay(1000);
    // Serial.println();
  }

  // if (Serial.available() > 0) {
  //   int val = Serial.parseInt();

  //   mqtt_cli.publish("xitowzys-stm32-to-esp/state", String(val).c_str()); 
  // }
}