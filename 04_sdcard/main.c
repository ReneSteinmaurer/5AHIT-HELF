#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <bits/types/time_t.h>
#include <time.h>

#define messungen 10

char* getTime() {
    time_t currentTime = time(0);
    return ctime(&currentTime);
}

void writeToFile(double input) {
    FILE *fh;
    double fileOutput[17] = {};
    fh=fopen("/media/SDCard/messwerte-bh1750.txt","a");
    if(fh==NULL){
        puts("Can't open that file!");
    }

    //sprintf(fileOutput, "%s %.2lflx\n", getTime(), input);
    sprintf(fileOutput, "%.2lflx  :  %s", input, getTime());
    fprintf(fh, fileOutput);
    fclose(fh);
}

void readFromFile() {
    FILE *fh;
    char array[100] = {};
    fh=fopen("/media/SDCard/messwerte-bh1750.txt","r");
    for (int i = 0; i < messungen; ++i) {
        fgets(array, 255, fh);
        printf(array);
    }
}

void readBH(double *lux) {
    int handle = wiringPiI2CSetup(0x5C);

    wiringPiI2CWrite(handle, 0x10);
    delay(1000);

    int word = wiringPiI2CReadReg16(handle, 0x00);

    *lux = ((word & 0xff00) >> 8) | ((word & 0x00ff) << 8);
}


int main() {
    double helligkeit = 0.0;
    for (int i = 0; i < messungen; ++i) {
        readBH(&helligkeit);
        writeToFile(helligkeit);
        delay(500);
    }
    readFromFile();

    return 0;
}
