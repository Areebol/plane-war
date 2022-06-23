//Timer.h
//log:2022/6/3
//Timer类的定义

#ifndef TIMER_H
#define TIMER_H

#include<Windows.h>
#include<time.h>

//计时器类
class Timer
{
public:
	//构造函数
	Timer(DWORD interval);

	//返回记录的时间
	DWORD record()const;

	//返回是否发生对应的时间变化
	bool update();

	//开始计时
	void start();
private:
	//时间间隔
	DWORD timeInterval;
	//当前记录时间
	DWORD currentRecord;
	//开始记录时间 毫秒
	DWORD timeStart;
};


#endif

