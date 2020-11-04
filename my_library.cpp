#include "my_library.h"

static dht11 dht; // temperature and humidity sensor library constructor
extern bool button_run_status;

void myLibrary::setup_gpio(void){
    pinMode(YELLOW,OUTPUT); // set output the yellow led
    pinMode(RED,OUTPUT);    // set output the red led
    pinMode(BUZZER,OUTPUT); // set output the buzzer
    pinMode(BUTTON,INPUT);  // set input the button
    pinMode(RGB_B,OUTPUT);  // set output the rgb module blue led
    pinMode(RGB_G,OUTPUT);  // set output the rgb module green led
    pinMode(RGB_R,OUTPUT);  // set output the rgb module red led
}

void myLibrary::yellow_led_write(bool val){
    digitalWrite(YELLOW,val);
}


void myLibrary::red_led_write(bool val){
    digitalWrite(RED,val);
}


void myLibrary::buzzer_write(bool val){
    digitalWrite(BUZZER,val);
}


void myLibrary::buzzer_run(void){
    for(uint8_t i=0;i<20;i++){
        this->buzzer_write(0);
        delay(1);  
        this->buzzer_write(1);
        delay(1);
    }
}

void myLibrary::rgb_run(uint8_t r,uint8_t g,uint8_t b){
    digitalWrite(RGB_R,r);
    digitalWrite(RGB_G,g);
    digitalWrite(RGB_B,b);
}

uint16_t myLibrary::pot_read(void){
    uint16_t read_val=analogRead(POT);
    return read_val;
}

uint16_t myLibrary::ldr_read(void){
    uint16_t read_val=analogRead(LDR);
    return read_val;
}

bool myLibrary::button_status(void){
    bool read_val=digitalRead(BUTTON);
    return read_val;
}

float myLibrary::read_temperature(void){    
    delay(500 );
    int dht11_chk=dht.read(DHT11);
    
    if(dht11_chk == 0){
        return (float)dht.temperature;
    }
    return ERROR;
}

float myLibrary::read_humidity(void){
    delay(500);
    int dht11_chk=dht.read(DHT11);
    
    if(dht11_chk == 0){
        return (float)dht.humidity;
    }
    return ERROR;
}

void myLibrary::button_event(void){
    this->yellow_led_write(1);
    delay(500);
    this->yellow_led_write(0);
    delay(500);
    this->red_led_write(1);
    delay(500);
    this->red_led_write(0);
    delay(500);
    this->rgb_run(1,0,0);
    delay(500);
    this->rgb_run(0,1,0);
    delay(500);
    this->rgb_run(0,0,1);
    delay(500);
    this->rgb_run(0,0,0);
    delay(500);
    this->rgb_run(1,1,1);
    delay(500);        
    this->rgb_run(0,0,0);
    button_run_status = false;          
    this->buzzer_run();
}