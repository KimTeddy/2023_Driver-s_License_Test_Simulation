#include "btn.h"

int main()
{
    buttonInit();
    int fp;
    int readSize, inputIndex;
    struct input_event1 stEvent;
    char inputDevPath[200] = {0, };

    buttonInit();

    while(1)
    {
        readSize = read(fp, &stEvent, sizeof(stEvent));
        if(readSize != sizeof(stEvent))
        {
            continue;
        }

        //int retmsg = 0;
        //retmsg = msgrcv(msgID, &B, sizeof(B) - sizeof(long int), 0, 0);

        if(stEvent.type == EV_KEY)
        {
            printf("EV_KEY(");
            switch(stEvent.code)
            {
                case KEY_VOLUMEUP : printf("Volume up key):"); break;
                case KEY_HOME : printf("Home key):"); break;
                case KEY_SEARCH : printf("Search key):"); break;
                case KEY_BACK: printf("Back key):"); break;
                case KEY_MENU : printf("Menu key):"); break;
                case KEY_VOLUMEDOWN : printf("Volume down key):"); break;
            }
            if(stEvent.value) printf("Pressed!\n");
            else printf("released\n");
        }
        else 
        ;  //doNothing
    }   //While End
    close(fp);
    buttonExit();

}