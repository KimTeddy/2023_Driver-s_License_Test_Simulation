#include "btn.h"

char buttonPath[200] = {0, };
int fd, msgID;
pthread_t buttonTh_id;

int probeButtonPath(char *newPath)
{
    int returnValue = 0; //button의 event# 찾았는지? 
    int number = 0;     //찾았다면 여기에 입력
    FILE *fp = fopen(PROBE_FILE, "rt"); //파일 오픈
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"
    while(!feof(fp))    //파일 끝까지 읽어들이고
    {
        char tmpStr[200];   //최대 200자 읽을 수 있게 버퍼 설정
        fgets(tmpStr, 200, fp); //200자 읽기
        if(strcmp(tmpStr, HAVE_TO_FIND_1) == 0)
        {
            printf("Found It! : %s\r\n", tmpStr);
            returnValue = 1;    //찾았을시 1
        }
        if( (returnValue == 1) && (strncasecmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0))
        {   //찾은 상태에서 Event 찾았으면
            printf("-->%s", tmpStr);
            printf("\t%c\r\n", tmpStr[strlen(tmpStr)-3]);
            number = tmpStr[strlen(tmpStr)-3] - '0';
            //ASCII -> int형으로 변환
            break;
        }
    }    
    fclose(fp); //파일 닫기
        if(returnValue == 1) //찾았으면
        {    
           sprintf(newPath, "%s%d", INPUT_DEVICE_LIST, number);
          //newpath에 저장.
         }
        return returnValue;
}


int buttonInit(void)
{
    printf("HI\n");
    if(probeButtonPath(buttonPath) == 0)
    {
        printf("Error\n");
        printf("Do insmod \n");
        return 0;
    }
        
    fd = open(buttonPath, O_RDONLY);    
    //buttonPath -> 200바이트의 버퍼
    msgID = msgget(MESSAGE_ID, IPC_CREAT|0666);
    if(msgID == -1)
    {
        printf("Can't Find\n");
        return 1;
    }
    pthread_create(&buttonTh_id, NULL, &buttonThFunc, NULL);
    return 1;
}

int buttonExit(void)
{
    pthread_join(buttonTh_id, NULL);
    return 0;
}

void *buttonThFunc(void *arg)
{
    int readSize;
    B.messageNum = 1;
    printf("thread success\n");
    while(1)
    {
        readSize = read(fd, &C, sizeof(C));
        // printf("thread success2\n");
        printf("read size : %d\n", readSize);
        printf("C size : %d\n", sizeof(C));
        
    /*
    struct input_event C;
    struct input_event
    {
        struct timeval time;
        _u16 type;
        _u16 code;
        _s32 value;
    };
    */
    //if문 조건을 sizeof(struct input_event)
    //readSize != sizeof(C)
        if(readSize != sizeof(struct input_event))   //오류 발생 부분
        {
            printf("ERR\n");
            sleep(5);

            continue;
        }
        //printf("thread success3\n");
        
        B.keyInput = C.code;
        B.pressed = C.value;
        B.type = C.type;
        msgsnd(msgID, &B, sizeof(B) - sizeof(long int), 0);
    }
    close(fd);
}



   
