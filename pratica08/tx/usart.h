#ifndef USART_H
#define	USART_H

// Frequência do cristal: 20MHz.
#define _XTAL_FREQ 20000000UL

// Protótipos.
void put_char(unsigned char byte);
void send_str( const char * str);
unsigned char get_char(void);
void rec_str(char *str, unsigned char size);
#endif	/* USART_H */