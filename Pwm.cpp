#include "Pwm.h"
#include <wiringPi.h>
#include <iostream>

using namespace std;

void* __loop__(void* data)
{
	Pwm* pwm = (Pwm*)data;
	unsigned long nextTime = micros() + pwm->highTime; //设置一个时间节点
	bool mode_high = true;
	digitalWrite(pwm->pin, HIGH);
	while (1)
	{
		unsigned long current = micros();
		if (current >= nextTime) //如果当前时间已经大于节点时间，反转电平同时设置新的时间节点
		{
			if (mode_high)
			{
				mode_high = false;
				nextTime = micros() + pwm->totalTime - pwm->highTime;
				digitalWrite(pwm->pin, LOW);
			}
			else
			{
				mode_high = true;
				nextTime = micros() + pwm->highTime;
				digitalWrite(pwm->pin, HIGH);
			}
		}
	}
	//为何不用四行的方波输出？因为实测发现digitalWrite耗时不可忽略！同样都是100%的CPU核心占用，这样的效果更好一点...
	return nullptr;
}

void Pwm::start()
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_RR);
	sched_param p;
	p.sched_priority = 10; //线程优先级10
	pthread_attr_setschedparam(&attr, &p);
	pthread_create(&thread, &attr, __loop__, this);
	pthread_attr_destroy(&attr);
	running = true;
}

void Pwm::wpiinit()
{
	pinMode(pin, OUTPUT);
}
