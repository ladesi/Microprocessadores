#include "lcd.h"
#include <xc.h>
#include <stdint.h>

// Frequência do cristal: 20MHz.
#define _XTAL_FREQ 20000000UL

// DEFINES
#ifndef LCD_nbits
#define LCD_nbits 4
#endif

#ifndef LCD_dat
unsigned char data;
#define LCD_dat data
#endif

#ifndef LCD4
uint8_t var4;
#define LCD4 var4
#endif

#ifndef LCD5
uint8_t var5;
#define LCD5 var5
#endif

#ifndef LCD6
uint8_t var6;
#define LCD6 var6
#endif

#ifndef LCD7
uint8_t var7;
#define LCD7 var7
#endif

#ifndef LCD_RS
uint8_t var8;
#define LCD_RS var8
#endif

#ifndef LCD_EN
uint8_t var9;
#define LCD_EN var9
#endif

// Funções

// Rotinas de temporização
void lcd_delay_1us(void)  {__delay_us(1);}
void lcd_delay_40us(void) {__delay_us(40);}
void lcd_delay_2ms(void)  {__delay_ms(2);}
void lcd_delay_40ms(void) {__delay_ms(40);}

void lcd_en_pulse(void){
    LCD_EN = 1;
    lcd_delay_1us();
    LCD_EN = 0;
    lcd_delay_1us();
}

void lcd_send_nibble(unsigned char data){
// nibble menos significativo

    if (data&0x01) LCD4 = 1;
    else LCD4 = 0;
    if (data&0x02) LCD5 = 1;
    else LCD5 = 0;
    if (data&0x04) LCD6 = 1;
    else LCD6 = 0;
    if (data&0x08) LCD7 = 1;
    else LCD7 = 0;

    lcd_en_pulse();
}

void lcd_byte_4bits(unsigned char data){
    unsigned char nibble;

    // nibble mais significativo
    nibble = (data >> 4);
    lcd_send_nibble(nibble);

    // nibble menos significativo
    nibble = (data & 0x0F);
    lcd_send_nibble(nibble);
}

void lcd_byte_8bits(unsigned char data){
    LCD_dat = data;
    lcd_en_pulse();
}

void lcd_cmd(unsigned char data){
    LCD_RS = 0;

    if (LCD_nbits == 8)
        lcd_byte_8bits(data);
    else
        lcd_byte_4bits(data);

    lcd_delay_40us();
}

void lcd_char(unsigned char data){
    LCD_RS = 1;

    if (LCD_nbits == 8)
        lcd_byte_8bits(data);
    else
        lcd_byte_4bits(data);

    lcd_delay_40us();
}

void lcd_puts(unsigned char *vector, unsigned char LENGHT){
    unsigned char cnt;
    unsigned char x;

    LCD_RS = 1; //seleciona o dado

    for (cnt=0; cnt<LENGHT; cnt++){
        x = *(vector+cnt);
        lcd_char(x);
    }
}

void lcd_init_8bits(void){
    // espera 40 ms até estabilização do LCD
    lcd_delay_40ms();
    // força configuração de 8 bits
    lcd_cmd(0x30);
    lcd_delay_2ms();
    lcd_cmd(0x30);
    lcd_delay_2ms();
    lcd_cmd(0x30);
    lcd_delay_2ms();
    // main
    lcd_cmd(M8BITS_2);
    lcd_cmd(CURSOR_DIR);
    lcd_cmd(COM_CURSOR);
    lcd_clear();
}

void lcd_init_4bits(void){
    // espera 40 ms até estabilização do LCD
    lcd_delay_40ms();
    // força configuração de 8 bits
    lcd_send_nibble(0x03);
    lcd_delay_2ms();
    lcd_send_nibble(0x03);
    lcd_delay_2ms();
    lcd_send_nibble(0x03);
    lcd_delay_2ms();
    // força configuração de 4 bits
    lcd_send_nibble(0x02);
    lcd_delay_2ms();
    // main
    lcd_cmd(M4BITS_1);
    lcd_cmd(CURSOR_DIR);
    lcd_cmd(COM_CURSOR);
    lcd_clear();
}

void lcd_init(void){
    if (LCD_nbits == 8)
        lcd_init_8bits();
    else
        lcd_init_4bits();
}

void lcd_clear(void){
    lcd_cmd(0x01);
    lcd_delay_2ms();
}

void lcd_shutdown(){
    lcd_clear();
    lcd_cmd(0x08);
}

void lcd_goto(unsigned char lin, unsigned char col){
    switch(lin){
        case 1:{
            lcd_cmd(0x80+col);
            break;
        }
        case 2:{
            lcd_cmd(0xc0+col);
            break;
        }
        case 3:{
            lcd_cmd(0x90+col);
            break;
        }
        case 4:{
            lcd_cmd(0xd0+col);
            break;
        }
    }
}

void lcd_txt(unsigned char * s){
    while(*s!='\0'){
        lcd_char(*s);
        s++;
    }
}

