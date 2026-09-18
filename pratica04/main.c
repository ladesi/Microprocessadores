/*
* ATIVIDADE PRÁTICA 04
* DISCIPLINA: MICROPROCESSADORES (SBL0082)
* TURMA: 01B
* DESCRIÇÃO: Eventos de Interrupção
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
 *     RE0/AN5 --| 8   33 |<< RB0/INT
 *     RE1/AN6 --| 9   32 |-- VDD
 *     RE2/AN7 --| 10  31 |-- VSS
 *         VDD --| 11  30 |-- RD7
 *         VSS --| 12  29 |-- RD6
 *    OSC1/RA7 --| 13  28 |-- RD5
 *    OSC2/RA6 --| 14  27 |-- RD4
 *         RC0 --| 15  26 |-- RC7/RX
 *         RC1 --| 16  25 |-- RC6/TX
 *         RC2 --| 17  24 |-- RC5
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

// Frequência do cristal: 20MHz (UFC-PicLab-4520).
#define _XTAL_FREQ 20000000

// Protótipos.
void config();

// Função de configuração.
void config(){
    // TODO
    // Configuração I/O.

    // Desabilita os comparadores.
    CMCON = 0x07;

    // Desabilita os resistores de pull-up do PORTB.
    INTCON2bits.RBPU = 1;

    // Desabilita a prioridade de interrução.
    RCONbits.IPEN = 0;

    // TODO: Verifique o bit relacionado no datasheet.
    // Interrupção externa por borda de subida.

    // TODO: Verifique o bit relacionado no datasheet.
    // Habilita a interrupção externa.
}

// Realize as alterações necessárias na função principal.
void main(void){
    // Desabilita todas as interrupções.
    INTCONbits.GIE = 0;

    // Configuração.
    config();

    // Habilita todas as interrupções.
//    INTCONbits.GIE = 1;

    while(1){
        if(PORTBbits.RB0){
            LATDbits.LD1 = ~LATDbits.LD1;
        }
        LATDbits.LD0 = ~LATDbits.LD0;
        __delay_ms(1000);
    }
}

// Rotina de interrupção.
// Realizar o teste de flag e alternar o estado de RD1.
void __interrupt() myIsr(void){
    // Teste da interrução externa.
}

