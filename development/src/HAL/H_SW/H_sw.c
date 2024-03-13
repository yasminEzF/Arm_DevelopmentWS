/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "HAL/H_SW/H_sw.h"
#include "MCAL/GPIO/gpio.h"
//#include "SCHED/sched.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/


/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef struct 
{
    uint8_t state;
    uint8_t prev;
    uint8_t count;
}swData_t;

/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/
extern const swCfg_t switches [_swsNum];
static swData_t swData[_swsNum] = {0};

/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/

uint8_t sw_init(void) {
    uint8_t errorStatus = RETURN_SW_NOT_OK;

    gpioPin_t sw_pin;
    sw_pin.speed = SPEED_HIGH;
    sw_pin.af = AF_SYSTEM;
    for(uint8_t i = 0; i < _swsNum; i++) {
        errorStatus = RETURN_SW_NOT_OK;
        
        if(switches[i].sw_connection == SW_CONNECTION_PULLUP) {
            sw_pin.mode = MODE_IP_PU;
        }
        else if(switches[i].sw_connection == SW_CONNECTION_PULLDOWN) {
            sw_pin.mode = MODE_IP_PD;
        }        
        sw_pin.port = switches[i].port;
        sw_pin.pin = switches[i].pin;
        if(gpio_initPin(&sw_pin)) {
            break;
        }
        else {
            errorStatus = RETURN_SW_OK;
        }
    }
    return errorStatus;
}

uint8_t sw_getState(uint8_t sw, uint8_t* sw_state) {
    uint8_t errorStatus = RETURN_SW_NOT_OK;
    
    *sw_state = swData[sw].state;
    
    return errorStatus;
}

void Hsw_runnable(){
    uint8_t current = 2;
    for(uint8_t i = 0; i < _swsNum; i++) {
        if(!gpio_getPinValue(switches[i].port,switches[i].pin,&current)){
            if(swData[i].prev == current) {
                swData[i].count++;
            }
            else {
                swData[i].count = 0;
            }
            if(swData[i].count == 5) {
                swData[i].state = swData[i].prev ^ switches[i].sw_connection;
            }
            swData[i].prev = current;
        }
        current = 2;
    }
}

