//BaseEnemy.h
//log:2022/6/3
//BaseEnemy�ඨ��

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

//������
#define SHOOT_INTERVAL 200
//�ƶ�ʱ����
#define MOVE_INTERVAL 600
//�ӵ�A������ص���
#define BULLETA_MAX 60
//�ӵ�B������ص���
#define BULLETB_MAX 20
//�ӵ�C������ص���
#define BULLETC_MAX 20 
//�ӵ�D������ص���
#define BULLETD_MAX 2
//ս��Ѫ���ı仯��ֵ
#define ENEMY_BLOOD_RATIO 2
//ս������Ѫ��
#define BASE_BLOOD 10
class BossEnemy;
class MiniEnemy;
class MaxEnemy;
//ս������
class BaseEnemy
{
	friend class BossEnemy;
	friend class MiniEnemy;
	friend class MaxEnemy;
public:
	//���캯��
	BaseEnemy(WindowSetter* window, GameConfig* config, int x = 0, int y = 0);

	//ս���ƶ�����
	virtual void move()=0;

	//ս�����ƺ���
	virtual void draw()=0;

	//����ս�����꺯��
	void reset(int x, int y);

	//ս����Ѫ����
	void subBlood(int sub);

	//�ж�ս���Ƿ���������
	bool isDead()const;

	//�������ٺ���
	void destroy();

	//��ʼ������
	void init();

	//����ӵ�����
	virtual void shoot()=0;

	//�ƶ������ӵ�����
	void moveAllBullet();

	//���������ӵ�����
	void drawAllBullet();

	//���������ӵ���Ϊ����
	void controlAllBullet();

	//���һöA�ӵ�����
	void shootBulletA(int x,int y);

	//���һöB�ӵ�����
	void shootBulletB(int x,int y);

	//���һöC�ӵ�����
	void shootBulletC(int x,int y);

	//���һöD�ӵ�����
	void shootBulletD(int x,int y);

	//A�����ӵ�������ײ��⺯��
	int hitObjectA(Rec& rhs);

	//B�����ӵ�������ײ��⺯��
	int hitObjectB(Rec& rhs);

	//C�����ӵ�������ײ��⺯��
	int hitObjectC(Rec& rhs);

	//D�����ӵ�������ײ��⺯��
	int hitObjectD(Rec& rhs);

	//���ؾ�����Ϣ
	Rec& getRec();

	//����x����
	int getX()const;
	
	//����y����
	int getY()const;
	
	//����Ѫ��
	double& getBlood();

	//�����Ƿ�����
	bool isFree()const;

	//����free״̬
	void setFree(bool state);
private:
	//������Ϣ
	int x;
	int y;
	//ս������״̬
	bool free;
	//ս��Ѫ��
	double blood;
	//ս��������Ϣ
	Rec rec;
	//����ָ�����ڻ���
	WindowSetter* window;
	//��Ϸ������������ս��
	GameConfig* config;
	//�����ƶ��ļ�ʱ��
	Timer moveRecord;
	//��������ļ�ʱ��
	Timer shootRecord;
	//��Ÿ������͵��ӵ�����
	EnemyBulletA bulletA[BULLETA_MAX];
	EnemyBulletB bulletB[BULLETB_MAX];
	EnemyBulletC bulletC[BULLETC_MAX];
	EnemyBulletD bulletD[BULLETD_MAX];
	vector<EnemyBulletA*> movingBulletsA;
	vector<EnemyBulletB*> movingBulletsB;
	vector<EnemyBulletC*> movingBulletsC;
	vector<EnemyBulletD*> movingBulletsD;
};

