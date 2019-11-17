#pragma once
#define MACHSPD_NONE 0
#define MACHSPD_QUICK 100
#define MACHSPD_STD 1500
#define MACH_INIT_WAITTIME 10000
#include "Pwm.h"

typedef int MACHSPD;

/*
��ʾһ�������˿�����
*/
class FishMach
{
public:
	/*
	�����Ҳ�ĵ��Pwm���
	*/
	Pwm* LPIN, * RPIN;
	bool inited;
	/*
	��ʾ�����Ҳ������ٶ�
	*/
	MACHSPD LSPD, RSPD;
	/*
	��ʼ�������˵��
	*/
	void initMach();
	/*
	Ӧ�ø���
	*/
	void apply();
};
