#include "temp.h"

int main(int argc, char **argv)
{
    char *buffer;
    int file;
    buffer = (char *)spi_read_lm74(file);
    close(file);

    int value = 0;
    value = (buffer[1] >> 3);
    value += (buffer[0]) << 5;

    if( buffer[0] & 0x80)
    {
        int i = 0;
        for(i = 31; i > 12; i--)
        value |= (1 << i);
    }

    double temp = (double)value * 0.0625;
    printf("Current Temp : %lf \n", temp);

    return 0;
}