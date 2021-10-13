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

void readBH(double *lux) {
    int handle = wiringPiI2CSetup(0x5C);

    wiringPiI2CWrite(handle, 0x10);
    delay(1000);

    int word = wiringPiI2CReadReg16(handle, 0x00);

    *lux = ((word & 0xff00) >> 8) | ((word & 0x00ff) << 8);
}

void readDHT(double *temperature, double *humidity) {

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
                if (counter == 255) break;
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
        }

        dhtCounter++;
    }
}

void setHelligkeit() {
    // Variablen Initialisierung
    double lux = 0;
    char array[16] = {};

    // Helligkeit einlesen
    readBH(&lux);
    printf("Light: %.2flx\n", lux);

    // Double von Helligkeit in char-array umwandeln
    sprintf(array, "Light: %6.2lflx", lux);

    // Helligkeit am LCD ausgeben
    printLCD(array);
}

void setTemp() {
    char array2[16] = {};
    double humidity = 0.0, temperature = 0.0;

    readDHT(&temperature, &humidity);
    printf("Temperature = %.2f°C\n", temperature);

    sprintf(array2, "Temp: %7.2lf°C", temperature);
    printLCD(array2);
}

int main() {
    wiringPiSetupPhys();
    // setHelligkeit();
    setTemp();
}