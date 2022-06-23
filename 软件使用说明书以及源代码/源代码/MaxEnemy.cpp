//MaxEnemy.h
//log:2022/6/3
//MaxEnemy类的成员函数的定义

#include "MaxEnemy.h"

MaxEnemy::MaxEnemy(WindowSetter* window, GameConfig* config, int x, int y)
	:BaseEnemy::BaseEnemy(window, config, x, y),
	shootRecordI(MAX_RECORDI)
{
	//参数的初始化
	blood = MAX_BLOOD;
	rec = Rec(this->x, this->y, MAX_WIDTH, MAX_HEIGHT);
}

void MaxEnemy::move()
{
	//移动状态 并且计时器刷新
	if (free == false && moveRecord.update())
	{
		//径直向下移动一格
		this->y += 1;
	}
	//重置矩形
	rec.reset(x, y);
	//判断是否越界 销毁
	if (y > WINDOW_ALL_HEIGHT)
		free = true;
}

void MaxEnemy::draw()
{
	//调用绘制辅助函数绘制
	drawHelper();

	//绘制血条
	string bloodS;
	//计算需要绘制的血条长度
	for (int i = 0; i < blood/ENEMY_BLOOD_RATIO; ++i)
	{
		bloodS += "-";
	}
	window->paintSentence(x + 1, y - 1, 0x0F, bloodS);
}

void MaxEnemy::shoot()
{
	//如果状态1刷新 射击
	if (shootRecordI.update())
	{
		for (int i = 0; i < 2; ++i)
			shootBulletA(this->x + 4, this->y + i - 1);
		for (int i = 0; i < 2; ++i)
			shootBulletA(this->x + 8, this->y + i - 1);
	}
}

void MaxEnemy::destroy()
{
	//调用基类的销毁函数
	BaseEnemy::destroy();
	//重置血量
	blood = MAX_BLOOD;
}

void MaxEnemy::init()
{
	//调用基类的初始化函数
	BaseEnemy::init();
	//将所有计时器打开
	shootRecordI.start();
	//重置血量
	blood = MAX_BLOOD;
}

void MaxEnemy::drawHelper()
{
	/// <summary>
	/// 以下代码为了绘制max类型战机
	/// </summary>
	string sentence;
	sentence = "◣";
	window->paintSentence(x, y, 0x08, sentence);
	sentence = "◢  ◣";
	window->paintSentence(x + 4, y, 0x09, sentence);
	sentence = "◢";
	window->paintSentence(x + 12, y, 0x08, sentence);
	sentence = "■          ■";
	window->paintSentence(x, y + 1, 0x08, sentence);
	sentence = "■■■";
	window->paintSentence(x + 4, y + 1, 0x09, sentence);
	sentence = "■          ■";
	window->paintSentence(x, y + 2, 0x08, sentence);
	sentence = "■■  ■■";
	window->paintSentence(x + 2, y + 2, 0x09, sentence);
	sentence = "○";
	window->paintSentence(x + 6, y + 2, 0x04, sentence);
	sentence = "■          ■";
	window->paintSentence(x, y + 3, 0x08, sentence);
	sentence = "◤■  ■◥";
	window->paintSentence(x + 2, y + 3, 0x06, sentence);
	sentence = "○";
	window->paintSentence(x + 6, y + 3, 0x04, sentence);
	sentence = "◥          ◤";
	window->paintSentence(x, y + 4, 0x08, sentence);
	sentence = "◥  ◤";
	window->paintSentence(x + 4, y + 4, 0x06, sentence);
}
