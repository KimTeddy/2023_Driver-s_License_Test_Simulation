#include "textlcd.h"


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