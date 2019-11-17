#include "XPWM.h"
#include <wiringPi.h>

Pwm* rpwm, * lpwm;

Pwm* initPwm(int pin)
{
	Pwm* pwm = new Pwm();
	pwm->pin = pin;
	pwm->totalTime = 20000;
	pwm->highTime = 1500;
	pwm->wpiinit();
	pwm->start();
	return pwm;
}

void xpwminit(int r, int l)
{
	rpwm = initPwm(r);
	lpwm = initPwm(l);
}
