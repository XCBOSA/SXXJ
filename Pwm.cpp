#include "Pwm.h"
#include <wiringPi.h>
#include <iostream>

using namespace std;

void* __loop__(void* data)
{
	Pwm* pwm = (Pwm*)data;
	unsigned long nextTime = micros() + pwm->highTime; //����һ��ʱ��ڵ�
	bool mode_high = true;
	digitalWrite(pwm->pin, HIGH);
	while (1)
	{
		unsigned long current = micros();
		if (current >= nextTime) //�����ǰʱ���Ѿ����ڽڵ�ʱ�䣬��ת��ƽͬʱ�����µ�ʱ��ڵ�
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
	//Ϊ�β������еķ����������Ϊʵ�ⷢ��digitalWrite��ʱ���ɺ��ԣ�ͬ������100%��CPU����ռ�ã�������Ч������һ��...
	return nullptr;
}

void Pwm::start()
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_RR);
	sched_param p;
	p.sched_priority = 10; //�߳����ȼ�10
	pthread_attr_setschedparam(&attr, &p);
	pthread_create(&thread, &attr, __loop__, this);
	pthread_attr_destroy(&attr);
	running = true;
}

void Pwm::wpiinit()
{
	pinMode(pin, OUTPUT);
}
