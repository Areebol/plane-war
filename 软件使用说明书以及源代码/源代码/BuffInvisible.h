//BuffInvisble.h
//log:2022/6/3
//BuffInvisible��Ķ���
#pragma once
#include "BaseBuff.h"

#define USE_TIME 10000

//ʹ��ս�������ӵ��˺�
class BuffInvisible :
	public BaseBuff
{
public:
	//���캯��
	BuffInvisible(WindowSetter* window = 0, Plane* plane = 0, int* score = 0,
	 int x = 0, int y = 0);
	
	//��д����buff����
	virtual void draw()override;

	//��д��ʾbuff���ܺ���
	virtual void showInformation()override;

	//��дʹ��buff���ܺ���
	virtual void use()override;
private:
	//���ƹ�����Чʱ��
	Timer useRecord;
};

