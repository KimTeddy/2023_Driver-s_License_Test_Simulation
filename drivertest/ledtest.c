#include <stdio.h>
#include <unistd.h>
#include "led.h"


int main(int argc, char** argv)
{
	int ledValue = 0;
	const char ledValuehex[] = "0000";

	printf("LED test");
	for (i = 0; i < 8; i++) {
		ledOnOff(i, 1);
		ledValue = ledStatus();
		printf("LED Status : %d", ledValue);
		usleep(500000);
	}
	usleep(1000000);

	while (1) {
		printf("LED 변화 값을 16진수로 입력하세요: ");
		if (scanf("%s", ledValuehex) != 1) {
			printf("올바른 입력이 아닙니다.\n");
			return 1; // 입력 오류가 발생한 경우 프로그램 종료
		}
		ledChange(ledValuehex);
		printf("led value changed");
	}
}