#pragma once
#include <pthread.h>

void* __loop__(void* data);

/*
手动实现的软件方波输出
*/
class Pwm
{
private:
	pthread_t thread;
public:
	/*
	开启
	*/
	void start();
	/*
	初始化管脚(需要先设置pin)
	*/
	void wpiinit();
	bool running;
	/*
	@totalTime: 单周期总时间
	@highTime:  单周期高电平时间
	*/
	unsigned int totalTime, highTime;
	unsigned int pin;
};

