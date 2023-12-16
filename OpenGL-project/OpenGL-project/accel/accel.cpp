#include "accel.h"

/*
왼쪽으로 기울이면 ACCEl 값(fisrt_accel[0]) -
오른쪽으로 기울이면 + 정도에 따라 +- 되는 값에 차이는 있음.
뒤로 기울이면 ACCEL z값(first_accel[2])이 수평으로 들었을 경우보다 -값으로 변함.
앞으로 기울이면 ACCEL z값이 +값으로 변함.

*/
void accel_calc()
{
    int first_accel[3]; // 시뮬레이션 시작 시점의 accel값을 저장
    int second_accel[3]; // 게임 도중의 accel값을 해당 변수에 저장
// -> second랑 first를 비교해서 기울기를 계산하여 차의 이동속도를 설정하도록
    
    //if() {}   //게임이 시작되는 트리거를 받아서 if문 활성화되면
    getAccel(first_accel); // 초기 값을 저장.
    //first_accel을 받고 sleep한 다음부터 계속 second_accel로 accel값 받기
    while(!game_stop)//game이 끝날 때 까지 second_accel값 받아서 기울기 계산
    {
        sleep(1);
        getAccel(second_accel);
        
        if( first_accel[0] - second_accel[0] > 5000 ) 
        { //왼쪽으로 기운 경우 차이가 5000이상 나면 
            
            // ~ 차 방향을 왼쪽으로 바꾸는 코드 ~
        }
        else if(second_accel[0] - first_accel[0] > 5000)
        { //오른쪽으로 기운 경우 [차이가 5000이상 나면]

            // ~ 차 방향을 오른쪽으로 바꾸는 코드 ~
        }
        else if( second_accel[1] - first_accel[1] > 5000 )
        { // 뒤로 기울인 경우

            // ~ 차 속도를 감소하는 코드?
            if( second_accel[1] - first_accel[1] > 8000 )
            { // 뒤로 기울인 각도가 큰 경우 (돌발에서 급 브레이크 밟은 경우)
                // ~ 차 멈추는 코드 ~
            }
        }
        else if( first_accel[1] - second_accel[1] > 5000 )
        { // 앞으로 기울인 경우

            // ~차가 앞으로 진행하는 코드 ~
            if( first_accel[1] - second_accel[1] > 8000 )
            { // 앞으로 많이 기울인 경우 (가속 구간에서 가속)
                // ~ 차 속도를 빠르게 ~
            }
        }
    

    }




}