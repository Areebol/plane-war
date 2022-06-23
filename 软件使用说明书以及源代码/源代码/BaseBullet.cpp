//BaseBullet.cpp
//log:2022/6/3
//BaseBullet类的成员函数的定义

#include "BaseBullet.h"

BaseBullet::BaseBullet(WindowSetter* window, int x, int y, int speed)
	:window(window),x(x),y(y),speed(speed),
	moveRecord(speed),free(true),hurt(1)
{
	//参数的初始化
}


void BaseBullet::reset(int x, int y)
{
	//重新设置坐标信息
	this->x = x;
	this->y = y;
}

bool BaseBullet::collision(Rec& rhs)
{
	//调用Rec的碰撞函数 
	
	//子弹发生碰撞
	if (rhs.collision(this->rec))
	{
		//子弹进行销毁
		this->destroy();
		return true;
	}
	//子弹没有发生碰撞
	else
		return false;
}

void BaseBullet::shoot()
{
	//子弹移动计时器开始计时
	moveRecord.start();
	//子弹进入射击状态
	free = false;
}

bool BaseBullet::isShoot()const
{
	//判断子弹是否进入射击状态
	return !free;
}

void BaseBullet::destroy()
{
	//重置子弹的信息
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
