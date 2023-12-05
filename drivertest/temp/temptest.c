#include "temp.h"

int main(int argc, char **argv)
{
    while(1)
    {
        printf("Getting Temp!\n");
        temp_read();
        
        sleep(10);
    }

    return 0;
}