#pragma once
#include <pthread.h>

void* __loop__(void* data);

/*
�ֶ�ʵ�ֵ�����������
*/
class Pwm
{
private:
	pthread_t thread;
public:
	/*
	����
	*/
	void start();
	/*
	��ʼ���ܽ�(��Ҫ������pin)
	*/
	void wpiinit();
	bool running;
	/*
	@totalTime: ��������ʱ��
	@highTime:  �����ڸߵ�ƽʱ��
	*/
	unsigned int totalTime, highTime;
	unsigned int pin;
};

