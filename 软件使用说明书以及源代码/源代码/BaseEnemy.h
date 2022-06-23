//BaseEnemy.h
//log:2022/6/3
//BaseEnemy类定义

#pragma once
#include"WindowSetter.h"
#include"Timer.h"
#include"GameConfig.h"
#include"Rec.h"
#include"EnemyBulletA.h"
#include"EnemyBulletB.h"
#include"EnemyBulletC.h"
#include"EnemyBulletD.h"
#include<vector>
using std::vector;

//射击间隔
#define SHOOT_INTERVAL 200
//移动时间间隔
#define MOVE_INTERVAL 600
//子弹A的最大载弹数
#define BULLETA_MAX 60
//子弹B的最大载弹数
#define BULLETB_MAX 20
//子弹C的最大载弹数
#define BULLETC_MAX 20 
//子弹D的最大载弹数
#define BULLETD_MAX 2
//战机血量的变化比值
#define ENEMY_BLOOD_RATIO 2
//战机基础血量
#define BASE_BLOOD 10
class BossEnemy;
class MiniEnemy;
class MaxEnemy;
//战机基类
class BaseEnemy
{
	friend class BossEnemy;
	friend class MiniEnemy;
	friend class MaxEnemy;
public:
	//构造函数
	BaseEnemy(WindowSetter* window, GameConfig* config, int x = 0, int y = 0);

	//战机移动函数
	virtual void move()=0;

	//战机绘制函数
	virtual void draw()=0;

	//重置战机坐标函数
	void reset(int x, int y);

	//战机掉血函数
	void subBlood(int sub);

	//判断战机是否死亡函数
	bool isDead()const;

	//彻底销毁函数
	void destroy();

	//初始化函数
	void init();

	//射击子弹函数
	virtual void shoot()=0;

	//移动所有子弹函数
	void moveAllBullet();

	//绘制所有子弹函数
	void drawAllBullet();

	//控制所有子弹行为函数
	void controlAllBullet();

	//射击一枚A子弹函数
	void shootBulletA(int x,int y);

	//射击一枚B子弹函数
	void shootBulletB(int x,int y);

	//射击一枚C子弹函数
	void shootBulletC(int x,int y);

	//射击一枚D子弹函数
	void shootBulletD(int x,int y);

	//A类型子弹进行碰撞检测函数
	int hitObjectA(Rec& rhs);

	//B类型子弹进行碰撞检测函数
	int hitObjectB(Rec& rhs);

	//C类型子弹进行碰撞检测函数
	int hitObjectC(Rec& rhs);

	//D类型子弹进行碰撞检测函数
	int hitObjectD(Rec& rhs);

	//返回矩形信息
	Rec& getRec();

	//返回x坐标
	int getX()const;
	
	//返回y坐标
	int getY()const;
	
	//返回血量
	double& getBlood();

	//返回是否闲置
	bool isFree()const;

	//设置free状态
	void setFree(bool state);
private:
	//坐标信息
	int x;
	int y;
	//战机闲置状态
	bool free;
	//战机血量
	double blood;
	//战机矩形信息
	Rec rec;
	//窗口指针用于绘制
	WindowSetter* window;
	//游戏参数用于配置战机
	GameConfig* config;
	//控制移动的计时器
	Timer moveRecord;
	//控制射击的计时器
	Timer shootRecord;
	//存放各种类型的子弹数组
	EnemyBulletA bulletA[BULLETA_MAX];
	EnemyBulletB bulletB[BULLETB_MAX];
	EnemyBulletC bulletC[BULLETC_MAX];
	EnemyBulletD bulletD[BULLETD_MAX];
	vector<EnemyBulletA*> movingBulletsA;
	vector<EnemyBulletB*> movingBulletsB;
	vector<EnemyBulletC*> movingBulletsC;
	vector<EnemyBulletD*> movingBulletsD;
};

