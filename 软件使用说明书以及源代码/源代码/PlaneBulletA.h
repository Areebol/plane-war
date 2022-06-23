//PlaneBulletA.h
//log:2022/6/3
//PlaneBulletA��Ķ���

#pragma once
#include "BaseBullet.h"

//�ӵ����˺�
#define PLANE_BULLET_A_HURT 1
//�ӵ��ľ�����Ϣ
#define PLANE_BULLET_A_WIDTH 2
#define PLANE_BULLET_A_HEIGHT 2
//�ӵ����ٶ�
#define PLANE_BULLET_A_SPEED 2

//ս�����ӵ�����A
class PlaneBulletA :
    public BaseBullet//�̳л����ӵ�
{
public:
    //���캯��
    PlaneBulletA(WindowSetter* window=0, int x=0, int y=0, int speed=PLANE_BULLET_A_SPEED);
public:
    //��д�ӵ��ƶ�����
    virtual void move()override;

    //��д�����ӵ�����
    virtual void draw(int index = 0)override;
};

