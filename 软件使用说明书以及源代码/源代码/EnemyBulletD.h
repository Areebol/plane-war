//EnemyBulletD.h
//log:2022/6/3
//EnemyBulletD��Ķ���

#pragma once
#include "BaseBullet.h"

//�ӵ��˺�
#define ENEMY_BULLET_D_HURT 10

//�ӵ�������Ϣ
#define ENEMY_BULLET_D_WIDTH 6
#define ENEMY_BULLET_D_HEIGHT 3
//�ӵ����ٶ�
#define ENEMY_BULLET_D_SPEED 20

//�л��ӵ�������D
class EnemyBulletD :
    public BaseBullet//�̳л����ӵ�
{
public:
    //���캯��
    EnemyBulletD(WindowSetter* window = 0, int x = 0, int y = 0, int speed = ENEMY_BULLET_D_SPEED);

public:
    //��д�ӵ��ƶ�����
    virtual void move()override;

    //��д�ӵ����ƺ���
    virtual void draw(int index = 0)override;
};


