#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "accelMagGyro.h"

#define ACCELPATH "/sys/class/misc/FreescaleAccelerometer/"
#define MAGNEPATH "/sys/class/misc/FreescaleMagnetometer/"
#define GYROPATH "/sys/class/misc/FreescaleGyroscope/"

int fd = 0;
FILE *fp = NULL;


void getAccel(int accel[]){
    // Accelerometer
    fd = open(ACCELPATH "enable", O_WRONLY);
    dprintf(fd, "1");
    close(fd);

    fp = fopen(ACCELPATH "data", "rt");
    fscanf(fp, "%d, %d, %d", &accel[0], &accel[1], &accel[2]);
    fclose(fp);
}

void getMagnet(int magnet[]){
    // Magnetometer
    fd = open(MAGNEPATH "enable", O_WRONLY);
    dprintf(fd, "1");
    close(fd);

    fp = fopen(MAGNEPATH "data", "rt");
    fscanf(fp, "%d, %d, %d", &magnet[0], &magnet[1], &magnet[2]);
    fclose(fp);
}

void getGyro(int gyro[]){
    // Gyroscope
    fd = open(GYROPATH "enable", O_WRONLY);
    dprintf(fd, "1");
    close(fd);

    fp = fopen(GYROPATH "data", "rt");
    fscanf(fp, "%d, %d, %d", &gyro[0], &gyro[1], &gyro[2]);
    fclose(fp);
}

