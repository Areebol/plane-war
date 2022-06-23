//EnemyBulletC.cpp
//log:2022/6/3
//EnemyBulletC类的成员函数定义

#include "EnemyBulletC.h"

EnemyBulletC::EnemyBulletC(WindowSetter* window, int x, int y, int speed)
	:BaseBullet::BaseBullet(window, x, y, speed)
{
	//参数初始化
	rec = Rec(x, y, ENEMY_BULLET_C_WIDTH, ENEMY_BULLET_C_HEIGHT);
	swag = true;//真的时候向右移动
}

void EnemyBulletC::destroy()
{
	//调用基类销毁函数
	BaseBullet::destroy();
	//初始化方向量
	swag = true;
}

void EnemyBulletC::move()
{
	//如果子弹超出边界
	//子弹超出边界
	if (free || y > WINDOW_ALL_HEIGHT || y <= 3||x<=1||x>GAME_WIDTH+2)
	{
		//子弹销毁并返回
		destroy();
		return;
	}

	//达到移动时间间隔
	if (moveRecord.update())
	{
		if (!swag)//向左移动
		{
			//移动2格
			if (x > 3)
			{
				x -= 2;
			}
			else if (x > 2)
			{
				x -= 1;
			}
			//到达左边界 切换方向
			else
			{
				x += 2;
				swag = true;
			}
		}
		else//向右移动
		{
			//移动2格
			if (x < GAME_WIDTH - 1)
				x += 2;
			else if (x < GAME_WIDTH)
				x += 1;
			//到达右边界 切换方向
			else
			{
				x -= 2;
				swag = false;
			}
		}
		//向下移动1格
		y += 1;
	}
	//重新移动矩形
	rec.reset(x, y);
}

void EnemyBulletC::draw(int index)
{
	//绘制子弹形状
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
