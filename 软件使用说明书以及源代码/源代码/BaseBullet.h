//BaseBullet.h
//log:2022/6/3
//BaseBullet类的定义

#pragma once
#include"WindowSetter.h"
#include"Rec.h"
#include"Timer.h"

class EnemyBulletA;
class EnemyBulletB;
class EnemyBulletC;
class EnemyBulletD;
class PlaneBulletA;
//作为基类来构建子弹
class BaseBullet
{
	friend class EnemyBulletA;
	friend class EnemyBulletB;
	friend class EnemyBulletC;
	friend class EnemyBulletD;
	friend class PlaneBulletA;
public:
	//构造函数
	BaseBullet(WindowSetter* window, int x, int y, int speed);

	//移动子弹函数
	virtual void move() = 0;

	//绘制子弹函数
	virtual void draw(int index = 0) = 0;

	//重设置子弹坐标位置
	void reset(int x, int y);

	//判断子弹与物体碰撞
	bool collision(Rec& rhs);

	//射击子弹函数
	void shoot();

	//判断子弹是否在射击状态函数
	bool isShoot()const;

	//子弹销毁函数
	void destroy();

	//返回free状态
	bool isFree()const;

	//设置free状态
	void setFree(bool state);
private:
	//子弹坐标信息
	int x;
	int y;
	//子弹闲置状态
	bool free;
	//子弹移动速度
	int speed;
	//子弹的矩形对象
	Rec rec;
	//存放窗口指针绘制子弹用
	WindowSetter* window;
	//子弹移动计时
	Timer moveRecord;
public:
	//子弹的伤害
	int hurt;
};

