#ifndef NVIC_H_
#define NVIC_H_

/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include <stdint.h>
#include "LIB/STM32F401CC_interrupts.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/


/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/



/*****************************************************************************/
/*                          Function Prototypes                              */
/*****************************************************************************/
uint8_t nvic_cfgIntProirity(irq,preempt_priority,subgp_priority);
uint8_t nvic_enableInt(irq);
uint8_t nvic_disableInt(irq);
uint8_t nvic_setPending(irq);
uint8_t nvic_clrPending(irq);
uint8_t nvic_getIntStatus(irq);
uint8_t nvic_cfgSubgpBits(subgp);
uint8_t nvic_genSwInt(irq);


#endif /* NVIC_H_ */