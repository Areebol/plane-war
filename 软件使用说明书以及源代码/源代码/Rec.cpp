//Rec.cpp
//log:2022/6/3
//Rec类的成员函数的定义

#include "Rec.h"

Rec::Rec(int x,int y,int width,int height)
	:x(x),y(y),width(width),height(height)
{
	//对参数进行初始化
}

bool Rec::collision(Rec& rhs)
{
	//判断两个矩形是否碰撞
	return (x<rhs.x + rhs.width) && (y<rhs.y + rhs.height)
		&& (x + width>rhs.x) && (y + height>rhs.y);
}

void Rec::reset(int newX, int newY)
{
	//重新设置矩形坐标位置
	this->x = newX;
	this->y = newY;
}
