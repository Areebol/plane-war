//Rec.cpp
//log:2022/6/3
//Rec��ĳ�Ա�����Ķ���

#include "Rec.h"

Rec::Rec(int x,int y,int width,int height)
	:x(x),y(y),width(width),height(height)
{
	//�Բ������г�ʼ��
}

bool Rec::collision(Rec& rhs)
{
	//�ж����������Ƿ���ײ
	return (x<rhs.x + rhs.width) && (y<rhs.y + rhs.height)
		&& (x + width>rhs.x) && (y + height>rhs.y);
}

void Rec::reset(int newX, int newY)
{
	//�������þ�������λ��
	this->x = newX;
	this->y = newY;
}
