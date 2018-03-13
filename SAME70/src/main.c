/**
 * 5 semestre - Eng. da Computação - Insper
 * Filipe Borba, Gabriel Moreira, Hugo Mendes
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 *  - Sensor de Presença
 *  - Botão Touch
 *  - LED Azul
 *  - Mini Cooler
 *  - MOSFET
 *  - Jumpers
 */

#include "asf.h"


/************************************************************************/
/* defines                                                              */
/************************************************************************/

#define LED_PIO PIOC
#define LED_PIO_ID ID_PIOC
#define LED_PIO_PIN 30
#define LED_PIO_PIN_MASK (1<< LED_PIO_PIN)

#define TOUCH_PIO PIOC
#define TOUCH_PIO_ID ID_PIOC
#define TOUCH_PIO_PIN 13
#define TOUCH_PIO_PIN_MASK (1<< TOUCH_PIO_PIN)

#define FAN_PIO PIOC
#define FAN_PIO_ID ID_PIOC
#define FAN_PIO_PIN 31
#define FAN_PIO_PIN_MASK (1<< FAN_PIO_PIN)

#define PRESENCE_PIO PIOC
#define PRESENCE_PIO_ID ID_PIOC
#define PRESENCE_PIO_PIN 17
#define PRESENCE_PIO_PIN_MASK (1<< PRESENCE_PIO_PIN)

/************************************************************************/
/* functions                                                            */
/************************************************************************/

// Flags
volatile bool fan_flag = false;
volatile bool led_flag = false;

void led_on(){
	pio_set(LED_PIO, LED_PIO_PIN_MASK);
}

void led_off(){
	pio_clear(LED_PIO, LED_PIO_PIN_MASK);
}

void fan_on(void) {
	pio_set(FAN_PIO, FAN_PIO_PIN_MASK);
}

void fan_off(void) {
	pio_clear(FAN_PIO, FAN_PIO_PIN_MASK)
}

void touch_callBack(void) {
	fan_flag = true;
}

// Funcao principal chamada na inicalizacao do uC.
int main(void){
	
	/* Initialize the board. */
	sysclk_init();
	board_init();
	ioport_init();
	
	delay_init();
	
	// Iniciando os perifericos
	pmc_enable_periph_clk(TOUCH_PIO_ID);
	pmc_enable_periph_clk(PRESENCE_PIO_ID);
	pmc_enable_periph_clk(LED_PIO_ID);
	pmc_enable_periph_clk(FAN_PIO_ID);
	
	// Configurando cada periferico
	pio_configure(TOUCH_PIO,PIO_INPUT, TOUCH_PIO_PIN_MASK, PIO_DEFAULT);
	pio_configure(PRESENCE_PIO,PIO_INPUT, PRESENCE_PIO_PIN_MASK, PIO_DEFAULT);
	pio_configure(LED_PIO,PIO_OUTPUT_0, LED_PIO_PIN_MASK, PIO_DEFAULT);
	pio_configure(FAN_PIO,PIO_OUTPUT_0, FAN_PIO_PIN_MASK, PIO_DEFAULT);
	
	// Configura o interruptor
	pio_enable_interrupt(TOUCH_PIO, TOUCH_PIO_PIN_MASK);
	pio_handler_set(TOUCH_PIO, ID_PIOC, TOUCH_PIO_PIN_MASK, PIO_IT_FALL_EDGE, &touch_callBack);
	
	// Configura o NVIC
	NVIC_EnableIRQ(ID_PIOC);
	NVIC_SetPriority(ID_PIOC, 0);
	
	
	while (1) {
		
		// LED
		if(pio_get(PRESENCE_PIO, PIO_TYPE_PIO_INPUT, PRESENCE_PIO_PIN_MASK)){
			led_on();	
		}
		else {
			led_off();	
		}
		
		// Fan
		if (fan_flag) {
			fan_on();
		} 
		
		else {
			fan_off();
		}
	}
	return 0;
}
