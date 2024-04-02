/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "HAL/SW/sw.h"
#include "MCAL/GPIO/gpio.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/


/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/

/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/
extern const swCfg_t switches [_swsNum];

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
    
    if(sw_state) {
        uint8_t switch_state = 2;

        if(!gpio_getPinValue(switches[sw].port,switches[sw].pin,&switch_state)) {
            errorStatus = RETURN_SW_OK;
        }
        *(sw_state) = switch_state ^ switches[sw].sw_connection;
    }
    
    return errorStatus;
}

