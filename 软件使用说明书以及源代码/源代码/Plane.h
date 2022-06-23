//Plane.h
//log:2022/6/3
//Plane��Ķ���

#ifndef PLANE_H
#define PLANE_H

//�ɻ���ʼ����λ��
#define PLANE_BEGIN_X 26
#define PLANE_BEGIN_Y 30
//�ɻ����μ�������
#define PLANE_REC_WIDTH 10
#define PLANE_REC_HEIGHT 3
//�ɻ�Ѫ��
#define PLANE_BLOOD 50
//�ɻ����д�С
#define PLANE_BULLETSA_MAX 40
//�ɻ��ӵ��ٶ�
#define BULLET_SPEED 100
//�ɻ��ӵ��ƶ����
#define BULLET_INTERVAL 300
//�ɻ���ɵ��˺�
#define PLANE_HURT 20

#include"PlaneBulletA.h"
#include"Timer.h"
#include"config.h"
#include"GameConfig.h"
#include"Rec.h"
#include"WindowSetter.h"

//ս����
class Plane
{
public:
	//�������
	enum direction { UP, DOWN, LEFT, RIGHT };
	
	//���캯��
	Plane(WindowSetter* window,GameConfig* config,int x=0,int y=0);
	
	//�ƶ�ս������
	void move(direction d);
	
	//��������ս��λ�ú���
	void moveTo(int x, int y);
	
	//����ս������
	void paint();
	
	//�ж�ս���ݻٺ���
	bool isDead();
	
	//A���ӵ����
	void shootBulletA();
	
	//�ƶ��Ѿ�������ӵ�A
	void moveBulletA();
	
	//�����Ѿ�������ӵ�A
	void drawBulletA();
	
	//�ɻ��ӵ���ײ����
	bool hitObject(Rec& rhs);

	//�ݻ��ӵ�
	void destroyBullet(int index);

	//����x����
	int getX()const;

	//����y����
	int getY()const;

	//���ؾ�����Ϣ
	Rec& getRec();

	//�۳�ս��Ѫ��
	void subBlood(int sub);

	//����ս��Ѫ��
	void addBlood(int add);

	//����ս��Ѫ��
	void setBlood(int blood);

	//����ս��Ѫ��
	int getBlood()const;
private:
	//����
	PlaneBulletA bulletsA[PLANE_BULLETSA_MAX];
	//ս���ƶ��ٶ�
	int planeSpeed;
	//���ڻ���ָ��
	WindowSetter* window;
	//������Ϣ
	int x;
	int y;
	//ս���ӵ���������ʱ��
	Timer bulletTimer;
	//ս���ӵ��ƶ��ٶȼ�ʱ��
	Timer bulletSpeedTimer;
	//��Ϸ��������ָ��
	GameConfig* config;
	//ս��������Ϣ
	Rec rec;
	//ս��Ѫ��
	int blood;
public:	
	//�ɻ���ײ��ɵ��˺�
	const int hurt = PLANE_HURT;
	//�ӵ��˺�
	const int bulletHurt;
};

#endif

