//EnemyBulletB.cpp
//log:2022/6/3
//EnemyBulletB类的成员函数的定义

#include "EnemyBulletB.h"

EnemyBulletB::EnemyBulletB(WindowSetter* window, int x, int y, int speed)
	:BaseBullet::BaseBullet(window, x, y, speed)
{
	//参数初始化
	rec = Rec(x, y, ENEMY_BULLET_B_WIDTH, ENEMY_BULLET_B_HEIGHT);
	swag = true;//真的时候向左移动
}

void EnemyBulletB::destroy()
{
	//调用基类的销毁函数
	BaseBullet::destroy();
	//初始化方向量
	swag = true;
}

void EnemyBulletB::move()
{
	//如果子弹超出边界 
	//子弹超出边界
	if (free || y > WINDOW_ALL_HEIGHT || y <= 3||x<=1||x>GAME_WIDTH+2)
	{
		//子弹销毁
		destroy();
		return;
	}

	//达到移动时间间隔
	if (moveRecord.update())
	{
		if (swag)//向左移动
		{
			//每次移动2格
			if (x > 3)
			{
				x -= 2;
			}
			else if (x > 2)
			{
				x -= 1;
			}
			//子弹到达左边界 切换方向
			else
			{
				x += 2;
				swag = false;
			}
		}
		else//向右移动
		{
			//每次移动2格
			if (x < GAME_WIDTH - 1)
				x += 2;
			else if (x < GAME_WIDTH)
				x += 1;
			//子弹到达右边界 切换方向
			else
			{
				x -= 2;
				swag = true;
			}
		}
		//子弹向下移动一格
		y += 1;
	}
	//移动矩形位置
	rec.reset(x, y);
}

void EnemyBulletB::draw(int index)
{
	//绘制子弹
	WORD color;
	string sentence;
	//根据下标参数进行选择
	switch (index)
	{
	case 0:
		color = 0x05;
		sentence = "●";
		//绘制子弹
		window->paintSentence(x, y, color, sentence);
		break;
	default:
		color = 0x05;
		sentence = "◆";
		//绘制子弹
		window->paintSentence(x, y, color, sentence);
	}
}
