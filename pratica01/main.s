/*
* ATIVIDADE PRÁTICA 01
* DISCIPLINA: MICROPROCESSADORES (SBL0082)
* TURMA: 01B
* DESCRIÇÃO: Introdução à Linguagem Assembly
* IDE: MPLABX v5.40
* COMPILADOR: pic-as v3.10
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
 * (BUTTON)RD0 >>| 19  22 |-- RD3
 *    (LED)RD1 <<| 20  21 |-- RD2
 *                --------
*/

; Bits de Configuração (Fuse Bits)
CONFIG  OSC = HS              ; Oscillator Selection bits (HS oscillator)
CONFIG  PWRT = ON             ; Power-up Timer Enable bit (PWRT enabled)
CONFIG  MCLRE = ON            ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
CONFIG  BOREN = OFF           ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
CONFIG  LVP = ON              ; Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
CONFIG  FCMEN = OFF           ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
CONFIG  IESO = OFF            ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
CONFIG  BORV = 3              ; Brown Out Reset Voltage bits (Minimum setting)
CONFIG  WDTPS = 32768         ; Watchdog Timer Postscale Select bits (1:32768)
CONFIG  CCP2MX = PORTC        ; CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
CONFIG  PBADEN = ON           ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
CONFIG  LPT1OSC = OFF         ; Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
CONFIG  STVREN = ON           ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
CONFIG  XINST = OFF           ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
CONFIG  CP0 = OFF             ; Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
CONFIG  CP1 = OFF             ; Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
CONFIG  CP2 = OFF             ; Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
CONFIG  CP3 = OFF             ; Code Protection bit (Block 3 (006000-007FFFh) not code-protected)
CONFIG  CPB = OFF             ; Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
CONFIG  CPD = OFF             ; Data EEPROM Code Protection bit (Data EEPROM not code-protected)
CONFIG  WRT0 = OFF            ; Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
CONFIG  WRT1 = OFF            ; Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
CONFIG  WRT2 = OFF            ; Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
CONFIG  WRT3 = OFF            ; Write Protection bit (Block 3 (006000-007FFFh) not write-protected)
CONFIG  WRTC = OFF            ; Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
CONFIG  WRTB = OFF            ; Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
CONFIG  WRTD = OFF            ; Data EEPROM Write Protection bit (Data EEPROM not write-protected)
CONFIG  EBTR0 = OFF           ; Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
CONFIG  EBTR1 = OFF           ; Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
CONFIG  EBTR2 = OFF           ; Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
CONFIG  EBTR3 = OFF           ; Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)
CONFIG  EBTRB = OFF           ; Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// config statements should precede project file includes.
#include <xc.inc>

; cristal externo de 4MHz -> (1 ciclo de instrução ~ 1us).
; cristal externo de 20MHz -> (1 ciclo de instrução ~ 200ns).
#define _XTAL_FREQ 4000000

; variáveis no access RAM.
PSECT udata_acs
VAR_AUX1: DS 1 ; 1 byte.
VAR_AUX2: DS 1 ; 1 byte.

; vetor de reset.
PSECT resetVec,class=CODE,reloc=2

resetVec:
    GOTO start

; LED definido em RD1.
#define LED LATD,1

; BUTTON em RD0
#define BUTTON PORTD,0

; main.
PSECT code

start:
    ; RD1 como saída.
    MOVLW 0b11111101
    MOVWF TRISD, a

    ; inicializa LATD com 0x00.
    CLRF LATD, a

loop:
    ; Se o botão for pressionado, o LED permanece apagado.
    BTFSS BUTTON, a
    ; Acende o LED.
    BSF LED, a
    CALL delay_ms

    ; Apaga o LED.
    BCF LED, a
    CALL delay_ms

    ; Retorna ao loop.
    GOTO loop

dummy_delay:
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    RETURN
    ; 18 NOP + 2 RETURN = 20 x ciclo_de_instrução.

; para 20MHz (UFC PicLab-4520) -> delay_ms ~ 100ms.
delay_ms:
    ; VAR_AUX1 = 100.
    MOVLW 100
    MOVWF VAR_AUX1, a

delay1:
    ; VAR_AUX2 = 200.
    MOVLW 200
    MOVWF VAR_AUX2, a

delay2:
    CALL dummy_delay ; 2 CALL + 20 dummy_delay = 22 ciclos.

    ; decremento com salto se VAR_AUX2 = 0.
    DECFSZ VAR_AUX2,1, 0 ; + 1 ciclo.
    GOTO delay2 ; + 2 ciclos.

    ; decremento com salto se VAR_AUX1 = 0.
    DECFSZ VAR_AUX1,1, 0
    GOTO delay1

    RETURN
    ; número total de ciclos: 22 + 3 = 25.
    ; tempo de delay_ms ~ (200 X 100 X 25) x (200E-9) s.
    ; tempo calculado: 100ms (20MHz).
END resetVec

