//GameConfig.cpp
//log:2022/6/3
//GameConfig��ĳ�Ա�����Ķ���

#include "GameConfig.h"

GameConfig::GameConfig()
{
	//��ʼ��Ϸ�Ѷ�Ϊ��
	mLevel = LOW;
	//������Ϸ�Ѷ�
	setLevel(mLevel);
	bulletIndex = 0;
	scoreFileRecord = new ScoreFileRecord();
}

void GameConfig::setLevel(level newLevel)
{
	//������Ϸ�Ѷ� ������Ϸ����
	mLevel = newLevel;
	//����ѡ�� ������Ϸ����
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
