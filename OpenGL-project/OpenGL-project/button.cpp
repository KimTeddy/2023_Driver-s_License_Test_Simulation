#ifdef __LINUX//리눅스 전용 코딩
void* btncheck(void) { //btn and leds. 버튼입력 확인및 LED동작 함수
    //reset Button flag state
    while (1) {
        if (simuwork != CRS_MAIN) { // repeat if simulation is working
            switch (stEvent.code)
            {
            case KEY_HOME:
                if (safetybelt == 0) {
                    safetybelt = 1; leddata = leddata ^ 10000000;
                }
                else if (safetybelt == 1) {
                    safetybelt = 1; leddata = leddata ^ 10000000;
                }
                break;

            case KEY_BACK: if (sidebrake == 0) {
                sidebrake = 1; leddata = leddata ^ 01000000;
            }
                         else if (sidebrake == 1) {
                sidebrake = 1; leddata = leddata ^ 01000000;
            }
                         break;

            case KEY_SEARCH: if (leftlight == 0) { // 점멸 구현 방법 생각 필요 thread? process?
                leftlight = 1; leddata = leddata ^ 00110000;
            }
                           else if (leftlight == 1) {
                leftlight = 1; leddata = leddata ^ 00110000;
            }
                           break;

            case KEY_MENU: if (rightlight == 0) { // 점멸 구현 방법 생각 필요 thread? process?
                rightlight = 1; leddata = leddata ^ 00001100;
            }
                         else if (rightlight == 1) {
                rightlight = 1; leddata = leddata ^ 00001100;
            }
                         break;

            case KEY_VOLUMEUP: if (emerlight == 0) { // 점멸 구현 방법 생각 필요 thread? process?
                emerlight = 1; leddata = leddata ^ 00111100;
            }
                             else if (emerlight == 1) {
                emerlight = 1; leddata = leddata ^ 00111100;
            }
                             break;

            case KEY_VOLUMEDOWN:
                // 초기화면으로 복귀 코드
                break;
            }
        }
    }
}
#endif