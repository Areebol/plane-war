//GameConfig.h
//log:2022/6/3
//GameConfig的定义

#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include"config.h"
#include"WindowSetter.h"
#include"ScoreFileRecord.h"

//敌机移动间隔
#define ENEMY_MOVE_INTERVAL 100
//敌机释放间隔
#define ENEMY_RELEASE_INTERVAL 5000

//游戏难度变量
enum level { LOW, MIDDLE, HIGH };
//游戏配置数据类
class GameConfig
{
public:
	//构造函数
	GameConfig();

	//设置游戏难度
	void setLevel(level newLevel);

	//返回最高分数指针
	ScoreFileRecord* getScoreFileRecord()const;

	//设置子弹下标
	void setBulletIndex(int bulletIndex);

	//返回子弹下标
	int getBulletIndex()const;

	//返回游戏难度
	level getLevel()const;

	//返回敌机移动时间间隔
	int getEnemyMoveInterval()const;

	//返回敌机释放时间间隔
	int getEnemyReleaseInterval()const;
private:
	//子弹资源下标
	int bulletIndex;
	//敌机的配置数据信息
	int enemyMoveInterval;
	int enemyReleaseInterval;
	//游戏难度
	level mLevel;
	ScoreFileRecord* scoreFileRecord;
};

#endif
