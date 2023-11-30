#include "temp.h"

char gbuf[10];

int spi_init(char filename[40])
{
    int file;
    __u8 mode, lsb, bits;
    __u32 speed = 20000;

    if((file = open(filename, O_RDWR)) < 0)
    {
        printf("Failed to open the bus.");
        printf("ErrType : %d\r\n", errno);
        exit(1);
    }
    //세팅된 SPI 전송 모드 확인 (mode에 저장).
    if( ioctl(file, SPI_IOC_RD_MODE, &mode) < 0)
    {   perror("SPI rd_mode");      return 0;}
    
    //세팅된 SPI 전송 LSB 순서를 확인 (lsb에 저장)
    if( ioctl(file, SPI_IOC_RD_LSB_FIRST, &lsb) < 0 )
    { perror("SPI rd_lsb_fist");    return 0;}

    //세팅된 SPI 전송 1Word bit 갯수를 확인 (bits에 저장)
    if( ioctl(file, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0)
    { perror("SPI bits_per_word");  return 0;}

    printf("%s: spi mode %d, %d bits %sper word, %d Hz max\n",filename, mode, bits, lsb ? "(lsb first) " : "", speed); 
    
    return file;
}

char * spi_read_lm74(int file)
{
    int len;

    memset(gbuf, 0, sizeof(gbuf));
    len = read(file, gbuf, 2);
    //Read two byte

    if(len != 2)
    {
        perror("read error");
        return NULL;
    }
    return gbuf;
}

