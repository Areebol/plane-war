//BaseEnemy.h
//log:2022/6/3
//BaseEnemy类的定义

#pragma once
#include "BaseEnemy.h"

//boss的矩形信息
#define BOSS_WIDTH 38
#define BOSS_HEIGHT 10
//boss的血量信息
#define BOSS_BLOOD 36*ENEMY_BLOOD_RATIO

//计时器的参数
#define BOSS_RECORDI 500
#define BOSS_RECORDII 5000
#define BOSS_RECORDIII 7000

//boss类型战机
class BossEnemy :
    public BaseEnemy//继承基类战机
{
public:
    //构造函数
    BossEnemy(WindowSetter* window = 0, GameConfig* config = 0, int x = 0, int y = 0);

    //重写移动战机函数
    virtual void move()override;

    //重写绘制战机函数
    virtual void draw()override;

    //重写射击函数
    virtual void shoot()override;

    //初始化函数
    void init();

    //销毁函数
    void destory();

private:
    //辅助绘制战机函数
    void drawHelper();
    //控制子弹的射击计时器
    Timer shootRecordI;
    Timer shootRecordII;
    Timer shootRecordIII;
};

