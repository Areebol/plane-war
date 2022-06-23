//GameConfig.h
//log:2022/6/3
//GameConfig�Ķ���

#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include"config.h"
#include"WindowSetter.h"
#include"ScoreFileRecord.h"

//�л��ƶ����
#define ENEMY_MOVE_INTERVAL 100
//�л��ͷż��
#define ENEMY_RELEASE_INTERVAL 5000

//��Ϸ�Ѷȱ���
enum level { LOW, MIDDLE, HIGH };
//��Ϸ����������
class GameConfig
{
public:
	//���캯��
	GameConfig();

	//������Ϸ�Ѷ�
	void setLevel(level newLevel);

	//������߷���ָ��
	ScoreFileRecord* getScoreFileRecord()const;

	//�����ӵ��±�
	void setBulletIndex(int bulletIndex);

	//�����ӵ��±�
	int getBulletIndex()const;

	//������Ϸ�Ѷ�
	level getLevel()const;

	//���صл��ƶ�ʱ����
	int getEnemyMoveInterval()const;

	//���صл��ͷ�ʱ����
	int getEnemyReleaseInterval()const;
private:
	//�ӵ���Դ�±�
	int bulletIndex;
	//�л�������������Ϣ
	int enemyMoveInterval;
	int enemyReleaseInterval;
	//��Ϸ�Ѷ�
	level mLevel;
	ScoreFileRecord* scoreFileRecord;
};

#endif
