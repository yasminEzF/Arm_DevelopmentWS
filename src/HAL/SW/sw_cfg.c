/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "HAL/SW/sw_cfg.h"
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
const swCfg_t switches[_swsNum] = {
    [sw_up] = {
        .port = PORT_B,
        .pin = PIN_9,
        .sw_connection = SW_CONNECTION_PULLDOWN
    },
    [sw_down] = {
        .port = PORT_B,
        .pin = PIN_10,
        .sw_connection = SW_CONNECTION_PULLDOWN
    },
    [sw_right] = {
        .port = PORT_B,
        .pin = PIN_8,
        .sw_connection = SW_CONNECTION_PULLDOWN
    },
    [sw_left] = {
        .port = PORT_B,
        .pin = PIN_12,
        .sw_connection = SW_CONNECTION_PULLDOWN
    },
    [sw_edit_reset] = {
        .port = PORT_B,
        .pin = PIN_2,
        .sw_connection = SW_CONNECTION_PULLDOWN
    },
    [sw_ok_start] = {
        .port = PORT_B,
        .pin = PIN_1,
        .sw_connection = SW_CONNECTION_PULLDOWN
    },
    [sw_mode] = {
        .port = PORT_B,
        .pin = PIN_0,
        .sw_connection = SW_CONNECTION_PULLDOWN
    }
};

/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/


