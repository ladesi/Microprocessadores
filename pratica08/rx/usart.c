#include <xc.h>
#include "usart.h"

// VARIABLES
uint8_t flag_rx = 0;   // =1 if received byte in serial

// Enviar caractere.
void put_char(unsigned char byte){
    while(!PIR1bits.TXIF)
        continue;
    TXREG = byte;
}

// Enviar string.
void send_str( const char * str){
	while(*str){
		put_char(*str++);
	}
}

// Receber caractere.
unsigned char get_char(void){
	while(!RCIF)	
		continue;
	return RCREG;
}

// Receber string.
void rec_str(char *str, unsigned char size){
    unsigned char i = 0;
    char c;

    while(i < size - 1){
        c = get_char();

        if(c == '\n' || c == '\r')
            break;

        str[i++] = c;
    }

    str[i] = '\0';
}