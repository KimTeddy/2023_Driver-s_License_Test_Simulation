#ifdef __LINUX//리눅스 전용 코딩
void* trafLight(void) { // 신호등함수
    //reset RGB LED state
    while (1) {
        if (simuwork == 1) { // repeat if simulation is working
            //LED ON R0 G100 B 0 green
            sleep(12)
                //LED ON R100 G63 B 0 orange
                sleep(3)
                //LED ON R100 G0 B 0 red
                sleep(5)
        }
    }
}
#endif