#include "FishMach.h"
#include "XPWM.h"
#include <wiringPi.h>
#include <iostream>
#include "Pwm.h"

using namespace std;

void applymms(Pwm *pin, unsigned int mms)
{
	pin->highTime = mms;
}

void FishMach::initMach()
{
	inited = false;
	applymms(LPIN, MACHSPD_STD);
	applymms(RPIN, MACHSPD_STD);
	delay(2000);
	LPIN->running = false;
	RPIN->running = false;
	delay(1000);
	LPIN->running = true;
	RPIN->running = true;
	cout << "maybe running" << endl;
	inited = true;
}

void FishMach::apply()
{
	if (inited)
	{
		applymms(LPIN, MACHSPD_STD - LSPD - 20);
		applymms(RPIN, MACHSPD_STD + RSPD);
	}
	else
	{
		while (!inited);
		apply();
	}
}
