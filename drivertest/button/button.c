
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>    // for open/close
#include <fcntl.h>     // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"

static int fd = 0;
static int msgID = 0;
static pthread_t buttonTh_id;
char buttonPath[256] = {0, };

// first read input device
#define INPUT_DEVICE_LIST "/dev/input/event" //실제 디바이스 드라이버 노드파일: 뒤에 숫자가 붙음., ex)/dev/input/event5
#define PROBE_FILE "/proc/bus/input/devices"  // PPT에 제시된 "이 파일을 까보면 event? 의 숫자를 알수 있다"는 바로 그 파일
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

int buttonInit(void)
{
    //printf("HI3\n");
    if (probeButtonPath(buttonPath) == 0)
        {
            printf("ERR?\n");
            return 0;
        }
        //return 0;
    //printf("HI4\n");
    fd = open(buttonPath, O_RDONLY);
    msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
    pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
    //printf("HI5\n");
    return 1;
}


int buttonExit(void)
{
    pthread_join(buttonTh_id, (void**)0);
    close(fd);
}


int probeButtonPath(char *newPath)
{
    
    int returnValue = 0;                // button에 해당하는 event#을 찾았나?
    int number = 0;                     //찾았다면 여기에 집어넣자
    FILE *fp = fopen(PROBE_FILE, "rt"); //파일을 열고
    
    while (!feof(fp)) //끝까지 읽어들인다.
    {
        
        char tmpStr[2000];       // 2000자를 읽을 수 있게 버퍼
        fgets(tmpStr, 2000, fp); //최대 2000자를 읽어봄
        // printf ("%s",tmpStr);
        if (strcmp(tmpStr,HAVE_TO_FIND_1) == 0)
        {
            printf("YES! I found!: %s\r\n", tmpStr);
            returnValue = 1; //찾음
        }
        //printf("HI8\n");
        if (
            (returnValue == 1) && //찾은 상태에서
            (strncasecmp(tmpStr, HAVE_TO_FIND_2,
                         strlen(HAVE_TO_FIND_2)) == 0) // Event??을 찾았으면
        )
        {
            printf("-->%s", tmpStr);
            printf("\t%c\r\n", tmpStr[strlen(tmpStr) - 3]);
            number = tmpStr[strlen(tmpStr) - 3] - '0';
            // Ascii character '0'-'9' (0x30-0x39)
            // to interger(0)
            break;
        }
    }
    fclose(fp);
    if (returnValue == 1)
    {
        sprintf(newPath, "%s%d", INPUT_DEVICE_LIST, number);
    }

    return returnValue;
}


static void *buttonThFunc(void)
{
    // while(1){을 돌면서 / read(); / msgsnd(); }
    BUTTON_MSG_T Data;
    Data.messageNum = 1;
    struct input_event stEvent;
    while (1)
    {
        read(fd, &stEvent, sizeof(stEvent));
        if ((stEvent.type == EV_KEY))
        {
            // && (stEvent.value == 0)
            Data.keyInput = stEvent.code;
	        Data.pressed = stEvent.value;
            Data.type = stEvent.type;
            msgsnd(msgID, &Data, sizeof(Data) - 4, 0);
        }
    }
}