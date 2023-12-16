#include <stdio.h>
#include <math.h>
#include "accelMagGyro.h"

const double RADIAN_TO_DEGREE = 180 / 3.14159;

int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
double angle_x, angle_y, angle_z;


void loop() // 각도 계산
{
    getAccel();
    angle_y = atan(-AcX / sqrt( pow( AcY, 2) + pow( AcZ, 2)));
    angle_y *= RADIAN_TO_DEGREE;
    angle_x = atan( AcY/ sqrt( pow(AcX, 2) + pow(AcZ, 2)));
    angle_x *= RADIAN_TO_DEGREE; 
    printf("Angle x : %f , Angle y :%f", angle_x, angle_y);
}


int main(void)
{
    int accel[3];
    int magnet[3];
    int gyro[3];
    double ang;

    while(1)
    {
        getAccel(accel);
        getMagnet(magnet);
        getGyro(gyro);
        printf("I read Accel %d, %d, %d\r\n", accel[0], accel[1], accel[2]);
        printf("I read Magneto %d, %d, %d\r\n", magnet[0], magnet[1], magnet[2]);
        printf("I read Gyroscope %d, %d, %d\r\n", gyro[0], gyro[1], gyro[2]);
        printf("\n\n");
        loop();
        
        sleep(4);
    }
    return 0;
}