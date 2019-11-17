#include <wiringPi.h>
#include "XPWM.h"
#include "FishMach.h"
#include <pthread.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <raspicam/raspicam_cv.h>
#include "RoundChecker.h"
#include "Direction.h"

#define	LED	17
#define MR 6
#define ML 13
#define MINSTRP 40
#define MAXBLACKPTCOLOR 40
#define MINTHES 0.5

using namespace std;
using namespace cv;
using namespace raspicam;

FishMach machine;

struct ptrMat
{
	Mat* ptr;
};

void* tVisionDMain(void* args)
{
	ptrMat* matptr = (ptrMat*)args;
	while (matptr->ptr == nullptr)
		delay(10);
	while (1)
	{
		tMatMain(matptr->ptr);
	}
}

void* tVisionMain(void* args)
{
	Mat mat;
	RaspiCam_Cv cam;
	cam.set(CAP_PROP_FRAME_WIDTH, 600);
	cam.set(CAP_PROP_FRAME_HEIGHT, 600);
	if (!cam.open())
	{
		cout << "Error opening camera" << endl;
		//摄像头炸了，没救了，直接关机放弃
		exit(0);
	}
	ptrMat* pmat = new ptrMat();  //其实这应该是一个Mat**，为了便于理解...
	pthread_t thrid;
	pthread_create(&thrid, nullptr, tVisionDMain, pmat);
	Mat image;
	while (1)
	{
		cam.grab();
		cam.retrieve(image);
		pmat->ptr = &image;
		//Direction方向差速微调: 理论上没有问题，静止测试也没有问题，水池测试问题很严重
		//原因可能是当机器运行起来以后拍摄的画面拖影很严重
		//取消注释下面代码开启方向差速微调

		/*tDirectionMain(&image);
		machine.LSPD = MACHSPD_QUICK + bleft;
		machine.RSPD = MACHSPD_QUICK + bright;
		machine.apply();*/
	}
	return nullptr;
}

int main(void)
{
	wiringPiSetupGpio();
	pinMode(LED, OUTPUT);
	digitalWrite(LED, HIGH);      //反向连接二极管
	xpwminit(ML, MR);             //初始化Pwm: lpwm和rpwm
	machine.LPIN = lpwm;
	machine.RPIN = rpwm;
	machine.LSPD = MACHSPD_NONE;
	machine.RSPD = MACHSPD_NONE;
	pthread_t thread_id;
	pthread_create(&thread_id, nullptr, tVisionMain, &machine);
	machine.initMach();           //字面意思
	machine.LSPD = MACHSPD_QUICK;
	machine.RSPD = MACHSPD_QUICK;
	machine.apply();
	while (1)
	{
		char* m = (char*)malloc(1024);
		cin >> m;
		//防止主线程退出...(好像Linux不用这样)
	}
	return 0;
}
