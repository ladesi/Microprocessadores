/*
* ATIVIDADE PRÁTICA 03
* DISCIPLINA: MICROPROCESSADORES (SBL0082)
* TURMA: 01B
* DESCRIÇÃO: Introdução à Linguagem C
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
 *         RC1 --| 16  25 |-- RC6/TX
 *         RC2 --| 17  24 |-- RC5
 *         RC3 --| 18  23 |-- RC4
 *         RD0 --| 19  22 |-- RD3
 *   (out) RD1 <<| 20  21 |-- RD2
 *                --------
*/

// Bits de Configuração:
#pragma config OSC = HS
#pragma config MCLRE = ON
#pragma config PWRT = ON
#pragma config BOREN = OFF
#pragma config WDT = OFF

#include <xc.h>

// Frequência do cristal: 20MHz (UFC-PicLab-4520).
#define _XTAL_FREQ 20000000

// Protótipos
void config();

// Utilizando Assembly 'inline'.
// Coloque cada instrução Assembly em asm().
void config(){
//  TODO: Defina o PORTD como saída.
    asm("");

//  TODO: Inicialize todo o PORTD em nível baixo.
    asm("");
}

// Realize as alterações necessárias na função principal.
void main(void){
    while(1){
        // Utilizando o operador ~ (bitwise),
        // alterne a saída de todo o PORTD na frequência de 1Hz.
    }
}

