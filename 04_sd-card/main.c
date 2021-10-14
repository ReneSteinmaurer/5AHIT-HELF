#include <stdint-gcc.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include "lcd_i2c.h"

#define DHTMAXTIMINGS 85
#define DHTPIN 11

int8_t opt_cursor = 0; // 0 off, 1 on , 2 blink
int8_t opt_address = LCD_I2C_PCF8574_ADDRESS_DEFAULT;
int8_t opt_backlight = 1; // -1 do nothing, 0 turn off, 1 turn on
int8_t opt_clear = 1; // 0 clear not, 1 clear
int8_t opt_cols = 16; // 16 Zeichen pro Zeile
int8_t opt_init; // Initialisierung
int8_t opt_rows = 2; // 2 Zeilen
int8_t opt_x = 0; // Positierung x-Achse
int8_t opt_y = 0; // Positierung y-Achse

void printLCD(char *array) {
    // i2c Initialisierung
    lcd_i2c_t lcd = {0};
    if (lcd_i2c_setup(&lcd, opt_address) == -1) {
        printf(stderr, "Error intialising PCF8574 at address i2c 0x%02x: %s\n", opt_address);
    }

    // LCD Initialisierung
    if (opt_init)
        lcd_i2c_init(&lcd);

    // Backlight des LCD ein-/ausschalten
    if (opt_backlight == 0)
        LCD_I2C_BACKLIGHT_OFF(&lcd);
    else if (opt_backlight == 1)
        LCD_I2C_BACKLIGHT_ON(&lcd);

    // vorherigen Text am LCD löschen
    if (opt_clear)
        lcd_i2c_clear(&lcd);

    // Positionierung des Textes am LCD
    lcd_i2c_gotoxy(&lcd, opt_x, opt_y);

    // Ausgabe des Textes am LCD
    lcd_i2c_puts(&lcd, array);
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
