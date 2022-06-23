//EnemyBulletA.h
//log:2022/6/3
//EnemyBulletA��Ķ���

#pragma once
#include "BaseBullet.h"

//�ӵ��˺�
#define ENEMY_BULLET_A_HURT 2
//�ӵ��ľ�����Ϣ
#define ENEMY_BULLET_A_WIDTH 2
#define ENEMY_BULLET_A_HEIGHT 1
//�ӵ����ƶ��ٶ�
#define ENEMY_BULLET_A_SPEED 10

//�����ӵ�����A
class EnemyBulletA :
    public BaseBullet//�̳л����ӵ�BaseBullet
{
public:
    //���캯��
    EnemyBulletA(WindowSetter* window=0, int x=0, int y=0, int speed=ENEMY_BULLET_A_SPEED);

public:
    //�ӵ��ƶ�����
    virtual void move()override;

    //�����ӵ�����
    virtual void draw(int index = 0)override;
};

