//EnemyBulletA.cpp
//log:2022/6/3
//EnemyBulletA类的构造函数的定义

#include "EnemyBulletA.h"

EnemyBulletA::EnemyBulletA(WindowSetter* window, int x, int y, int speed)
	:BaseBullet::BaseBullet(window, x, y, speed)
{
	//对参数初始化
	rec = Rec(x, y, ENEMY_BULLET_A_WIDTH, ENEMY_BULLET_A_HEIGHT);
}

void EnemyBulletA::move()
{
	//如果子弹超出了边界
	if (free || y > WINDOW_ALL_HEIGHT || y <= 3)
	{
		//子弹销毁退出
		destroy();
		return;
	}
	//时间计时器刷新
	if (moveRecord.update())
		++y;//子弹向下刷新

	//重新设置子弹的位置信息
	rec.reset(x, y);
}

void EnemyBulletA::draw(int index)
{
	//绘制子弹形状
	WORD color;//颜色参数
	string sentence;

	//根据下标参数绘制不同的子弹图标
	switch (index)
	{
	case 0:
		color = 0x04;//红色
		sentence = "●";
		window->paintSentence(x, y, color, sentence);
		break;
	default:
		color = 0x05;//紫色
		sentence = "◆";
		window->paintSentence(x, y, color, sentence);
	}
}
