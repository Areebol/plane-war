//BuffAntidote.h
//log:2022/6/3
//BuffAntidote��Ķ���

#pragma once
#include "BaseBuff.h"

//�ָ�ս��Ѫ��
class BuffAntidote :
    public BaseBuff//�̳л���BaseBuff
{
public:
	//���캯��
	BuffAntidote(WindowSetter* window = 0, Plane* plane = 0, int* score = 0,
		 int x = 0, int y = 0);
	
	//��д����buff����
	virtual void draw()override;

	//��д��ʾbuff���ܺ���
	virtual void showInformation()override;

	//��дʹ��buff���ܺ���
	virtual void use()override;
};

