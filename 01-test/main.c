#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "lcd_i2c.h"
// option flags
int8_t opt_cursor=0; // 0 off, 1 on , 2 blink
int8_t opt_address = LCD_I2C_PCF8574_ADDRESS_DEFAULT;
int8_t opt_backlight=1; // -1 do nothing, 0 turn off, 1 turn on
int8_t opt_clear = 1;
int8_t opt_cols = 16;
int8_t opt_help;
int8_t opt_init;
int8_t opt_rows = 2;
int8_t opt_x=-1;
int8_t opt_y=-1;

// forward declarations
static void usage(char *argv0);
//! process command line options, set the opt_xxx variables
//! returns 0 on success, on failure it displays an error message and returns non-zero
static int process_options(int argc, char **argv);
//! display values of the options variables
static void print_options();

int main(int argc, char **argv) {
    const char hallo[] = { 'H', 'a', 'l', 'l', 'o', ' ',
                           'W', 'e', 'l', 't', '!', '\0'};

    // init i2c
    lcd_i2c_t lcd={0};
    if( lcd_i2c_setup(&lcd,opt_address)==-1  ){
        printf(stderr,"Error intialising PCF8574 at address i2c 0x%02x: %s\n",opt_address);
    }

    // init lcd
    if(opt_init)
        lcd_i2c_init(&lcd);

    // backlight
    if(opt_backlight==0){
        LCD_I2C_BACKLIGHT_OFF(&lcd);
    }else if(opt_backlight==1){
        LCD_I2C_BACKLIGHT_ON(&lcd);
    }

    if(opt_clear)
        lcd_i2c_clear(&lcd);

    printf("%i",strlen(hallo));

    lcd_i2c_puts(&lcd, &hallo);
}
