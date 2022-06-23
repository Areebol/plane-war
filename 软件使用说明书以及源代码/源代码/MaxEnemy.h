//MaxEnemy.h
//log:2022/6/3
//MaxEnemy类的定义

#pragma once
#include "BaseEnemy.h"

//max战机的矩形信息
#define MAX_WIDTH 14
#define MAX_HEIGHT 5
//max的血量信息
#define MAX_BLOOD 12*ENEMY_BLOOD_RATIO
//max的子弹射击间隔参数
#define MAX_RECORDI 1000

//max类型战机
class MaxEnemy :
    public BaseEnemy//继承基类战机
{
public:
    //构造函数
    MaxEnemy(WindowSetter* window = 0, GameConfig* config = 0, int x = 0, int y = 0);

    //重写战机移动函数
    virtual void move()override;

    //重写战机绘制函数
    virtual void draw()override;

    //重写战机射击函数
    virtual void shoot()override;

    //战机销毁函数
    void destroy();

    //战机初始化函数
    void init();

    //战机辅助绘制函数
    void drawHelper();
private:
    //战机射击状态的计时器
    Timer shootRecordI;
};

