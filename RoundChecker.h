#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <raspicam/raspicam_cv.h>
#include <iostream>
#include <wiringPi.h>

#define MINSTRP 40
#define MAXBLACKPTCOLOR 30
#define MINTHES 0.5

void tMatMain(cv::Mat* img);
