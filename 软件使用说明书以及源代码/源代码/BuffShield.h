//BuffShiled.h
//log:2022/6/3
//BuffShield类的定义

#pragma once
#include "BaseBuff.h"

//为战机增加护盾效果
class BuffShield :
	public BaseBuff
{
public:
	//构造函数
	BuffShield(BossEnemy* boss, MiniEnemy** minis, MaxEnemy** maxs, WindowSetter* window = 0,
		Plane* plane = 0, int* score = 0, int x = 0, int y = 0);

	//重写绘制buff函数
	virtual void draw()override;

	//重写显示buff功能函数
	virtual void showInformation()override;

	//重写使用buff功能函数
	virtual void use()override;
	
	//检测护盾的碰撞
	void collision();

	//检测护盾与子弹碰撞
	void collisionShieldWithEnemyBullet();


public:
	//护盾的位置信息
	Rec shieldRec;
	int shieldBlood;
private:
	//敌机数组
	MiniEnemy** miniEnemys;
	MaxEnemy** maxEnemys;
	BossEnemy* bossEnemy;
};

