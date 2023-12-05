#include "btn.h"

int main(int argc, char *argv[])
{
//printf("HI\n");
int msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
//printf("HI\n");
buttonInit();
//printf("Bye\n");
while(1){
struct input_event stEvent;	
int returnValue = 0;
returnValue = msgrcv(msgID, &stEvent, sizeof(unsigned short) * 2 + sizeof(int), 0, 0);
		
if(stEvent.type== EV_KEY){
printf("EV_KEY(");
switch(stEvent.code)
{
case KEY_VOLUMEUP: printf("Volume up key):"); break;
case KEY_HOME: printf("Home key):"); break;
case KEY_SEARCH: printf("Search key):"); break;
case KEY_BACK: printf("Back key):"); break;
case KEY_MENU: printf("Menu key):"); break;
case KEY_VOLUMEDOWN: printf("Volume down key):"); break;
}
if ( stEvent.value ) printf("pressed\n");
else printf("released\n");
} //End of if
else // EV_SYN
; // do notthing
} // End of While

buttonExit();
}
