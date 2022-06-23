//GameConfig.cpp
//log:2022/6/3
//GameConfig类的成员函数的定义

#include "GameConfig.h"

GameConfig::GameConfig()
{
	//初始游戏难度为简单
	mLevel = LOW;
	//设置游戏难度
	setLevel(mLevel);
	bulletIndex = 0;
	scoreFileRecord = new ScoreFileRecord();
}

void GameConfig::setLevel(level newLevel)
{
	//根据游戏难度 进行游戏设置
	mLevel = newLevel;
	//根据选择 设置游戏参数
	switch (mLevel)
	{
	case LOW:
		enemyMoveInterval = 3*ENEMY_MOVE_INTERVAL;
		enemyReleaseInterval = 3*ENEMY_RELEASE_INTERVAL;
		break;
	case MIDDLE:
		enemyMoveInterval = 2*ENEMY_MOVE_INTERVAL;
		enemyReleaseInterval = 2*ENEMY_RELEASE_INTERVAL;
		break;
	case HIGH:
		enemyMoveInterval = ENEMY_MOVE_INTERVAL;
		enemyReleaseInterval = ENEMY_RELEASE_INTERVAL;
		break;
	}
}

ScoreFileRecord* GameConfig::getScoreFileRecord()const
{
	return scoreFileRecord;
}

void GameConfig::setBulletIndex(int newBulletIndex)
{
	this->bulletIndex = newBulletIndex;
}

int GameConfig::getBulletIndex() const
{
	return bulletIndex;
}


level GameConfig::getLevel() const
{
	return mLevel;
}

int GameConfig::getEnemyMoveInterval() const
{
	return enemyMoveInterval;
}

int GameConfig::getEnemyReleaseInterval() const
{
	return enemyReleaseInterval;
}
