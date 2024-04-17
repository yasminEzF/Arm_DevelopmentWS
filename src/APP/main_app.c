#include"APP/app_defines.h"

#include"SCHED/sched.h"

#include"HAL/H_SW/H_sw.h"
#include"HAL/LCD/lcd.h"

#include"MCAL/RCC/rcc.h"

#include"MCAL/GPIO/gpio.h"
#include"MCAL/NVIC/nvic.h"

#include"MCAL/USART/USART.h"

void incCursor();
void decCursor();
/*****************************************************************************/
/*                              Module Task                                  */
/*****************************************************************************/
uint8_t state = APP_STATE_CLOCK;
uint8_t stopwatchState = STOPWATCH_STATE_RESET;
uint8_t clockState = CLOCK_STATE_DISPLAY;

uint8_t pressedKey_id = _swsNum;
uint8_t pressedKey_sendId = _swsNum;

User_Request_t Tx;
User_Request_t Rx;

uint8_t Tx_buf[1] = {_swsNum};
uint8_t Rx_buf[1] = {_swsNum};

uint64_t timestamp = 0;
uint64_t stopwatchTime = 0;

uint8_t hrs;
uint8_t min;
uint8_t sec;
// uint8_t day;
// uint8_t month;
// uint8_t year;

uint8_t i_cursor = 0;

uint8_t clock[32] = "Date 12-04-2024 Clock 00:00:00  ";
uint8_t stopwatch[32] = "  00:00:00.00                   ";

#define NULL    (void *)0

void lcdCBF(){
    lcd_setCursorAsync(i_cursor%16,i_cursor/16,NULL);
    // doneFlag = DONE;
}

void setCursorBlink(uint8_t cursor_state){
    lcd_blinkCursorAsync(cursor_state,NULL);
}
void incCursor(){
    i_cursor++;
    if(i_cursor == 32){
        i_cursor = 0;
    }
    // lcd_setCursorAsync(i_cursor%16,i_cursor/16,NULL);
}
void decCursor(){
    if(i_cursor == 0){
        i_cursor = 32;
    }
    i_cursor--;
    // lcd_setCursorAsync(i_cursor%16,i_cursor/16,NULL);
}

static uint8_t numToAscii(uint8_t num){
    return num + 48;
}

