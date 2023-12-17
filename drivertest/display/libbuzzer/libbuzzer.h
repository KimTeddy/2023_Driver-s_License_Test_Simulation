#ifndef _LIB_BUZZER_H_
#define _LIB_BUZZER_H_
enum
{
	C 	= 0,	//도
	C_S = 1,	//도#
	D_F = 1,	//레 플렛
	D	= 2,	//레
	D_S = 3,	//레#
	E_F	= 3,
	E	= 4,	//미
	F  	= 5,	//파#
	F_S = 6,
	G_F = 6,
	G	= 7,
	G_S	= 8,
	A_F	= 8,
	A	= 9,
	A_S = 10,
	B_F = 10,
	B	= 11,
	HC 	= 12,
	HC_S =	HC+1,	//도#
	HD_F = 	HC+1,	//레 플렛
	HD	= 	HC+2,	//레
	HD_S = 	HC+3,	//레#
	HE_F = 	HC+3,
	HE	= 	HC+4,	//미
	HF  = HC+5,	//파#
	HF_S = HC+6,
	HG_F = HC+6,
	HG	= HC+7,
	HG_S	= HC+8,
	HA_F	= HC+8,
	HA	= HC+9,
	HA_S = HC+10,
	HB_F = HC+10,
	HB	= HC+11,
	HHC 	= HC+12,

	LAST_SCALE,
};
void libBuzzerInit(void);
void buzzerEnable(int bEnable);
void setFrequency(int scale);
#endif