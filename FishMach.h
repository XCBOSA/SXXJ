#pragma once
#define MACHSPD_NONE 0
#define MACHSPD_QUICK 100
#define MACHSPD_STD 1500
#define MACH_INIT_WAITTIME 10000
#include "Pwm.h"

typedef int MACHSPD;

/*
表示一个机器人控制类
*/
class FishMach
{
public:
	/*
	左侧和右侧的电调Pwm输出
	*/
	Pwm* LPIN, * RPIN;
	bool inited;
	/*
	表示左侧和右侧电调的速度
	*/
	MACHSPD LSPD, RSPD;
	/*
	初始化机器人电调
	*/
	void initMach();
	/*
	应用更改
	*/
	void apply();
};
