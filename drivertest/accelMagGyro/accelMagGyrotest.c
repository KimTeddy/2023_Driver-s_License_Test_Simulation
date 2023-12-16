#include <stdio.h>
#include "accelMagGyro.h"
int main(void)
{
    int accel[3];
    int magnet[3];
    int gyro[3];

    getAccel(accel);
    getMagnet(magnet);
    getGyro(gyro);
    while(1)
    {
        printf("I read Accel %d, %d, %d\r\n", accel[0], accel[1], accel[2]);
        printf("I read Magneto %d, %d, %d\r\n", magnet[0], magnet[1], magnet[2]);
        printf("I read Gyroscope %d, %d, %d\r\n", gyro[0], gyro[1], gyro[2]);
        sleep(4);
    }
    return 0;
}