#include "btn.h"

int main()
{
    //buttonInit();
   // int fp;
    //int readSize, inputIndex;
   // struct input_event stEvent;
    //char inputDevPath[200] = {0, };

    buttonInit();
    struct input_event stEvent;
    int msgID = msgget(MESSAGE_ID, IPC_CREAT|0666);
    if(msgID == -1)
    {
        printf("Can't find\n");
        return 1;
    }

    while(1)
    {

        int retmsg = 0;
        retmsg = msgrcv(msgID, &stEvent, sizeof(stEvent)-sizeof(long int), 0, 0);

        if(stEvent.type == EV_KEY)
        {
            printf("EV_KEY(");
            switch(stEvent.keyInput)
            {
                case KEY_VOLUMEUP : printf("Volume up key):"); break;
                case KEY_HOME : printf("Home key):"); break;
                case KEY_SEARCH : printf("Search key):"); break;
                case KEY_BACK: printf("Back key):"); break;
                case KEY_MENU : printf("Menu key):"); break;
                case KEY_VOLUMEDOWN : printf("Volume down key):"); break;
            }
            if(stEvent.pressed) printf("Pressed!\n");
            else printf("released\n");
        }
        else 
        ;  //doNothing
    }   //While End
    //close(fp);
    buttonExit();

}