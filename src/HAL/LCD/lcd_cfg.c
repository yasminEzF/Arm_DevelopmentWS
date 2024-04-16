/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "HAL/LCD/lcd_cfg.h"
#include "HAL/LCD/lcd.h"
#include "MCAL/GPIO/gpio.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/

#define LCD_DISP_SHIFT_OFF      0
#define LCD_CURSOR_DIR_INC		1
#define LCD_CURSOR_DIR_DEC		0
#define LCD_DISPLAY_ON          1
#define LCD_DISPLAY_OFF         0
#define LCD_CURSOR_ON           1
#define LCD_CURSOR_OFF          0
#define LCD_BLINK_ON            1
#define LCD_BLINK_OFF           0


/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/


/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/
lcdCfg_t lcdCfg = {
    .lcdPinsArr = {
        [d0] = {
            .pin = PIN_7,
            .port = PORT_A
        },
        [d1] = {
            .pin = PIN_6,
            .port = PORT_A
        },
        [d2] = {
            .pin = PIN_5,
            .port = PORT_A
        },
        [d3] = {
            .pin = PIN_4,
            .port = PORT_A
        },
        [d4] = {
            .pin = PIN_3,
            .port = PORT_A
        },
        [d5] = {
            .pin = PIN_2,
            .port = PORT_A
        },
        [d6] = {
            .pin = PIN_1,
            .port = PORT_A
        },
        [d7] = {
            .pin = PIN_0,
            .port = PORT_A
        },
        [rs] = {
            .pin = PIN_10,
            .port = PORT_A
        },
        [rw] = {
            .pin = PIN_9,
            .port = PORT_A
        },
        [e] = {
            .pin = PIN_8,
            .port = PORT_A
        }
    },
    .cursor_dir = LCD_CURSOR_DIR_INC,
    .disp_shift = LCD_DISP_SHIFT_OFF,
    .display = LCD_DISPLAY_ON,
    .cursor = LCD_CURSOR_ON,
    .blink = LCD_BLINK_ON
}; 

/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/


