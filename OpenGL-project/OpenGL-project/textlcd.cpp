#include "textlcd.h"

/*
#define CRS_MAIN 0  //���� �޴� �ܰ�
#define CRS_START 1 // �ڽ� ���� �� ��� (���� ���� �� -> ~���� �ܰ�~)
#define CRS_BASIC 2 //�⺻ ���� �ܰ�
#define CRS_UP 3    //����
#define CRS_JUNCTION 4  //������
#define CRS_PARKING 5   //����
#define CRS_EMERGENCY 6 //����
#define CRS_ACCEL 7     //���� ����
*/

void crs_lcd()	//�Լ� �̸� �����ʿ��ϸ� �ϼ���.
{
	while (1)
	{
		if (CRS_MAIN)
		{
			//MAIN������ LCD ���ܿ��� "PRESS START" ���, 
			//�Ʒ��κ��� �׸� 0��
		}
		else if (CRS_START)	//���� ��ư�� ������ ~���� �κ�~
		{
			//START�κп����� ���ܿ� "" ���,
			//�Ʒ��κ� �׸� 0��
		}
		else if (CRS_BASIC)
		{
			//���ܿ� "CAR COMPONENT"
			// �׸� 2��
		}
		else if (CRS_UP)
		{
			// ���ܿ� "UP HILL" 
			// �׸� 4��
		}
		else if (CRS_JUNCTION)
		{
			// "JUNCTION"
			// �׸� 6��
		}
		else if (CRS_PARKING)
		{
			// "PARKING"
			// �׸� 8��
		}
		else if (CRS_EMERGENCY)
		{
			// "EMERGENCY"
			// �׸� 10��
		}
		else if (CRS_ACCEL)
		{
			// "ACCELERATE"
			// �׸� 12��
		}
		else if (CRS_END)
		{
			// "END"
			// �׸� 16��
		}
	}

}