#ifdef __LINUX//������ ���� �ڵ�
void* btncheck(void) { //btn and leds. ��ư�Է� Ȯ�ι� LED���� �Լ�
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

            case KEY_SEARCH: if (leftlight == 0) { // ���� ���� ��� ���� �ʿ� thread? process?
                leftlight = 1; leddata = leddata ^ 00110000;
            }
                           else if (leftlight == 1) {
                leftlight = 1; leddata = leddata ^ 00110000;
            }
                           break;

            case KEY_MENU: if (rightlight == 0) { // ���� ���� ��� ���� �ʿ� thread? process?
                rightlight = 1; leddata = leddata ^ 00001100;
            }
                         else if (rightlight == 1) {
                rightlight = 1; leddata = leddata ^ 00001100;
            }
                         break;

            case KEY_VOLUMEUP: if (emerlight == 0) { // ���� ���� ��� ���� �ʿ� thread? process?
                emerlight = 1; leddata = leddata ^ 00111100;
            }
                             else if (emerlight == 1) {
                emerlight = 1; leddata = leddata ^ 00111100;
            }
                             break;

            case KEY_VOLUMEDOWN:
                // �ʱ�ȭ������ ���� �ڵ�
                break;
            }
        }
    }
}
#endif