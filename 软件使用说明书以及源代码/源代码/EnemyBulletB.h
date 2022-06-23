//EnemyBulletB.h
//log:2022/6/3
//EnemyBulletB类的定义

#pragma once
#include "BaseBullet.h"

//子弹伤害
#define ENEMY_BULLET_B_HURT 2
//子弹矩形信息
#define ENEMY_BULLET_B_WIDTH 1
#define ENEMY_BULLET_B_HEIGHT 1
//子弹速度
#define ENEMY_BULLET_B_SPEED 10

//敌机子弹类型B
class EnemyBulletB :
    public BaseBullet//继承基类子弹
{
public:
    //构造函数
    EnemyBulletB(WindowSetter* window = 0, int x = 0, int y = 0, int speed = ENEMY_BULLET_B_SPEED);

    //销毁函数
    void destroy();
public:
    //重写子弹移动函数
    virtual void move()override;

    //重写绘制子弹函数
    virtual void draw(int index = 0)override;

private:
    //存放子弹移动方向
    bool swag;
};

