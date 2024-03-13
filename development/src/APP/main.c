#include"MCAL/RCC/rcc.h"
#include"HAL/LED/led.h"
#include"HAL/SW/sw.h"

int main(){

    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOA,PERIPH_STATE_ENABLED);

    led_init();
    sw_init();

    while(1){

        
        uint8_t sw_state;
        sw_getState(sw_red,&sw_state);
        if(sw_state == SW_STATE_PRESSED){
            led_setState(led_red,LED_STATE_ON);
        }
        else {
            led_setState(led_red,LED_STATE_OFF);
        }

        sw_getState(sw_green,&sw_state);
        if(sw_state == SW_STATE_PRESSED){
            led_setState(led_green,LED_STATE_ON);
        }
        else {
            led_setState(led_green,LED_STATE_OFF);
        }
        sw_getState(sw_blue,&sw_state);
        if(sw_state == SW_STATE_PRESSED){
            led_setState(led_blue,LED_STATE_ON);
        }
        else {
            led_setState(led_blue,LED_STATE_OFF);
        }
        sw_getState(sw_yellow,&sw_state);
        if(sw_state == SW_STATE_PRESSED){
            led_setState(led_yellow,LED_STATE_ON);
        }
        else {
            led_setState(led_yellow,LED_STATE_OFF);
        }
    }
}