输油管道水下巡检项目源码
=
开发环境配置：
-
建议使用安装了LinuxC++项目支持的VS2019，它可以直接连接树莓派远程编译运行调试。用到的lib有: Raspicam(控制摄像头) wiringPi("精准"延时和类似Arduino的API) OpenCV4.1.1(摄像头图像解码/简单识别) pthread(Linux多线程)。
#
1.编译安装OpenCV<br/>
编译C++ OpenCV时开启make -j4可以开启4线程编译，同时也可能会遇到更多的报错。大多数的错误都是由于编译时CPU突然抽风导致的，报红重新编译就好，之前的编译进度会保留。如果突然遇到了编译几次都卡在同一个报错，那么删除报错的代码(比如说整个函数都注释掉但是函数本身保留防止链接问题)。会报错的都是奇奇怪怪用不到的地方。
#
3.编译此项目<br/>
建议使用VSLinux远程编译，设置好lib查找路径和h文件查找路径，将体系架构更改为ARM，定义DEBUG常量(如果不定义DEBUG会导致链接OpenCV函数时出现找不到的情况，不清楚原因)，库依赖性填写: pthread;opencv_core;opencv_imgproc;opencv_highgui;opencv_imgcodecs