void updateState(){
    USART_ReceiveBufferAsync(&Rx);
    switch(state){
        case APP_STATE_CLOCK:
            clock[22] = numToAscii(hrs / 10);
            clock[23] = numToAscii(hrs % 10);
            clock[25] = numToAscii(min / 10);
            clock[26] = numToAscii(min % 10);
            clock[28] = numToAscii(sec / 10);
            clock[29] = numToAscii(sec % 10);
            lcd_writeStringXYAsync(clock,32,0,0,lcdCBF);
            // lcd_setCursorAsync(i_cursor%16,i_cursor/16,NULL);
            if(pressedKey_id == sw_mode){
                state = APP_STATE_STOPWATCH;
            }
            else{
                switch(clockState){
                    case CLOCK_STATE_DISPLAY:
                        setCursorBlink(CURSOR_STATE_OFF);
                        if(pressedKey_id == sw_edit_reset){
                            clockState = CLOCK_STATE_EDIT;
                        }
                        break;
                    case CLOCK_STATE_EDIT:
                    {
                        setCursorBlink(CURSOR_STATE_ON);
                        // lcd_setCursorAsync(i_cursor%16,i_cursor/16,NULL);
                        if(pressedKey_id == sw_ok_start){
                            clockState = CLOCK_STATE_DISPLAY;
                        }
                        else if(pressedKey_id == sw_right) {
                            // incCursor();
                            i_cursor++;
                            if(i_cursor == 32){
                                i_cursor = 0;
                            }
                        }
                        else if(pressedKey_id == sw_left){
                            // decCursor();
                            if(i_cursor == 0){
                                i_cursor = 32;
                            }
                            i_cursor--;
                        }
                        else if(pressedKey_id == sw_up){
                            if(i_cursor == 22){
                                if(clock[i_cursor] == 9){
                                    timestamp -= 9 * 36000000;
                                }
                                else {
                                    timestamp += 36000000;
                                }
                            }
                            else if(i_cursor == 23){
                                if(clock[i_cursor] == 9){
                                    timestamp -= 9 * 3600000;
                                }
                                else {
                                    timestamp += 3600000;
                                }
                            }
                            else if(i_cursor == 25){
                                if(clock[i_cursor] == 9){
                                    timestamp -= 9 * 600000;
                                }
                                else {
                                    timestamp += 600000;
                                }
                            }
                            else if(i_cursor == 26){
                                if(clock[i_cursor] == 9){
                                    timestamp -= 9 * 60000;
                                }
                                else {
                                    timestamp += 60000;
                                }
                            }
                            else if(i_cursor == 28){
                                if(clock[i_cursor] == 9){
                                    timestamp -= 9 * 10000;
                                }
                                else {
                                    timestamp += 10000;
                                }
                            }
                            else if(i_cursor == 29){
                                if(clock[i_cursor] == 9){
                                    timestamp -= 9 * 1000;
                                }
                                else {
                                    timestamp += 1000;
                                }
                            }
                        }
                        else if(pressedKey_id == sw_down){
                            if(i_cursor == 22){
                                if(clock[i_cursor] == 0){
                                    timestamp += 9 * 36000000;
                                }
                                else {
                                    timestamp -= 36000000;
                                }
                            }
                            else if(i_cursor == 23){
                                if(clock[i_cursor] == 0){
                                    timestamp += 9 * 3600000;
                                }
                                else {
                                    timestamp -= 3600000;
                                }
                            }
                            else if(i_cursor == 25){
                                if(clock[i_cursor] == 0){
                                    timestamp += 9 * 600000;
                                }
                                else {
                                    timestamp -= 600000;
                                }
                            }
                            else if(i_cursor == 26){
                                if(clock[i_cursor] == 0){
                                    timestamp += 9 * 60000;
                                }
                                else {
                                    timestamp -= 60000;
                                }
                            }
                            else if(i_cursor == 28){
                                if(clock[i_cursor] == 0){
                                    timestamp += 9 * 10000;
                                }
                                else {
                                    timestamp -= 10000;
                                }
                            }
                            else if(i_cursor == 29){
                                if(clock[i_cursor] == 0){
                                    timestamp += 9 * 1000;
                                }
                                else {
                                    timestamp -= 1000;
                                }
                            }
                        }
                    }
                    break;
                }
            }
            break;
        case APP_STATE_STOPWATCH:
            stopwatch[2] = numToAscii(((stopwatchTime / (1000 * 60 * 60)) % 24) / 10);
            stopwatch[3] = numToAscii(((stopwatchTime / (1000 * 60 * 60)) % 24) % 10);
            stopwatch[5] = numToAscii(((stopwatchTime / (1000 * 60)) % 60) / 10);    
            stopwatch[6] = numToAscii(((stopwatchTime / (1000 * 60)) % 60) % 10);
            stopwatch[8] = numToAscii(((stopwatchTime / 1000) % 60) / 10);
            stopwatch[9] = numToAscii(((stopwatchTime / 1000) % 60) % 10);
            stopwatch[11] = numToAscii(((stopwatchTime / 10) % 100) / 10);
            stopwatch[12] = numToAscii(((stopwatchTime / 10) % 100) % 10);
            lcd_writeStringXYAsync(stopwatch,32,0,0,NULL);
            setCursorBlink(CURSOR_STATE_OFF);
            if(pressedKey_id == sw_mode){
                state = APP_STATE_CLOCK;
            }
            else{
                switch(stopwatchState){
                    case STOPWATCH_STATE_RESET:
                        stopwatchTime = 0;
                        if(pressedKey_id == sw_ok_start){
                            stopwatchState = STOPWATCH_STATE_RUN;
                        }
                        break;
                    case STOPWATCH_STATE_RUN:
                        
                        // if(pressedKey_id == sw_edit_reset){
                        //     stopwatchState = STOPWATCH_STATE_RESET;
                        // }
                        if(pressedKey_id == sw_ok_start){
                            stopwatchState = STOPWATCH_STATE_PAUSE;
                        }
                        break;
                    case STOPWATCH_STATE_PAUSE:
                        if(pressedKey_id == sw_edit_reset){
                            stopwatchState = STOPWATCH_STATE_RESET;
                        }
                        else if(pressedKey_id == sw_ok_start){
                            stopwatchState = STOPWATCH_STATE_RUN;
                        }
                        break;
                }
            }   
            break;     
    }
    USART_ReceiveBufferAsync(&Rx);
}

