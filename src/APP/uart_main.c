#include"APP/app.h"

#if(APP == UART_APP)

/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include"MCAL/RCC/rcc.h"
#include"HAL/LED/led.h"
#include "SCHED/sched.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/


/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef enum {
    traffic_state_red,
    traffic_state_yellow,
    traffic_state_green
}traffic_state_t;

/*****************************************************************************/
/*                                  App Task                                 */
/*****************************************************************************/
/* uart light task */
/*        mS         */
void App_task(){
    
}

int main() {
    
    rcc_enableClk(CLOCK_HSI);
    uint8_t res;
    rcc_getClkStatus(CLOCK_HSI,&res);
    if(res == CLK_READY) {
        rcc_selectSysClk(SYSCLK_HSI);
    }
    rcc_configAHB(AHB_PRE_2);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOA,PERIPH_STATE_ENABLED);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOB,PERIPH_STATE_ENABLED);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOC,PERIPH_STATE_ENABLED);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOD,PERIPH_STATE_ENABLED);
    
    
    sched_init();
    sched_start();

}



#endif