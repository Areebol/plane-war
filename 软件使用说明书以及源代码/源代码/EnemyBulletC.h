//EnemyBulletC.h
//log:2022/6/3
//EnemyBulletC类的定义

#pragma once
#include "BaseBullet.h"

//子弹伤害
#define ENEMY_BULLET_C_HURT 2
//子弹的矩形信息
#define ENEMY_BULLET_C_WIDTH 2
#define ENEMY_BULLET_C_HEIGHT 1
//子弹的速度
#define ENEMY_BULLET_C_SPEED 10

//敌机子弹类型C
class EnemyBulletC :
    public BaseBullet//继承基类子弹
{
public:
    //构造函数
    EnemyBulletC(WindowSetter* window = 0, int x = 0, int y = 0, int speed = ENEMY_BULLET_C_SPEED);

    //销毁函数
    void destroy();
public:
    //重写移动子弹函数
    virtual void move();

    //重写绘制子弹函数
    virtual void draw(int index = 0);

private:
    //存放子弹移动方向
    bool swag;
};

