#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define CRS_MAIN 0  //���� �޴� �ܰ�
#define CRS_START 1 // �ڽ� ���� �� ��� (���� ���� �� -> ~���� �ܰ�~)
#define CRS_BASIC 2 //�⺻ ���� �ܰ�
#define CRS_UP 3    //����
#define CRS_JUNCTION 4  //������
#define CRS_PARKING 5   //����
#define CRS_EMERGENCY 6 //����
#define CRS_ACCEL 7     //���� ����
#define CRS_END 8	//����
