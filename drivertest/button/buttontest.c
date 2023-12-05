#include "button.h"

int main(int argc, char *argv[])
{

BUTTON_MSG_T Data;
buttonInit();
int msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);

while(1)
{
//struct input_event stEvent;	
    int returnValue = 0;
    returnValue = msgrcv(msgID, &Data, sizeof(Data) - sizeof(long int), 0, 0);
		
if(Data.type== EV_KEY){
    printf("EV_KEY(");
    switch(Data.keyInput)
    {
        case KEY_VOLUMEUP: printf("Volume up key):"); break;
        case KEY_HOME: printf("Home key):"); break;
        case KEY_SEARCH: printf("Search key):"); break;
        case KEY_BACK: printf("Back key):"); break;
        case KEY_MENU: printf("Menu key):"); break;
        case KEY_VOLUMEDOWN: printf("Volume down key):"); break;
    }
if ( Data.pressed ) printf("pressed\n");
else printf("released\n");
} 
else 
; 
} 

    buttonExit();
}
