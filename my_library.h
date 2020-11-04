#ifndef MY_LIBRARY
#define MY_LIBRARY

#include "Arduino.h"
#include "dht11.h"
#include "string.h"

#define MY_LIBRARY_VERSION "1.0.0"

#define OK     1
#define ERROR  0

#define YELLOW 8   //yellow output led
#define RED    9   //red output led
#define DHT11  2   //dht11 sensor red pin
#define BUZZER 3   //buzzer output pin
#define BUTTON 4   //button read pin
#define RGB_B  10  //rgb module blue output led
#define RGB_G  11  //rgb module green output led
#define RGB_R  12  //rgb module red output led
#define LDR    A0  //ldr analog read pin
#define POT    A1  //potentiometer analod read pin

class myLibrary{
    public:
        void setup_gpio(void);
        void yellow_led_write(bool val);
        void red_led_write(bool val);        
        void buzzer_write(bool val);        
        void buzzer_run(void);
        uint16_t pot_read(void);
        uint16_t ldr_read(void);
        bool button_status(void); 
        void rgb_run(uint8_t r,uint8_t g,uint8_t b);
        float read_temperature(void);
        float read_humidity(void);
        void button_event(void);
};



#endif
