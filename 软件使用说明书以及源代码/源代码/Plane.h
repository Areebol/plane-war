//Plane.h
//log:2022/6/3
//Plane类的定义

#ifndef PLANE_H
#define PLANE_H

//飞机初始坐标位置
#define PLANE_BEGIN_X 26
#define PLANE_BEGIN_Y 30
//飞机矩形几何数据
#define PLANE_REC_WIDTH 10
#define PLANE_REC_HEIGHT 3
//飞机血量
#define PLANE_BLOOD 50
//飞机弹夹大小
#define PLANE_BULLETSA_MAX 40
//飞机子弹速度
#define BULLET_SPEED 100
//飞机子弹移动间隔
#define BULLET_INTERVAL 300
//飞机造成的伤害
#define PLANE_HURT 20

#include"PlaneBulletA.h"
#include"Timer.h"
#include"config.h"
#include"GameConfig.h"
#include"Rec.h"
#include"WindowSetter.h"

//战机类
class Plane
{
public:
	//方向变量
	enum direction { UP, DOWN, LEFT, RIGHT };
	
	//构造函数
	Plane(WindowSetter* window,GameConfig* config,int x=0,int y=0);
	
	//移动战机函数
	void move(direction d);
	
	//重新设置战机位置函数
	void moveTo(int x, int y);
	
	//绘制战机函数
	void paint();
	
	//判断战机摧毁函数
	bool isDead();
	
	//A型子弹射击
	void shootBulletA();
	
	//移动已经射出的子弹A
	void moveBulletA();
	
	//绘制已经射击的子弹A
	void drawBulletA();
	
	//飞机子弹碰撞矩形
	bool hitObject(Rec& rhs);

	//摧毁子弹
	void destroyBullet(int index);

	//返回x坐标
	int getX()const;

	//返回y坐标
	int getY()const;

	//返回矩形信息
	Rec& getRec();

	//扣除战机血量
	void subBlood(int sub);

	//增加战机血量
	void addBlood(int add);

	//设置战机血量
	void setBlood(int blood);

	//返回战机血量
	int getBlood()const;
private:
	//弹夹
	PlaneBulletA bulletsA[PLANE_BULLETSA_MAX];
	//战机移动速度
	int planeSpeed;
	//窗口绘制指针
	WindowSetter* window;
	//坐标信息
	int x;
	int y;
	//战机子弹发射间隔计时器
	Timer bulletTimer;
	//战机子弹移动速度计时器
	Timer bulletSpeedTimer;
	//游戏数据配置指针
	GameConfig* config;
	//战机矩形信息
	Rec rec;
	//战机血量
	int blood;
public:	
	//飞机碰撞造成的伤害
	const int hurt = PLANE_HURT;
	//子弹伤害
	const int bulletHurt;
};

#endif

