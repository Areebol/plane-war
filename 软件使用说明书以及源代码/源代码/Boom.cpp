//Boom.cpp
//log:2022/6/3
//Boom类的成员函数的定义

#include "Boom.h"

Boom::Boom(WindowSetter* window, int x, int y)
	:window(window), x(x), y(y),free(true),
	record(0)
{
	//参数初始化
}

void Boom::paint()
{
	//如果爆炸效果闲置 返回
	if (free)
		return;

	//绘制爆炸效果
	WORD color = 0x02;
	string sentence;
	sentence = "★";
	window->paintSentence(x+2, y, color, sentence);
	sentence = "★★★";
	window->paintSentence(x, y+1, color, sentence);
	sentence = "★";
	window->paintSentence(x+2, y+2, color, sentence);
	//记录更新
	record++;
}

void Boom::reset()
{
	//持续时间记录
	if (free||record<7)
		return;
	//持续时间结束
	free = true;
	record = 0;
}

void Boom::resetPosition(int newX, int newY)
{
	//根据参数重新设置坐标
	this->x = newX;
	this->y = newY;
}

bool Boom::isFree() const
{
	return free;
}

void Boom::setFree(bool state)
{
	free = state;
}
