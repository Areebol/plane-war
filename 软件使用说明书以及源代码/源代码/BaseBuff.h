//BaseBuff.h
//log:2022/6/3
//基类BaseBuff定义

#ifndef BASEBUFF_H
#define BASEBUFF_H

#include"Rec.h"
#include"config.h"
#include"WindowSetter.h"
#include"Plane.h"
#include"Timer.h"
#include"BossEnemy.h"
#include"MaxEnemy.h"
#include"MiniEnemy.h"
#include<time.h>
#include<random>

//敌机的最多数量宏定义
#define ENEMY_MAX_MAX 4
#define ENEMY_MINI_MAX 6

class BuffAntidote;
class BuffAward;
class BuffBoming;
class BuffInvisible;
class BuffShield;
class BaseBuff
{
	friend class BuffAntidote;
	friend class BuffAward;
	friend class BuffBoming;
	friend class BuffInvisible;
	friend class BuffShield;
public:
	//构造函数
	BaseBuff(WindowSetter* window=0,Plane*plane=0,int* score=0,int x=0,int y=0);

	//绘制buff函数
	virtual void draw()=0;

	//显示buff功能函数
	virtual void showInformation()=0;

	//使用buff功能函数
	virtual void use()=0;

	//移动buff函数
	void move();

	//辅助显示buff功能函数
	void showInformation(string& sentence)const;

	//重置buff坐标函数
	void setPosition(int x, int y);

	//返回闲置状态
	bool& Free();
private:
	//窗口指针绘制用
	WindowSetter* window;
	//存放游戏飞机实现功能
	Plane* plane;
	//移动计时器
	Timer record;
	//存放分数实现功能
	int* score;
	//坐标信息
	int x;
	int y;
	//矩形信息
	int width;
	int height;
	//闲置信息
	bool free;
public:
	//矩形用于碰撞
	Rec rec;
	//是否持续作用
	bool beUsing;
};

#endif
