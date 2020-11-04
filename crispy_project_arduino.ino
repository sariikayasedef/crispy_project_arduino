/*############################################
############### Sedef SARIKAYA ###############
########## Crispy Project to Try :D ##########
############################################*/
#include "my_library.h";
// myLibrary class call
myLibrary ml; 
//veriables
bool button_run_status;
bool pot_chk,temp_chk,ldr_chk;
uint16_t pot_val = 0;
uint16_t temp_val = 0;
uint16_t ldr_val = 0;
int read_val =0;
byte send_data[15] = {0};

void setup() {
    Serial.begin(115200); // Serial Communication Start with Baud Rate 115200
    ml.setup_gpio(); //setup gpio configuration
    button_run_status = false;
    pot_chk=false;
    temp_chk=false;
    ldr_chk=false;
}

void loop() { 
    memset(send_data,0,15);
    send_data[0]=0x7E; //header data packet
    if(Serial.available()){
        read_val=Serial.parseInt(Serial.read()); 
        switch(read_val){
            case 0x00: ml.yellow_led_write(1);   break;
            case 0x01: ml.yellow_led_write(0);   break;
            case 0x02: ml.red_led_write(1);      break;
            case 0x03: ml.red_led_write(0);      break;
            case 0x04: ml.rgb_run(1,0,0);        break;
            case 0x05: ml.rgb_run(0,0,0);        break;
            case 0x06: ml.rgb_run(0,1,0);        break;
            case 0x07: ml.rgb_run(0,0,0);        break;
            case 0x08: ml.rgb_run(0,0,1);        break;
            case 0x09: ml.rgb_run(0,0,0);        break;
            case 0x0A: ml.buzzer_run();          break;
            case 0x0B: pot_chk=true;             break;
            case 0x0C: temp_chk=false;           break;
            case 0x0D: ldr_chk=false;            break;
            case 0x0E: button_run_status = true; break;
        }
    }
    if(pot_chk){
        pot_val= ml.pot_read();
        send_data[1]=0x10;       //id for pot
        send_data[2]=pot_val>>8; //first  msb
        send_data[3]=pot_val;    //second lsb
    }
    if(temp_chk){
        temp_val= ml.read_temperature();
        send_data[4]=0x11;        //id for temp
        send_data[5]=temp_val>>8; //first  msb
        send_data[6]=temp_val;    //second lsb
    }
    if(temp_chk){
        ldr_val= ml.ldr_read();
        send_data[7]=0x12;       //id for ldr
        send_data[8]=ldr_val>>8; //first  msb
        send_data[9]=ldr_val;    //second lsb
    }
    if(button_run_status){
      int read_button=digitalRead(BUTTON);
      if(read_button){
          ml.button_event();          
          send_data[10]=0x01;
      }
    }
    send_data[14]=0xEE; //end data packet
    delay(250);
    Serial.write(send_data,15);
}
