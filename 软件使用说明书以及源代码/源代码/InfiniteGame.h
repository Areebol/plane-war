//InfiniteGame.h
//log:2022/6/4
//InfiniteGame�ඨ��

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

//�л�mini�������
#define MINI_MAX ENEMY_MINI_MAX
//�л�max�������
#define MAX_MAX ENEMY_MAX_MAX

using std::to_string;
using std::vector;

//�޾�ģʽ��
class InfiniteGame
{
public:
	//���캯��
	InfiniteGame(WindowSetter* window, GameConfig* config, Plane* plane);

	//��������
	~InfiniteGame();

	/////////////////////��Ϸ���غ���/////////////////////////////
	//��Ϸ����
	void game();
	
private:
	//��ͣ��Ϸ����
	bool pause();
	
	//��Ϸ���ݸ���
	void gameUpdate();

	//������ͣ���ѡ����
	void paintPause(int select);
	
	//����������ʾ��Ϣ����
	void paintOther();

	//������������
	void paintDead();

	//�����Ƽ�¼����
	void paintBreaking();
	////////////////////////���Ƶл���Ϊ����///////////////////////////////////
	//�ͷŵл�
	void releaseEnemy();
	
	//�л��ͷ�1
	void releaseEnemyI();
	
	//�л��ͷ�2
	void releaseEnemyII();
	
	//�л��ͷ�3
	void releaseEnemyIII();
	
	//�ƶ��л�
	void moveAllEnemy();
	
	//���Ƶл�
	void drawAllEnemy();
	
	//��������л�
	void clearDeadEnemy();
	
	//�л����
	void shootEnemy();
	
	//�л��ӵ���Ϊ
	void controlEnemyBullet();
	
	//���Ƶл�����
	void controlEnemy();
	
	//�жϵл���������
	void winEnemy();

	//////////////////////////////////buff����ƺ���//////////////////////////////////////

	//�ͷŶ�Ӧ��buff��
	void releaseBuffs();
	
	//�������е�buff��
	void drawBuffs();
	
	//�ƶ��ִ��buff��
	void moveBuffs();
	
	//ʰȡbuff��ʹ��
	void pickBuffs();
	
	//���ڳ����Ե�buff��ʹ��
	void useBuffs();
	
	//����buff������
	void deleteBuffs();
	
	//��buff�Ĳ�������
	void controlBuffs();
	
	//////////////////////////�ҷ�ս�����ƺ���/////////////////////////////////////////////
	//���ڼ���ս���Ĳ���
	void controlPlane();

	///////////////////////////��ըЧ�����ƺ���//////////////////////////////////////
	//���Ʊ�ըЧ������
	void paintBoom();
	
	//���ñ�ըЧ��
	void setBoom(int x, int y);

	//////////////////////////�����ײ����/////////////////////////////////////
	//��ײ������
	void collisionAll();
	
	//���л����ҷ�ս���ӵ���ײ����
	void collisionEnemyWithPlaneBullet();
	
	//���л����ҷ�ս����ײ����
	void collisionEnemyWithPlane();
	
	//���л��ӵ����ҷ�ս����ײ����
	void collisionPlaneWithEnemyBullet();

	//////////////////////////��Ϸ�������ٺ���/////////////////////////////////
	//����������Ϸ����
	void init();
	//�˳���Ϸ�����Ϸ����
	void destroy();
private:
	//���ڻ���ָ��
	WindowSetter* window;
	//��Ϸ������ָ��
	GameConfig* config;
	//ս��
	Plane* mPlane;
	//��ըЧ������
	Boom* booms[BOOM_MAX];
	//����Ч������
	vector<BaseBuff*>buffs;
	//��Ϸ��ʱ��
	Timer gameRecorder;
	//���Ƽ��̼�ʱ��
	Timer keyboardRecorder;
	//���Ƶл��ͷż�ʱ��
	Timer enemyReleaseRecorder;
	//���Ƶл��ƶ���ʱ��
	Timer enemyMoveRecorder;
	//�����ͷŵ���
	Timer releaseBuffRecorder;
	//��¼�Ծַ���
	int score;
	//�л�����
	MiniEnemy* miniEnemys[MINI_MAX];
	MaxEnemy* maxEnemys[MAX_MAX];
	BossEnemy* bossEnemy;
};


#endif

