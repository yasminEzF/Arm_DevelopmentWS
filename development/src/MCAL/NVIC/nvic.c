/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "MCAL/NVIC/nvic.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define IMPLEMENTED_BITS    

/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef struct {
    ISER0,
    ISER1,
    ISER2,
    ISER3,
    ISER4,
    ISER5,
    ISER6,
    ISER7,
    ICER0,
    ICER1,
    ICER2,
    ICER3,
    ICER4,
    ICER5,
    ICER6,
    ICER7,
    ISPR0,
    ISPR1,
    ISPR2,
    ISPR3,
    ISPR4,
    ISPR5,
    ISPR6,
    ISPR7,
    ICPR0,
    ICPR1,
    ICPR2,
    ICPR3,
    ICPR4,
    ICPR5,
    ICPR6,
    ICPR7,
    IABR0,
    IABR1,
    IABR2,
    IABR3,
    IABR4,
    IABR5,
    IABR6,
    IABR7,
    IPR0,
    IPR1,
    IPR2,
    IPR3,
    IPR4,
    IPR5,
    IPR6,
    IPR7,
    STIR
}nvic_t;

/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/


/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/
uint8_t nvic_cfgIntProirity(interrupt,preempt_priority,subgp_priority);
uint8_t nvic_enableInt(interrupt);
uint8_t nvic_disableInt(interrupt);
uint8_t nvic_setPending(interrupt);
uint8_t nvic_clrPending(interrupt);
uint8_t nvic_getIntStatus(interrupt);
uint8_t nvic_cfgSubgpBits(subgp);
uint8_t nvic_genSwInt(interrupt);

