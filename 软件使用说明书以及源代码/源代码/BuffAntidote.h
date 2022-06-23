//BuffAntidote.h
//log:2022/6/3
//BuffAntidote类的定义

#pragma once
#include "BaseBuff.h"

//恢复战机血量
class BuffAntidote :
    public BaseBuff//继承基类BaseBuff
{
public:
	//构造函数
	BuffAntidote(WindowSetter* window = 0, Plane* plane = 0, int* score = 0,
		 int x = 0, int y = 0);
	
	//重写绘制buff函数
	virtual void draw()override;

	//重写显示buff功能函数
	virtual void showInformation()override;

	//重写使用buff功能函数
	virtual void use()override;
};

