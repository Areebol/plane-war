//Timer.h
//log:2022/6/3
//Timer��Ķ���

#ifndef TIMER_H
#define TIMER_H

#include<Windows.h>
#include<time.h>

//��ʱ����
class Timer
{
public:
	//���캯��
	Timer(DWORD interval);

	//���ؼ�¼��ʱ��
	DWORD record()const;

	//�����Ƿ�����Ӧ��ʱ��仯
	bool update();

	//��ʼ��ʱ
	void start();
private:
	//ʱ����
	DWORD timeInterval;
	//��ǰ��¼ʱ��
	DWORD currentRecord;
	//��ʼ��¼ʱ�� ����
	DWORD timeStart;
};


#endif

