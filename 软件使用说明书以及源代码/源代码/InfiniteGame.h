//InfiniteGame.h
//log:2022/6/4
//InfiniteGame类定义

#ifndef INFINITEGAME_H
#define INFINITEGAME_H

#include"config.h"
#include"WindowSetter.h"
#include"GameConfig.h"
#include"Plane.h"
#include"Boom.h"
#include"MiniEnemy.h"
#include"MaxEnemy.h"
#include"PlaneBulletA.h"
#include"EnemyBulletA.h"
#include"BossEnemy.h"
#include"BaseBuff.h"
#include"BuffAntidote.h"
#include"BuffAward.h"
#include"BuffBoming.h"
#include"BuffInvisible.h"
#include"BuffShield.h"
#include<ctime>
#include<conio.h>
#include<string>
#include<vector>
#include<algorithm>

//敌机mini最大数量
#define MINI_MAX ENEMY_MINI_MAX
//敌机max最大数量
#define MAX_MAX ENEMY_MAX_MAX

using std::to_string;
using std::vector;

//无尽模式类
class InfiniteGame
{
public:
	//构造函数
	InfiniteGame(WindowSetter* window, GameConfig* config, Plane* plane);

	//析构函数
	~InfiniteGame();

	/////////////////////游戏主控函数/////////////////////////////
	//游戏函数
	void game();
	
private:
	//暂停游戏函数
	bool pause();
	
	//游戏数据更新
	void gameUpdate();

	//绘制暂停面板选择函数
	void paintPause(int select);
	
	//绘制其他提示信息函数
	void paintOther();

	//绘制死亡画面
	void paintDead();

	//绘制破纪录画面
	void paintBreaking();
	////////////////////////控制敌机行为函数///////////////////////////////////
	//释放敌机
	void releaseEnemy();
	
	//敌机释放1
	void releaseEnemyI();
	
	//敌机释放2
	void releaseEnemyII();
	
	//敌机释放3
	void releaseEnemyIII();
	
	//移动敌机
	void moveAllEnemy();
	
	//绘制敌机
	void drawAllEnemy();
	
	//清空死亡敌机
	void clearDeadEnemy();
	
	//敌机射击
	void shootEnemy();
	
	//敌机子弹行为
	void controlEnemyBullet();
	
	//控制敌机函数
	void controlEnemy();
	
	//判断敌机过境函数
	void winEnemy();

	//////////////////////////////////buff类控制函数//////////////////////////////////////

	//释放对应的buff类
	void releaseBuffs();
	
	//绘制所有的buff类
	void drawBuffs();
	
	//移动现存的buff类
	void moveBuffs();
	
	//拾取buff类使用
	void pickBuffs();
	
	//对于持续性的buff的使用
	void useBuffs();
	
	//对于buff的销毁
	void deleteBuffs();
	
	//对buff的操作函数
	void controlBuffs();
	
	//////////////////////////我方战机控制函数/////////////////////////////////////////////
	//关于己方战机的操作
	void controlPlane();

	///////////////////////////爆炸效果控制函数//////////////////////////////////////
	//绘制爆炸效果函数
	void paintBoom();
	
	//设置爆炸效果
	void setBoom(int x, int y);

	//////////////////////////检测碰撞函数/////////////////////////////////////
	//碰撞检测操作
	void collisionAll();
	
	//检测敌机与我方战机子弹碰撞函数
	void collisionEnemyWithPlaneBullet();
	
	//检测敌机与我方战机碰撞函数
	void collisionEnemyWithPlane();
	
	//检测敌机子弹与我方战机碰撞函数
	void collisionPlaneWithEnemyBullet();

	//////////////////////////游戏数据销毁函数/////////////////////////////////
	//重新设置游戏数据
	void init();
	//退出游戏清除游戏数据
	void destroy();
private:
	//窗口绘制指针
	WindowSetter* window;
	//游戏数据类指针
	GameConfig* config;
	//战机
	Plane* mPlane;
	//爆炸效果数组
	Boom* booms[BOOM_MAX];
	//道具效果数组
	vector<BaseBuff*>buffs;
	//游戏计时器
	Timer gameRecorder;
	//控制键盘计时器
	Timer keyboardRecorder;
	//控制敌机释放计时器
	Timer enemyReleaseRecorder;
	//控制敌机移动计时器
	Timer enemyMoveRecorder;
	//控制释放道具
	Timer releaseBuffRecorder;
	//记录对局分数
	int score;
	//敌机数组
	MiniEnemy* miniEnemys[MINI_MAX];
	MaxEnemy* maxEnemys[MAX_MAX];
	BossEnemy* bossEnemy;
};


#endif

