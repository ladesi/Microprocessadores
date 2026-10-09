#ifndef LCD_H
#define	LCD_H

/*
 * Sempre definir os pinos:
 *      LCD_EN
 *      LCD_RS
 * Para o modo de 4 bits:
 *      LCD_nbits = 4
 *      default: LCD_nbits = 8
 * Para 4 bits, definir:
 *      LCD_D4
 *      LCD_D5
 *      LCD_D6
 *      LCD_D7
 * Para 8 bits, definir:
 *      LCD_dat 
 * Funções
 * void lcd_cmd(unsigned char data);   // 
 * void lcd_char(unsigned char data);  // 
 * void lcd_init(void);                // 
 * void lcd_clear(void);               // 
 * void lcd_shutdown(void);            // 
 * void lcd_puts(unsigned char *vector, unsigned char LENGHT); // 
 * void lcd_goto(unsigned char lin, unsigned char col);         // 
 */

/* LCD: Definições: */
#define LCD_nbits 4
#define LCD_RS	PORTEbits.RE1
#define LCD_EN	PORTEbits.RE2 
#define LCD4	PORTDbits.RD4   // bit 4 do lcd
#define LCD5	PORTDbits.RD5   // bit 5 do lcd
#define LCD6	PORTDbits.RD6   // bit 6 do lcd
#define LCD7	PORTDbits.RD7   // bit 7 do lcd

// Condições de utilização
#define M4BITS_1        0x28 // 0b00101000 - 4b, 2 lin, 5x7      - 40 us
#define M4BITS_2        0x2C // 0b00101100 - 4b, 2 lin, 5x10     - 40 us
#define M8BITS_1        0x30 // 0b00110000 - 8b, 1 lin, 5x7      - 40 us
#define M8BITS_2        0x38 // 0b00111000 - 8b, 2 lin, 5x7      - 40 us

// Controle
#define SEM_CURSOR      0x0C // 0b00001100 - liga LCD sem cursor - 40 us
#define COM_CURSOR      0x0E // 0b00001110 - liga LCD com cursor - 40 us

// Mode de operação
#define CURSOR_DIR      0x06 // 0b00000110 - cursor indo p dir   - 40 us

// Comandos auxiliares
#define AVANCA_CURSOR   0x14 // 0b00010100 - cursor p direita    - 40 us
#define RECUA_CURSOR    0x10 // 0b00010000 - cursor p esquerda   - 40 us

// LCD 16x2 or 16x4
#define LCD16_LIN1      0x80 // Endereço da primeira linha na RAM do LCD
#define LCD16_LIN2      0xC0 // Endereço da segunda linha na RAM do LCD
#define LCD16_LIN3      0x90 // Endereço da terceira linha na RAM do LCD
#define LCD16_LIN4      0xD0 // Endereço da quarta linha na RAM do LCD

// LCD 20x2
#define LCD20_LIN1      0x80 // Endereço da primeira linha na RAM do LCD
#define LCD20_LIN2      0xC0 // Endereço da segunda linha na RAM do LCD
#define LCD20_LIN3      0x94 // Endereço da terceira linha na RAM do LCD
#define LCD20_LIN4      0xD4 // Endereço da quarta linha na RAM do LCD

// Protótipos
void lcd_cmd(unsigned char data);
void lcd_char(unsigned char data);
void lcd_init(void);
void lcd_clear(void);
void lcd_shutdown(void);
void lcd_puts(unsigned char *vector, unsigned char LENGHT);
void lcd_goto(unsigned char lin, unsigned char col);
void lcd_txt(unsigned char * s);

#endif
