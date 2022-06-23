//BaseBullet.h
//log:2022/6/3
//BaseBullet��Ķ���

#pragma once
#include"WindowSetter.h"
#include"Rec.h"
#include"Timer.h"

class EnemyBulletA;
class EnemyBulletB;
class EnemyBulletC;
class EnemyBulletD;
class PlaneBulletA;
//��Ϊ�����������ӵ�
class BaseBullet
{
	friend class EnemyBulletA;
	friend class EnemyBulletB;
	friend class EnemyBulletC;
	friend class EnemyBulletD;
	friend class PlaneBulletA;
public:
	//���캯��
	BaseBullet(WindowSetter* window, int x, int y, int speed);

	//�ƶ��ӵ�����
	virtual void move() = 0;

	//�����ӵ�����
	virtual void draw(int index = 0) = 0;

	//�������ӵ�����λ��
	void reset(int x, int y);

	//�ж��ӵ���������ײ
	bool collision(Rec& rhs);

	//����ӵ�����
	void shoot();

	//�ж��ӵ��Ƿ������״̬����
	bool isShoot()const;

	//�ӵ����ٺ���
	void destroy();

	//����free״̬
	bool isFree()const;

	//����free״̬
	void setFree(bool state);
private:
	//�ӵ�������Ϣ
	int x;
	int y;
	//�ӵ�����״̬
	bool free;
	//�ӵ��ƶ��ٶ�
	int speed;
	//�ӵ��ľ��ζ���
	Rec rec;
	//��Ŵ���ָ������ӵ���
	WindowSetter* window;
	//�ӵ��ƶ���ʱ
	Timer moveRecord;
public:
	//�ӵ����˺�
	int hurt;
};

