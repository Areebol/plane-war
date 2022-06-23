//EnemyBulletD.h
//log:2022/6/3
//EnemyBulletD类的定义

#pragma once
#include "BaseBullet.h"

//子弹伤害
#define ENEMY_BULLET_D_HURT 10

//子弹矩形信息
#define ENEMY_BULLET_D_WIDTH 6
#define ENEMY_BULLET_D_HEIGHT 3
//子弹的速度
#define ENEMY_BULLET_D_SPEED 20

//敌机子弹的类型D
class EnemyBulletD :
    public BaseBullet//继承基类子弹
{
public:
    //构造函数
    EnemyBulletD(WindowSetter* window = 0, int x = 0, int y = 0, int speed = ENEMY_BULLET_D_SPEED);

public:
    //重写子弹移动函数
    virtual void move()override;

    //重写子弹绘制函数
    virtual void draw(int index = 0)override;
};


