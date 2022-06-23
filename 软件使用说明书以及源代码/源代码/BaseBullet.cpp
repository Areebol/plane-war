//BaseBullet.cpp
//log:2022/6/3
//BaseBullet��ĳ�Ա�����Ķ���

#include "BaseBullet.h"

BaseBullet::BaseBullet(WindowSetter* window, int x, int y, int speed)
	:window(window),x(x),y(y),speed(speed),
	moveRecord(speed),free(true),hurt(1)
{
	//�����ĳ�ʼ��
}


void BaseBullet::reset(int x, int y)
{
	//��������������Ϣ
	this->x = x;
	this->y = y;
}

bool BaseBullet::collision(Rec& rhs)
{
	//����Rec����ײ���� 
	
	//�ӵ�������ײ
	if (rhs.collision(this->rec))
	{
		//�ӵ���������
		this->destroy();
		return true;
	}
	//�ӵ�û�з�����ײ
	else
		return false;
}

void BaseBullet::shoot()
{
	//�ӵ��ƶ���ʱ����ʼ��ʱ
	moveRecord.start();
	//�ӵ��������״̬
	free = false;
}

bool BaseBullet::isShoot()const
{
	//�ж��ӵ��Ƿ�������״̬
	return !free;
}

void BaseBullet::destroy()
{
	//�����ӵ�����Ϣ
	free = true;
	this->x = 0;
	this->y = 0;
	rec.reset(this->x, this->y);
}

bool BaseBullet::isFree() const
{
	return free;
}

void BaseBullet::setFree(bool state)
{
	this->free = state;
}
