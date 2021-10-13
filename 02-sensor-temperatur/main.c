#include <stdint-gcc.h>
#include <stdio.h>
#include <wiringPi.h>
#include <string.h>
#include "lcd_i2c.h"

#define DHTMAXTIMINGS 85
#define DHTPIN 11

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

void readDHT(double *temperature, double *humidity, int *worked) {
    int dht11_dat[5] = {0, 0, 0, 0, 0};
    int dhtCounter = 0;

    while (*humidity == 0 && *temperature == 0 && dhtCounter < 5) {
        // predefine values
        uint8_t laststate = HIGH, counter, j = 0, i;
        dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

        // set pin mode
        pinMode(DHTPIN, OUTPUT);
        digitalWrite(DHTPIN, LOW);
        delay(18);
        digitalWrite(DHTPIN, HIGH);
        delayMicroseconds(40);
        pinMode(DHTPIN, INPUT);

        // digital read
        for (i = 0; i < DHTMAXTIMINGS; i++) {
            counter = 0;
            while (digitalRead(DHTPIN) == laststate) {
                counter++;
                delayMicroseconds(1);
                if (counter == 255) { break; }
            }
            laststate = digitalRead(DHTPIN);

            if (counter == 255) break;

            if ((i >= 4) && (i % 2 == 0)) {
                dht11_dat[j / 8] <<= 1;
                if (counter > 50)
                    dht11_dat[j / 8] |= 1;
                j++;
            }
        }

        // calculate values
        if ((j >= 40) && (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF))) {
            *temperature = dht11_dat[0] + (dht11_dat[1] / 10);
            *humidity = dht11_dat[2] + (dht11_dat[3] / 10);
            *worked = HIGH;
        } else
            *worked = LOW;

        dhtCounter++;
    }
}

void printLCD(char array[]) {
    //const char hallo[] = { 'H', 'a', 'l', 'l', 'o', ' ',
    //                       'W', 'e', 'l', 't', '!', '\0'};

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

    printf("%i",strlen(array));

    lcd_i2c_puts(&lcd, &array);
}

int main() {
    double humidity = 0.0, temperature = 0.0;
    int worked = 0;

    wiringPiSetupPhys();

    printf("DHT:\n");
    readDHT(&temperature, &humidity, &worked);

    if (worked)
        printf("Humidity = %.2f%% Temperature = %.2f°C\n", humidity, temperature);
}