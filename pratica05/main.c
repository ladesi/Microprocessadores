/*
* ATIVIDADE PRÁTICA 05
* DISCIPLINA: MICROPROCESSADORES (SBL0082)
* TURMA: 01B
* DESCRIÇÃO: Temporizadores (TIMER0 e Botão Multi Função)
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
 *     RE0/AN5 --| 8   33 |<< RB0/INT (BUTTOM)
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
 *  (LED0) RD0 <<| 19  22 |-- RD3
 *  (LED1) RD1 <<| 20  21 |-- RD2
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
#define _XTAL_FREQ 20000000UL

// TODO:
// Defina aqui o valor da recarga do temporizador.
#define REC_TMR0 0

// Variáveis.
#define LED0 LATDbits.LATD0
#define LED1 LATDbits.LATD1
#define BUTTOM PORTBbits.RB0

// Variáveis globais.
unsigned int count0 = 0;
unsigned char buttom_on = 0x00;
unsigned char buttom_flag = 0x00;
unsigned char led_control = 0x00;

// Protótipos.
void config();
void init_tmr0();
void read_buttom();

// Função de configuração.
void config(){
    // TODO: Defina TRISD e TRISB.
    // Configuração I/O.
    // TRISD = ;
    PORTD = 0x00;
    LATD = 0x00;
    // TRISB = ;

    // Desabilita os comparadores.
    CMCON = 0x07;

    // Desabilita os resistores de pull-up do PORTB.
    INTCON2bits.RBPU = 1;
}

// Configuração do TIMER0.
void init_tmr0(){
    // Recarga do TIMER0.
    TMR0 = 256 - REC_TMR0;

    // TODO: Verifique o resistrador T0CON no datasheet.
    // O TIMER0 deve ter a seguinte configuração:
    // Modo de 8 bits.
    // Seleção de clock interno.
    // Estouro a cada 1ms.

    // TODO: Apresente o cálculo realizado para o tempo de aproximadamente 5ms.

    // TODO:
    // Habilite a interrupção do TIMER0.

    // TODO:
    // Habilite a contagem do TIMER0.
}

// Varredura do botão.
void read_buttom(){
    // Se botão está em nivel alto, a flag é ativada.
    if(BUTTOM) buttom_flag = 0x01;

    // Ao soltar o botão, a flag será desativada.
    if(!BUTTOM && buttom_flag){
        buttom_flag = 0x00;
        count0 = 0;

        // O LED alterna o estado de acordo com a variável led_control.
        if(!led_control) LED0 = ~LED0;
        if(led_control) LED1 = ~LED1;
    }
}

// Rotina de interrupção.
void __interrupt() myIsr(void){
    if(INTCONbits.TMR0IF){
        // Limpeza da FLAG.
        INTCONbits.TMR0IF = 0;

        // Recarga do temporizador.
        TMR0 = 256 - REC_TMR0;

        // Incremento do contador.
        // Ao pressionar o botão, a buttom_flag permanece em nível alto.
        if(buttom_flag) count0++;

        // Se o contador chega a 1000, aproximadamente em 1s,
        // o led controlado é alternado.
        if(count0 == 1000){
            count0 = 0;
            led_control = ~led_control;
            // Como sinalização, o LED ativo oscila por 500ms.
            if(!led_control){
                for(int i=0; i<11; i++){
                  LED0 = ~LED0;
                  __delay_ms(50);
                }
            } else{
                for(int i=0; i<11; i++){
                  LED1 = ~LED1;
                  __delay_ms(50);
                }
            }
        }
    }
}

// Realize as alterações necessárias na função principal.
void main(void){
    // TODO:
    // Boas práticas:
    // Desabilite as interrupções globalmente,
    // carregue as configurações e habilite as interrupções novamente.

    while(1){
        // Realiza a varredura do botão.
        read_buttom();
    }
}

