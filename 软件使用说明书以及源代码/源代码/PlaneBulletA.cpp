//PlaneBulletA.cpp
//log:2022/6/3
//PlaneBulletA类的成员函数的定义

#include "PlaneBulletA.h"

PlaneBulletA::PlaneBulletA(WindowSetter* window, int x, int y, int speed)
	:BaseBullet::BaseBullet(window, x, y, speed)
{
	//参数初始化
	rec = Rec(x, y, PLANE_BULLET_A_WIDTH, PLANE_BULLET_A_HEIGHT);
}

void PlaneBulletA::move()
{
	//如果子弹超出边界
	if (free||y > WINDOW_ALL_HEIGHT || y <= 3)
	{
		//超出边界 销毁
		destroy();
		return;
	}

	//达到移动时间间隔
	if (moveRecord.update())
	--y;//向上移动
	//重置子弹的矩形信息
	rec.reset(x, y);
}

void PlaneBulletA::draw(int index)
{
	//绘制子弹形状
	WORD color=0x02;
	static WORD continueColor = 0x00;
	string sentence;
	//根据下标参数进行选择
	switch (index)
	{
	case 0:
		//绘制1
		color = 0x02;
		sentence = "01";
		//绘制子弹
		window->paintSentence(x, y, color, sentence);
		sentence = "10";
		//绘制子弹
		window->paintSentence(x, y+1, color, sentence);
		break;
	case 1:
		//绘制2
		color = 0x07;
		sentence = "◆";
		//绘制子弹
		window->paintSentence(x, y, color, sentence);
		color = 0x04;
		sentence = "◆";
		//绘制子弹
		window->paintSentence(x, y + 1, color, sentence); 
		break;
	case 2:
		//绘制3
		continueColor = (continueColor + 1) % 0x0F;
		sentence = "01";
		//绘制子弹
		window->paintSentence(x, y, continueColor, sentence);
		continueColor = (continueColor + 1) % 0x0F;
		sentence = "10";
		//绘制子弹
		window->paintSentence(x, y + 1, continueColor, sentence); 
		break;
	default:
		//绘制4
		continueColor = (continueColor + 1) % 0x0F;
		sentence = "◆";
		//绘制子弹
		window->paintSentence(x, y, continueColor, sentence);
		continueColor = (continueColor + 1) % 0x0F;
		sentence = "◆";
		//绘制子弹
		window->paintSentence(x, y + 1, continueColor, sentence);
	}

}
