#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <sys/shm.h>

pthread_t thread_object_1; //스레드 1 for rgb led
pthread_t thread_object_2; //스레드 2 for btn and led
pthread_t thread_object_3; //스레드 3 for 7segment

int simuwork=0;
int safetybelt=0, sidebrake=0, leftlight=0, rightlight=0, emerlight=0;
int fnddat;

void* trafLight(void) {
        //reset RGB LED state
    while(1) {
        if(simuwork==1) { // repeat if simulation is working
        //LED ON R0 G100 B 0 green
        sleep(12)
        //LED ON R100 G63 B 0 orange
        sleep(3)
        //LED ON R100 G0 B 0 red
        sleep(5)
        }
    }
}


void* btncheck(void) { //btn and leds
    //reset Button flag state
    while(1) {
        if(simuwork==1) { // repeat if simulation is working
         switch(stEvent.code)
         {
            case KEY_HOME: 
            if(safetybelt==0) {
                safetybelt=1; leddata=leddata^10000000; }
            else if(safetybelt==1) {
                safetybelt=1; leddata=leddata^10000000; }
                break;

            case KEY_BACK: if(sidebrake==0) {
                sidebrake=1; leddata=leddata^01000000; }
            else if(sidebrake==1) {
                sidebrake=1; leddata=leddata^01000000; }
                break;

            case KEY_SEARCH: if(leftlight==0) { // 점멸 구현 방법 생각 필요 thread? process?
                leftlight=1; leddata=leddata^00110000; }
            else if(leftlight==1) {
                leftlight=1; leddata=leddata^00110000; }
                break;

            case KEY_MENU: if(rightlight==0) { // 점멸 구현 방법 생각 필요 thread? process?
                rightlight=1; leddata=leddata^00001100; }
            else if(rightlight==1) {
                rightlight=1; leddata=leddata^00001100; }
                break;

            case KEY_VOLUMEUP: if(emerlight==0) { // 점멸 구현 방법 생각 필요 thread? process?
                emerlight=1; leddata=leddata^00111100; }
            else if(emerlight==1) {
                emerlight=1; leddata=leddata^00111100; }
                break;

            case KEY_VOLUMEDOWN: 
            // 초기화면으로 복귀 코드
            break;
         }
        }
    }
}


void* sevenseg(void) {
        //reset 7seg state
    while(1) {
        if(simuwork==1) { // repeat if simulation is working
        //100 표시
        //구간별 조건문 작성해야함
        }
    }
}

/* 7 seg decoder 만들때 참고.
14,11,10,6,8,7 => 선택 자리수만 LOW, 외에는 HIGH => 3자리만 사용할것이기에 14,11,10 HIGH고정, 6,8,7번갈아가며 LOW 입력.
- 표시: 5번핀 high, 1,2,3,4,9,12,13번핀 low
0 표시: 1,2,4,9,12,13번핀 high, 3,5번핀 low
1 표시: 4,9번핀 high 1,2,3,5,12,13번핀 low
2 표시: 1,2,5,9,13번핀 high, 3,4,12번핀 low
3 표시: 2,4,5,9,13번핀 high, 1,3,12번핀 low
4 표시: 4,5,9,12번핀 high, 1,2,3,13번핀 low
5 표시: 2,4,5,12,13번핀 high, 1,3,9번핀 low
6 표시: 1,2,4,5,12,13번핀 high, 3,9번핀 low
7 표시: 4,9,12,13번핀high, 1,2,3,5번핀 low
8 표시: 1,2,4,5,9,12,13번핀 high, 3번핀 low
9 표시: 2,3,4,5,9,12,13번핀 high, 1번핀 low
*/


int main(void) {
pthread_create(&thread_object_1, NULL, trafLight, NULL);
pthread_create(&thread_object_2, NULL, btncheck, NULL);
pthread_create(&thread_object_2, NULL, sevenseg, NULL);

pthread_join(thread_object_1, NULL);
pthread_join(thread_object_2, NULL);
pthread_join(thread_object_3, NULL);

}