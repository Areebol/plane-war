//EnemyBulletC.h
//log:2022/6/3
//EnemyBulletC��Ķ���

#pragma once
#include "BaseBullet.h"

//�ӵ��˺�
#define ENEMY_BULLET_C_HURT 2
//�ӵ��ľ�����Ϣ
#define ENEMY_BULLET_C_WIDTH 2
#define ENEMY_BULLET_C_HEIGHT 1
//�ӵ����ٶ�
#define ENEMY_BULLET_C_SPEED 10

//�л��ӵ�����C
class EnemyBulletC :
    public BaseBullet//�̳л����ӵ�
{
public:
    //���캯��
    EnemyBulletC(WindowSetter* window = 0, int x = 0, int y = 0, int speed = ENEMY_BULLET_C_SPEED);

    //���ٺ���
    void destroy();
public:
    //��д�ƶ��ӵ�����
    virtual void move();

    //��д�����ӵ�����
    virtual void draw(int index = 0);

private:
    //����ӵ��ƶ�����
    bool swag;
};

