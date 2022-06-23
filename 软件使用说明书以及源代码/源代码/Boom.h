//Boom.h
//log:2022/6/3
//Boom的定义

#ifndef BOOM_H
#define BOOM_H

#include"Timer.h"
#include"config.h"
#include"Rec.h"
#include"WindowSetter.h"

//爆炸效果类
class Boom
{
public:
	//构造函数
	Boom(WindowSetter* window, int x = 0, int y = 0);

	//绘制爆炸效果函数
	void paint();
	
	//重新设置爆炸效果
	void reset();
	
	//重新设置坐标位置函数
	void resetPosition(int newX, int newY);

	//返回是否空闲
	bool isFree()const;

	//设置是否空闲
	void setFree(bool state);
private:
	//闲置状态函数
	bool free;
	//坐标位置
	int x;
	int y;
	//窗口类指针
	WindowSetter* window;
	//记录时间
	int record;
};
#endif

