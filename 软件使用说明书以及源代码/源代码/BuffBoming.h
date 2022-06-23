//BuffBoming.h
//log:2022/6/3
//BuffBoming类定义

#pragma once
#include "BaseBuff.h"

#define BOMING_HURT 50

//使用对战场进行轰炸
class BuffBoming :
	public BaseBuff
{
public:
	//构造函数
	BuffBoming(BossEnemy* boss,MiniEnemy** minis,MaxEnemy** maxs,WindowSetter* window = 0,
		Plane* plane = 0, int* score = 0, int x = 0, int y = 0);
	
	//重写绘制buff函数
	virtual void draw()override;

	//重写显示buff功能函数
	virtual void showInformation()override;

	//重写使用buff功能函数
	virtual void use()override;
private:
	//敌机数组用以实现buff功能
	MiniEnemy** miniEnemys;
	MaxEnemy** maxEnemys;
	BossEnemy* bossEnemy;
};

