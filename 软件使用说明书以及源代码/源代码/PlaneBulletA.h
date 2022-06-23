//PlaneBulletA.h
//log:2022/6/3
//PlaneBulletA类的定义

#pragma once
#include "BaseBullet.h"

//子弹的伤害
#define PLANE_BULLET_A_HURT 1
//子弹的矩形信息
#define PLANE_BULLET_A_WIDTH 2
#define PLANE_BULLET_A_HEIGHT 2
//子弹的速度
#define PLANE_BULLET_A_SPEED 2

//战机的子弹类型A
class PlaneBulletA :
    public BaseBullet//继承基类子弹
{
public:
    //构造函数
    PlaneBulletA(WindowSetter* window=0, int x=0, int y=0, int speed=PLANE_BULLET_A_SPEED);
public:
    //重写子弹移动函数
    virtual void move()override;

    //重写绘制子弹函数
    virtual void draw(int index = 0)override;
};

