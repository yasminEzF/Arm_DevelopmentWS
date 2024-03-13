/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "SCHED/sched.h"
#include "RUNNABLES/runnables.h"
#include "MCAL/SYSTCK/systck.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/


/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/


/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/
extern const runnable_t runnables[_runsNum];
static uint8_t pendingTicks = 0;
static uint64_t timeStamp = 0;

/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/
static uint8_t sched();
static uint8_t tickCallBack();
/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/
uint8_t sched_init() {
    systck_cfgMode();
    systck_setCallBck(tickCallBack);
    systck_setTime_mS((uint64_t)SCHED_TIME_MS);
}
uint8_t sched_start() {
    systck_start();
    while(1){
        if(pendingTicks) {
            pendingTicks--;
            sched();
        }
    }
}
static uint8_t sched() {
    timeStamp++;
    for(uint8_t i = 0; i < _runsNum; i++) {
        if(!(timeStamp % runnables[i].period_mS)) {
            runnables[i].callBck();
        }
    }
}
static uint8_t tickCallBack() {
    pendingTicks++;
}
