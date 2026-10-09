/*
* ATIVIDADE PRÁTICA 07
* DISCIPLINA: MICROPROCESSADORES (SBL0082)
* TURMA: 01B
* DESCRIÇÃO: Conversor AD
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

#include <xc.h>
#include <stdbool.h> 
#include <stdio.h>
#include "lcd.h"

// Frequência do cristal: 20MHz.
#define _XTAL_FREQ 20000000UL

volatile float ad_value;
char ad_char_val[16];

// Função de configuração.
void config(){   
    // TODO: Determine a configuração I/O.
    TRISA = 0x??;
    TRISD = 0x??;
    TRISE = 0x??;
    
    PORTA = 0x00;
    LATA = 0x00;
    
    TRISB = 0x00;
    PORTB = 0x00;
    LATB = 0x00;

    LATC = 0x00;
    TRISC = 0x00;
    LATC = 0x00;     
    
    PORTD = 0x00;
    LATD = 0x00;
    
    PORTE = 0x00;
    LATE = 0x00;
    
    // Desabilita os comparadores.
    CMCON = 0x07;
}

// Configuração do ADC.
void adc_config(void){
    // Habilite a conversão AD.
    ADCON0 = 0x??; // 0000 0001
    
    // Determine somente AN0 como entrada analógica.
    ADCON1 = 0x??; // 0000 1110 - AN0:AN7
    
    // Determine:
    // 1. Saída justificada à direita.
    // 2. F/32 para conversão. 
    ADCON2 = 0x??;
}

// Seleção do canal analógico.
unsigned int adc_read(int port){
    unsigned int value;
    // Desloca o número do canal em 2 bits.
    // Atribui o resultado aos bits <5-2> de ADCON0.
    ADCON0 = ( (port<<2) | (ADCON0 & 0xC3) ); // 0xC3 = 0b11000011
    
    // Delay de conversão.
    __delay_us(20);
    
    // Inicia a conversão.
    ADCON0bits.GO_DONE = 0x01;
    while(ADCON0bits.GO_DONE);
    
    // Retorna o valor completo da conversão.
    value = (unsigned int)( (ADRESH << 8) + (ADRESL) );
    return(value);
}

// Realize as alterações necessárias na função principal.
void main(void){
    // Configuração.
    config();
    adc_config();
    
     // Inicializa o LCD.
    lcd_init();
    
    // Escrita inicial do LCD.
    lcd_goto(1,1);
    lcd_puts("Pratica 07",10);
    __delay_ms(1000);
    lcd_goto(2,1);
    lcd_puts("MICROS 2026.2",13);
    __delay_ms(1000);
    lcd_clear();
    
    lcd_goto(1,1);
    
    // TODO: Escreva um texto de preferência (%s).
    // Especifique a quantidade de caracteres (%d).
    lcd_puts("%s",%d);
  
    while(1){
        // TODO: Realize o cálculo correto da conversão AD.
        ad_value = ???;

        // Conversão da variável para string.
        snprintf(ad_char_val, sizeof(ad_char_val), "%.2fV", ad_value); 
        lcd_goto(2,1);
        lcd_txt(ad_char_val);
        __delay_ms(1000);
    }
}