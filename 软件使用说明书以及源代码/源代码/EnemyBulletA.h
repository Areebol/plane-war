//EnemyBulletA.h
//log:2022/6/3
//EnemyBulletA类的定义

#pragma once
#include "BaseBullet.h"

//子弹伤害
#define ENEMY_BULLET_A_HURT 2
//子弹的矩形信息
#define ENEMY_BULLET_A_WIDTH 2
#define ENEMY_BULLET_A_HEIGHT 1
//子弹的移动速度
#define ENEMY_BULLET_A_SPEED 10

//敌人子弹类型A
class EnemyBulletA :
    public BaseBullet//继承基类子弹BaseBullet
{
public:
    //构造函数
    EnemyBulletA(WindowSetter* window=0, int x=0, int y=0, int speed=ENEMY_BULLET_A_SPEED);

public:
    //子弹移动函数
    virtual void move()override;

    //绘制子弹函数
    virtual void draw(int index = 0)override;
};

