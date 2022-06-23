//BuffAward.h
//log:2022/6/3
//BuffAward类的定义

#pragma once
#include "BaseBuff.h"

//增加游戏得分
class BuffAward :
    public BaseBuff//继承BaseBuff基类
{
public:
	//构造函数
	BuffAward(WindowSetter* window = 0, Plane* plane = 0, int* score = 0,
	 int x = 0, int y = 0);
	
	//重写绘制buff函数
	virtual void draw()override;

	//重写显示buff功能函数
	virtual void showInformation()override;

	//重写使用buff功能函数
	virtual void use()override;
};

