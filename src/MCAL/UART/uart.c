/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include "MCAL/UART/uart.h"
#include "LIB/bitMasks.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define NUM_UART_PERIPH         3

#define USART6_BASE         (0x40011400)
#define USART1_BASE         (0x40011000)
#define USART2_BASE         (0x40014400)

#define TXE_MASK            BIT7_MASK
#define RXNE_MASK            BIT5_MASK


/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/
typedef void (*callback_t)(void);
typedef enum {
    state_busy,
    state_ready
}state_t;

typedef struct {
    uint32_t SR;
    uint32_t DR;
    uint32_t BRR;
    uint32_t CR1;
    uint32_t CR2;
    uint32_t CR3;
    uint32_t GTPR;
}usart_t;

typedef struct{
    uint32_t* data;
    uint16_t current_index;
    uint16_t len;
}buffer_t;

typedef struct {
    buffer_t buffer;
    state_t state;
    callback_t callback;
}txUsrReq_t;

typedef struct {
    buffer_t buffer;
    state_t state;
    callback_t callback;
}rxUsrReq_t;


/*****************************************************************************/
/*                           Global Variables                                */
/*****************************************************************************/
static volatile usart_t* const usart[NUM_UART_PERIPH] = {
    [USART1] = (usart_t*)USART1_BASE,
    [USART2] = (usart_t*)USART2_BASE,
    [USART6] = (usart_t*)USART6_BASE
};
txUsrReq_t txUsrReq[NUM_UART_PERIPH];
rxUsrReq_t rxUsrReq[NUM_UART_PERIPH];


/*****************************************************************************/
/*                      Static Function Prototypes                           */
/*****************************************************************************/

/*****************************************************************************/
/*                           Implementation                                  */
/*****************************************************************************/
void uart_sendByte(uint8_t byte);
void uart_recByte(uint8_t* byte);

void uart_txBuffAsync(uint32_t* buff, uint16_t len);
void uart_txBuff(uint32_t* buff, uint16_t len) {
    if(txUsrReq->state == state_ready) {

    }
}

void uart_rxBuffAsync();
void uart_rxBuff();

void USART_handlers(uint8_t usart_id){
    if(TXE_MASK & usart[usart_id]->SR) {
        if(txUsrReq[usart_id].buffer.current_index < txUsrReq[usart_id].buffer.len) {

        }
    }
    if(RXNE_MASK & usart[usart_id]->SR) {

    }
}

void USART1_Handler(){
    USART_handlers(USART1);
}
void USART2_Handler(){
    USART_handlers(USART2);
}
void USART6_Handler(){
    USART_handlers(USART6);
}