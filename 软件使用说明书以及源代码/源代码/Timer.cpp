//Timer.cpp
//log:2022/6/3
//Timer类的成员函数的定义

#include "Timer.h"

Timer::Timer(DWORD interval)
{
	//设置计时器间隔
	timeInterval = interval;
	currentRecord = 0;
	timeStart = 0;
}

DWORD Timer::record()const
{
	//返回时间间隔
	return (DWORD)(GetTickCount64()-timeStart) / timeInterval;
}

bool Timer::update()
{
	//判断是否有更新
	int newRecord = record();
	if (currentRecord != newRecord)
	{
		currentRecord = newRecord;
		return true;
	}
	return false;
}

void Timer::start()
{
	//记录开始时间
	timeStart = (DWORD)GetTickCount64();
	//初始化现在时间
	currentRecord = 0;
}
