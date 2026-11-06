/*
* ATIVIDADE PRÁTICA 08
* DISCIPLINA: MICROPROCESSADORES (SBL0082)
* TURMA: 01B
* DESCRIÇÃO: Comunicação Síncrona (Transmissor)
* IDE: MPLABX v5.40
* COMPILADOR: XC8
* MICROCONTROLADOR: PIC18F4520
*/

/*
 * Hardware Pin Out
 *                --------
 *  MRCLR'/RE3 --| 1   40 |-- RB7/PGD
 *     RA0/AN0 --| 2   39 |-- RB6/PGC
 *     RA1/AN1 --| 3   38 |-- RB5
 *     RA2/AN2 --| 4   37 |-- RB4
 *     RA3/AN3 --| 5   36 |-- RB3/PGM
 *         RA4 --| 6   35 |-- RB2
 *     RA5/AN4 --| 7   34 |-- RB1
 *     RE0/AN5 --| 8   33 |-- RB0/INT
 *     RE1/AN6 --| 9   32 |-- VDD
 *     RE2/AN7 --| 10  31 |-- VSS
 *         VDD --| 11  30 |-- RD7
 *         VSS --| 12  29 |-- RD6
 *    OSC1/RA7 --| 13  28 |-- RD5
 *    OSC2/RA6 --| 14  27 |-- RD4
 *         RC0 --| 15  26 |-- RC7/RX
 *    CCP2/RC1 --| 16  25 |-- RC6/TX
 *    CCP1/RC2 --| 17  24 |-- RC5
 *         RC3 --| 18  23 |-- RC4
 *         RD0 --| 19  22 |-- RD3
 *         RD1 --| 20  21 |-- RD2
 *                --------
*/

#include <xc.h>

// Frequência do cristal: 20MHz.
#define _XTAL_FREQ 20000000UL

// Bits de Configuração:
#pragma config OSC = HS
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config PWRT = OFF
#pragma config BOREN = SBORDIS
#pragma config WDT = OFF
#pragma config MCLRE = ON
#pragma config LPT1OSC = OFF
#pragma config PBADEN = OFF
#pragma config CCP2MX = PORTC
#pragma config STVREN = ON
#pragma config LVP = OFF
#pragma config XINST = OFF

#define rx_pin  PORTCbits.RC7   // RX pin
#define tx_pin  PORTCbits.RC6   // TX pin

#include <stdbool.h>
#include <stdio.h>
#include "usart.h"

volatile float ad_value;
char ad_char_val[16];

// Função de configuração.
void config(){
    // Configuração I/O.
    // TODO: Configurar o TRISA
    TRISA = 0x??;
    PORTA = 0x00;
    LATA = 0x00;

    TRISB = 0x00;
    PORTB = 0x00;
    LATB = 0x00;

    // TODO: Configurar o TRISC
    TRISC = 0x??;
    PORTC = 0x00;
    LATC = 0x00;

    TRISD = 0x00;
    PORTD = 0x00;
    LATD = 0x00;

    TRISE = 0x00;
    PORTE = 0x00;
    LATE = 0x00;

    // Desabilita os comparadores.
    CMCON = 0x07;
}

// Configuração do ADC.
void adc_config(void){
    // Habilite a conversão AD.
    ADCON0 = 0x01; // 0000 0001

    // Determine somente AN0 como entrada analógica.
    ADCON1 = 0x0E; // 0000 1110 - AN0:AN7

    // Determine:
    // 1. Saída justificada à direita.
    // 2. F/32 para conversão.
    ADCON2 = 0x82;
}

// Seleção do canal analógico.
unsigned int adc_read(int port){
    unsigned int value;
    // Desloca o número do canal em 2 bits.
    // Atribui o resultado aos bits <5-2> de ADCON0.
    ADCON0 = ( (port<<2) | (ADCON0 & 0XC3) ); // 11000011

    // Delay de conversão.
    __delay_us(20);

    // Inicia a conversão.
    ADCON0bits.GO_DONE = 0x01;
    while(ADCON0bits.GO_DONE);

    // Retorna o valor dos registradores se justificado à direita.
    value = (unsigned int)( (ADRESH << 8) + (ADRESL) );
    return(value);
}

void usart_config(void){
//Configuração USART
	TXSTA = 0b00100100;		//datasheet pg. 204
/*	   		  ||||||||
	   		  |||||||TX9D	(9o bit - can be parity)
	   		  ||||||TRMT	TSR status (=1 TSR empty)
	   		  |||||BRGH		(baud rate -> =1 high)
	  		  ||||(n)		(not implemented)
	   		  |||SYNC		(=0 Assynchronous)
	   		  ||TXEN		(enable Tx)
	  		  |TX9			(enable 9 bits Tx)
	   		  CSRC			(sinc: master/slave)
*/

	RCSTA = 0b10010000;		//datasheet pg. 205
/*	   		  ||||||||
	   		  |||||||RX9D	(9o bit - can be parity)
	   		  ||||||OERR	(overrun error - |see file of)
	   		  |||||FERR		(framing error - |USART => ERROS)
	  		  ||||ADDEN		(for 9 bits. =0 disable)
	   		  |||CREN		(continous receive, =1 enable)
	   		  ||SREN		(dont care)
	  		  |RX9			(habilita 9 bits Rx)
	   		  SPEN			(serial enable)
*/

    // TODO: Configurar a taxa de bits para 9600.
	SPBRG = ???;	// BR = 9600

    /*
        Baud Rate = FOSC/(16(x+1))
        x = valor de SPBRG (0 to 255)
        Baud Rate = 9.6k, FOSC = 20MHz
    */
}

// Realize as alterações necessárias na função principal.
void main(void){
    // Configuração.
    config();
    adc_config();
    usart_config();


    while(1){
        // Realize o cálculo correto da conversão AD.
        ad_value = 5.0 * (adc_read(0) / 1023.0);
        // Conversão da variável para string.
        snprintf(ad_char_val, sizeof(ad_char_val), "%.2fV", ad_value);
        __delay_ms(1000);
        send_str(ad_char_val);
        put_char('\n');
        put_char('\r');
    }
}
