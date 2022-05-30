# STM to internet

## Задание

Есть два устройства одно с кнопкой и потенциометром, второе со светодиодной лентой. Реализуйте общение двух устройств по сценарию:

1. Нажатие кнопки -> включение/выключение света
2. Регулировка потенциометра -> изменение яркости 

ESP использовать только для связи. Управление датчиками и светодиодной лентой сделать с помощью STM 

### Для проверки связи STM32 и ESP

> Питание ESP осуществить подключив Main Power с PINBOARD на Vin ESP.

На стороне ESP

```c++
void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {     
    delay(50);
    Serial.println("Echo from ESP");
    while (Serial.available())
      Serial.write(Serial.read());  
    Serial.println();
  }
}
```

На стороне STM

```c++
#include "mbed.h"
#define MAXIMUM_BUFFER_SIZE 32
static BufferedSerial serial_port(PA_9, PA_10);
static BufferedSerial esp_serial(PA_2, PA_3);
int main(void)
{
  serial_port.set_baud(9600);
  serial_port.set_format(8, BufferedSerial::None, 1);
  esp_serial.set_baud(9600);
  esp_serial.set_format(8, BufferedSerial::None, 1);
  char buf[MAXIMUM_BUFFER_SIZE] = {0};
  while (1) {
    if (uint32_t num = serial_port.read(buf, sizeof(buf))) {
        esp_serial.write(buf, num);
    }
    ThisThread::sleep_for(100ms);
    if (uint32_t num = esp_serial.read(buf, sizeof(buf))) {
        serial_port.write(buf, num);
    }

  }
}
```

### Конвертация Serial-MQTT

[Дополните скетч ESP чтобы обрабатывать данные приходящие с STM и отправлять их по MQTT](https://github.com/vesninam/esp_network_mqtt/blob/main/esp_networking.ino)

```c++
void publish_when_available() {

  while(Serial.available() > 1) {
    String topic = "";
    char source = Serial.read();
    char val = Serial.read();
    if(source == 'b')
       topic = "Light/Switch";
    else if(source == 'p')
       topic = "Light/Brightness";
    if(topic != "")
       mqtt_cli.publish(topic, String((int) val));
  }

}
```

```c++
void callback(char *topic, byte *payload, unsigned int length) {
   
    char source = ' ';
    if(strcmp(topic, "Light/Switch") == 0)
       source = 'b';
    else if(strcmp(topic, "Light/Brightness") ==0 )
       source == 'p';
    int data = 0;
    int order = 1;
    for (int i = length -1 ; i >= 0; i--) {
      data += int((char) payload[i]) * order;
      order *= 10;
    }
    if(source != ' ' and data < 256 and data > 0) {
      Serial.write(source);
      Serial.write((char)data);
    }
}
```

