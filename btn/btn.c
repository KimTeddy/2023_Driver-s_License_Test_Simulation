#include "btn.h"

char buttonPath[200] = {0, };
int fd, msgID;
pthread_t buttonTh_id;

int probeButtonPath(char *newPath)
{
    int returnValue = 0; //button의 event# 찾았는지? 
    int number = 0;     //찾았다면 여기에 입력
    FILE *fp = fopen(PROBE_FILE, "rt"); //파일 오픈

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
        //event를 못 찾았다면 에러 문구 출력.
        printf("Error\n");
        printf("Do insmod \n");
        return 0;
    }
        
    fd = open(buttonPath, O_RDONLY);    
    //찾았으면 오픈
    //buttonPath -> 200바이트의 버퍼
    msgID = msgget(MESSAGE_ID, IPC_CREAT|0666);
    if(msgID == -1)
    {
        printf("Can't Find\n");
        return 1;
    }
    pthread_create(&buttonTh_id, NULL, &buttonThFunc, NULL);
    return msgID;
}

int buttonExit(void)
{
    pthread_join(buttonTh_id, NULL);
    close(fd);
    //return 0;
}

void *buttonThFunc(void *arg)
{
    
    B.messageNum = 1;
    struct input_event C;
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

    printf("thread success\n");
    while(1)
    {
        read(fd, &C, sizeof(C));

    //if문 조건을 sizeof(struct input_event) ? -> 똑같음
    //readSize != sizeof(C)

            /*
            printf("ERR\n");
            printf("C Size = %zu\n", sizeof(C)); //sizeof
            printf("readSize = %d\n", readSize);
            sleep(5);

            continue;
            */
        
        if((C.type == EV_KEY) && (C.value == 0))   
        {
            
           B.keyInput = C.code;
           msgsnd(msgID, &B, sizeof(B) - sizeof(long int), 0);
           printf("msg snd success\n");
           sleep(5);
        }
        printf("if doesn't work\n");
       // if()

        //printf("thread success3\n");
 
    }
}



   
