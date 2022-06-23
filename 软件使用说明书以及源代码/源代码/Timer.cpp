//Timer.cpp
//log:2022/6/3
//Timer��ĳ�Ա�����Ķ���

#include "Timer.h"

Timer::Timer(DWORD interval)
{
	//���ü�ʱ�����
	timeInterval = interval;
	currentRecord = 0;
	timeStart = 0;
}

DWORD Timer::record()const
{
	//����ʱ����
	return (DWORD)(GetTickCount64()-timeStart) / timeInterval;
}

bool Timer::update()
{
	//�ж��Ƿ��и���
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
	//��¼��ʼʱ��
	timeStart = (DWORD)GetTickCount64();
	//��ʼ������ʱ��
	currentRecord = 0;
}
