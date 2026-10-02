/*
* ATIVIDADE PRÁTICA 06
* DISCIPLINA: MICROPROCESSADORES (SBL0082)
* TURMA: 01B
* DESCRIÇÃO: Módulo PWM
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
 *     RE0/AN5 --| 8   33 |<< RB0/INT(BUTTON0)
 *     RE1/AN6 --| 9   32 |-- VDD
 *     RE2/AN7 --| 10  31 |-- VSS
 *         VDD --| 11  30 |-- RD7
 *         VSS --| 12  29 |-- RD6
 *    OSC1/RA7 --| 13  28 |-- RD5
 *    OSC2/RA6 --| 14  27 |-- RD4
 *         RC0 --| 15  26 |-- RC7/RX
 *    CCP2/RC1 --| 16  25 |-- RC6/TX
 *    CCP1/RC2 <<| 17  24 |-- RC5
 *         RC3 --| 18  23 |-- RC4
 *   (LED0)RD0 <<| 19  22 |-- RD3
 *   (LED1)RD1 <<| 20  21 |-- RD2
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

// Frequência do cristal: 20MHz.
#define _XTAL_FREQ 20000000UL

#define REC_TMR0 96

#define LED0 LATDbits.LATD0
#define LED1 LATDbits.LATD1
#define BUTTON0 PORTBbits.RB0
#define TMR0_FLAG INTCONbits.TMR0IF
#define MAX_DUTY 475
#define MIN_DUTY 25

// Variáveis globais.
unsigned int count0 = 0;
unsigned int DUTY_VALUE = 250;

volatile bool buttom_flag = false;
volatile bool pwm_control = false;
volatile bool pwm_lock = false;

// Protótipos.
void config();
void pwm_config(void);
void set_duty(unsigned int d_value);
void timer0_init(void);
void read_buttom();

// Função de configuração.
void config(){
    // Configuração I/O.
    // TODO:
    TRISB = 0x??;
    PORTB = 0x00;
    LATB = 0x00;

    TRISC = 0x??;
    LATC = 0x00;
    LATC = 0x00;

    TRISD = 0x??;
    PORTD = 0x00;
    LATD = 0x00;

    // Desabilita os comparadores.
    CMCON = 0x07;

    // Habilita os resistores de pull-up do PORTB.
    INTCON2bits.RBPU = 0;
}

// Configuração do TIMER0.
void timer0_init(){
    // Recarga do TIMER0.
    TMR0 = 256 - REC_TMR0;

    // Configuração do TIMER0
    T0CONbits.T08BIT = 1;    // bit<6> - Modo de 8 bits
    T0CONbits.T0CS = 0;      // bit<5> - Seleciona o Clock interno
    T0CONbits.T0SE = 0;      // bit<4> - Incremento em borda de subida
    T0CONbits.PSA = 0;       // bit<3> - Habilita o prescaler
    T0CONbits.T0PS = 0b110;  // bit<2:0> - Valor do prescaler: 000 1:2

    // Habilita a interrupção do TIMER0.
    INTCONbits.TMR0IE = 1;

    T0CONbits.TMR0ON = 1;  // bit<7> - Habilita o TIMER0
}

void pwm_config(void){
    // Desabilita o pino CCP1.
    TRISCbits.TRISC2 = 1;

    // Configuração do CCP.
    // TODO: Configure o módulo CCP para PWM através de CCP1CON.
    CCP1CON = 0x??;

    // Defina o Prescaler para 1:4.
    T2CONbits.T2CKPS = 0b??;

    // Carrega PR2 com o valor do período do PWM.
    PR2 = 124;

    // (PR2 + 1) x Tm(200ns) x PRESCALER(1:4) = 100us(10KHz).

    // Definição da razão cíclica para início em 50%.
    // 10 bits: 00 11 11 10 | 10 = 250.
    CCPR1L = 0b????????;
    CCP1CONbits.DC1B = 0b??;

    // CCPR1L|CCP1CON<5:4>(???) x Tosc(200ns) x PRESCALER(1:1) = 50us (50%).

    // Limpeza da flag de interrupção do TIMER2.
    PIR1bits.TMR2IF = 0;

    // Habilita o TIMER2.
    T2CONbits.TMR2ON = 1;

    // Habilita o pino CCP1 após o primeiro estouro do TIMER2.
    while(!PIR1bits.TMR2IF);
    TRISCbits.TRISC2 = 0;
}

void set_duty(unsigned int d_value){
    // Define o duty máximo para 95% e mínimo para 5%.
    if(d_value >= MAX_DUTY) d_value = MAX_DUTY;
    if(d_value <= MIN_DUTY ) d_value = MIN_DUTY;

    // Ajusta os registradores do duty cycle.
    CCPR1L = (unsigned char)(d_value >> 2);
    CCP1CONbits.DC1B = (unsigned char)(d_value & 0x03);
    DUTY_VALUE = d_value;
}

void read_buttom(){
    if(!BUTTON0 && !buttom_flag) {
        __delay_ms(20);
        if(!BUTTON0) {
            buttom_flag = true;
            __delay_ms(20);
            count0 = 0;
            pwm_lock = false;
        }
    }

    if(BUTTON0 && buttom_flag){
        buttom_flag = false;

        if(!pwm_lock){
            if(!pwm_control) DUTY_VALUE+=MIN_DUTY;
            if(pwm_control) DUTY_VALUE-=MIN_DUTY;
            set_duty(DUTY_VALUE);
        }
    }
}

// Rotina de interrupção.
void __interrupt() myIsr(void){
    if(TMR0_FLAG){
        TMR0_FLAG = 0;
        TMR0 = 256 - REC_TMR0;

        if(buttom_flag) count0++;

        if(count0 == 200){
            count0 = 0;
            LED0 = !LED0;

            // Trava a atualização do PWM.
            pwm_lock = true;

            // Alterna a variável de controle.
            pwm_control = ~pwm_control;
        }
    }
}

// Realize as alterações necessárias na função principal.
void main(void){
    // Desabilita todas as interrupções.
    INTCONbits.GIE = 0;

    // Configuração.
    config();
    timer0_init();
    pwm_config();

    // Habilita todas as interrupções.
    INTCONbits.GIE = 1;

    while(1){
        // Realiza a varredura do botão.
        read_buttom();
    }
}

