#include "mbed.h"
#include <chrono>

#define MAXIMUM_BUFFER_SIZE 32
static BufferedSerial serial_port(PA_9, PA_10);
static BufferedSerial esp_serial(PA_2, PA_3);
static AnalogIn ain(PA_5);
static DigitalIn button(PA_1);

FileHandle *mbed::mbed_override_console(int fd) { return &serial_port;}

int main()
{
    serial_port.set_baud(9600);
    serial_port.set_format(8, BufferedSerial::None, 1);
    esp_serial.set_baud(9600);
    esp_serial.set_format(8, BufferedSerial::None, 1);
    char buf[MAXIMUM_BUFFER_SIZE] = {0};

    button.mode(PullUp);

    bool btn_state = button.read();

    unsigned char p = ain.read_u16()>>8;

    while (1) {

        unsigned char brightness = ain.read_u16() >> 8;

        if(button.read() != btn_state) {
           btn_state = !btn_state;
        }


        buf[0] = brightness;
        buf[1] = btn_state;

        esp_serial.write(buf, 2);

        ThisThread::sleep_for(2000ms);
    }

} 