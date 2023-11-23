#include "btn.h"

int main()
{
    buttonInit();
    int msgID = msgget(MESSAGE_ID, IPC_CREAT|0666);
    if(msgID == -1)
    {
        printf("Can't Fing It\r\n");
        return 1;
    }
    while(1)
    {
        int retmsg = 0;
        retmsg = msgrcv(msgID, &B, sizeof(B) - sizeof(long int), 0, 0);

        if(B.type == EV_KEY)
        {
            printf("EV_KEY(");
            switch(B.keyInput)
            {
                case KEY_VOLUMEUP : printf("Volume up key):"); break;
                case KEY_HOME : printf("Home key):"); break;
                case KEY_SEARCH : printf("Search key):"); break;
                case KEY_BACK: printf("Back key):"); break;
                case KEY_MENU : printf("Menu key):"); break;
                case KEY_VOLUMEDOWN : ("Volume down key):"); break;
            }
            if(B.pressed) printf("Pressed!\n");
            else printf("released\n");
        }
        else ;  //doNothing
    }   //While End

    buttonExit();
}