/* work at released */
void getPressed(){
    uint8_t SW_state = SW_STATE_RELEASED;
    static uint8_t prev_pressed = _swsNum;
    uint8_t pressed_flag = 0;
    for(uint8_t i = 0; i < _swsNum; i++){
        hsw_getState(i,&SW_state);
        if(SW_state == SW_STATE_PRESSED){
            pressed_flag = 1;
            prev_pressed = i;
        }
    }
    if(pressed_flag ||(prev_pressed == _swsNum)){
        pressedKey_sendId = _swsNum;
    }
    else if((!pressed_flag) && (prev_pressed != _swsNum)) { /* currently sw released but previously was pressed */
        hsw_getState(prev_pressed,&SW_state);
        if(SW_state == SW_STATE_RELEASED){
            pressedKey_sendId = prev_pressed;
            Tx.Ptr_Buffer[0] = prev_pressed;
            USART_SendBufferAsync(&Tx);
            prev_pressed = _swsNum;
        }
    }
}

void tx_cbf(){
    Tx.Ptr_Buffer[0] = _swsNum;
}

void rx_cbf(){
    if(Rx.Ptr_Buffer[0] != _swsNum) {
        pressedKey_id = Rx.Ptr_Buffer[0];
    }
}

void updateTime(){
    timestamp += 6;
    hrs = (timestamp / (1000 * 60 * 60)) % 24;
    min = (timestamp / (1000 * 60)) % 60;
    sec = (timestamp / 1000) % 60;
    if(stopwatchState == STOPWATCH_STATE_RUN){
        stopwatchTime += 6;
    }
}


/*****************************************************************************/
/*                                  Main                                     */
/*****************************************************************************/
int main() {
    
    rcc_enableClk(CLOCK_HSI);
    uint8_t res;
    rcc_getClkStatus(CLOCK_HSI,&res);
    while(res != CLK_READY);
    rcc_selectSysClk(SYSCLK_HSI);
    // rcc_configAHB(AHB_PRE_1);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOA,PERIPH_STATE_ENABLED);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOB,PERIPH_STATE_ENABLED);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOC,PERIPH_STATE_ENABLED);
    rcc_controlAHB1Peripheral(AHB1_PERIPH_GPIOD,PERIPH_STATE_ENABLED);
    
    hsw_init();
    lcd_initAsync();

    rcc_controlAPB2Peripheral(APB2_PERIPH_USART1,PERIPH_STATE_ENABLED);
    

	gpioPin_t UART_PINS[2]={
			//tx
			[0]= {
                .mode = MODE_AF_PP,
                .port = PORT_A,
                .pin = PIN_9,
                .speed = SPEED_HIGH,
                .af = AF_USART_1_2
            },
			//rx
            [1]= {
                .mode= MODE_AF_PP,
                .port=PORT_A,
                .pin=PIN_10,
                .speed=SPEED_HIGH,
                .af = AF_USART_1_2
            }
	};
    gpio_initPin(&UART_PINS[0]);
	gpio_initPin(&UART_PINS[1]);

    nvic_enableInt(IRQ_USART1);

    
	Tx.Ptr_Buffer = Tx_buf;
	Tx.USART_Num = USART_1;
	Tx.CallBack = tx_cbf;
    Tx.Length = 1;

    Rx.Ptr_Buffer = Rx_buf;
 	Rx.USART_Num = USART_1;
 	Rx.CallBack = rx_cbf;
    Rx.Length = 1;

    // USART_SendBufferAsync(&Tx);

    USART_Init();

    sched_init();
    sched_start();

}
