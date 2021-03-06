//BuffInvisble.h
//log:2022/6/3
//BuffInvisible类的定义
#pragma once
#include "BaseBuff.h"

#define USE_TIME 10000

//使得战机无视子弹伤害
class BuffInvisible :
	public BaseBuff
{
public:
	//构造函数
	BuffInvisible(WindowSetter* window = 0, Plane* plane = 0, int* score = 0,
	 int x = 0, int y = 0);
	
	//重写绘制buff函数
	virtual void draw()override;

	//重写显示buff功能函数
	virtual void showInformation()override;

	//重写使用buff功能函数
	virtual void use()override;
private:
	//控制功能生效时间
	Timer useRecord;
};

