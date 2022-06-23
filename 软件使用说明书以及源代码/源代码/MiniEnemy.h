//MiniEnemy.h
//log:2022/6/3
//MiniEnemy的定义

#pragma once
#include "BaseEnemy.h"

//mini的矩形信息
#define MINI_WIDTH 10
#define MINI_HEIGHT 3
//mini的血量信息
#define MINI_BLOOD 8*ENEMY_BLOOD_RATIO
//状态的计时器
#define MINI_RECORDI 5000

//mini类型战机
class MiniEnemy :
    public BaseEnemy//继承基类战机
{
public:
    //构造函数
    MiniEnemy(WindowSetter* window=0, GameConfig* config=0, int x = 0, int y = 0);

    //重写移动函数
    virtual void move()override;

    //重写绘制函数
    virtual void draw()override;

    //重写射击函数
    virtual void shoot()override;

    //销毁函数
    void destroy();

    //初始化函数
    void init();
private:
    //射击状态的计时器
    Timer shootRecordI;
};

