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
		printf("LED ��ȭ ���� 16������ �Է��ϼ���: ");
		if (scanf("%s", ledValuehex) != 1) {
			printf("�ùٸ� �Է��� �ƴմϴ�.\n");
			return 1; // �Է� ������ �߻��� ��� ���α׷� ����
		}
		ledChange(ledValuehex);
		printf("led value changed");
	}
}