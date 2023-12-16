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

void temp_read()
{
    char *buffer;
    int file;
    file = spi_init("/dev/spidev1.0");
    buffer = (char *)spi_read_lm74(file);
    close(file);

    int value = 0; 
    //13bit 빅 엔디안 signed int를 16비트 리틀 엔디안 signed int로
    value = (buffer[1] >> 3); //마지막 3비트의 쓰레긱값을 제거 5비트만 value에 더해짐
    value += (buffer[0]) << 5; //위 5비트 더한 것에 상위 8비트(13bit)를 원하는 값으로 채움

    if( buffer[0] & 0x80) //if buffer[0]의 최상위 8번째 빝이 1이면 signed이므로 음수 -> 영하의 기온
    {
        //그러면 value의 32번 비트에서 부터 14번 비트까지 1로 채워주기 (sign extension??)
        int i = 0;
        for(i = 31; i > 12; i--)
        value |= (1 << i); //1로 채우기
    }

    double temp = (double)value * 0.0625;
    //1비트가 0.0625도 
    printf("Current Temp : %lf \n", temp);
    if(temp > 30)
    {
        printf("It's SUMMER!!\n");
    }
    else if(temp < 5)
    {
        printf("It's WINTER!!\n");
    }
    else 
        printf("It's AUTUMN or SPRING?\n");

}
