//EnemyBulletB.h
//log:2022/6/3
//EnemyBulletB��Ķ���

#pragma once
#include "BaseBullet.h"

//�ӵ��˺�
#define ENEMY_BULLET_B_HURT 2
//�ӵ�������Ϣ
#define ENEMY_BULLET_B_WIDTH 1
#define ENEMY_BULLET_B_HEIGHT 1
//�ӵ��ٶ�
#define ENEMY_BULLET_B_SPEED 10

//�л��ӵ�����B
class EnemyBulletB :
    public BaseBullet//�̳л����ӵ�
{
public:
    //���캯��
    EnemyBulletB(WindowSetter* window = 0, int x = 0, int y = 0, int speed = ENEMY_BULLET_B_SPEED);

    //���ٺ���
    void destroy();
public:
    //��д�ӵ��ƶ�����
    virtual void move()override;

    //��д�����ӵ�����
    virtual void draw(int index = 0)override;

private:
    //����ӵ��ƶ�����
    bool swag;
};

