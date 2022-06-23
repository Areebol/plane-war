//EnemyBulletD.h
//log:2022/6/3
//EnemyBulletD类的成员函数的定义

#include "EnemyBulletD.h"

EnemyBulletD::EnemyBulletD(WindowSetter* window, int x, int y, int speed)
	:BaseBullet::BaseBullet(window, x, y, speed)
{
	//参数初始化
	rec = Rec(x, y, ENEMY_BULLET_D_WIDTH, ENEMY_BULLET_D_HEIGHT);
}

void EnemyBulletD::move()
{
	//如果子弹超出边界 
	//超出边界
	if (free || y > WINDOW_ALL_HEIGHT || y <= 3)
	{
		//子弹销毁并退出
		destroy();
		return;
	}

	//达到移动时间间隔
	if (moveRecord.update())
		++y;//向下移动
	//移动矩形位置
	rec.reset(x, y);
}

void EnemyBulletD::draw(int index)
{
	//绘制子弹形状
	WORD color1;
	WORD color2;
	string sentence;
	//默认绘制
	switch (index)
	{
	case 0:
		color1 = 0x07;
		color2 = 0x04;
		sentence = "◥";
		window->paintSentence(x, y, color2, sentence);
		sentence = "■";
		window->paintSentence(x+2, y, color1, sentence);
		sentence = "◤";
		window->paintSentence(x+4, y, color2, sentence);
		sentence = "■";
		window->paintSentence(x + 2, y + 1, color1, sentence);
		sentence = "▼";
		window->paintSentence(x + 2, y + 2, color1, sentence);
		break;
	default:
		;
	}
}
