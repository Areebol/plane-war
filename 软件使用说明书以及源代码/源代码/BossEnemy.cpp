//bossEnemy->cpp
//log:2022/6/3
//BossEnemy类的成员函数的定义

#include "BossEnemy.h"

BossEnemy::BossEnemy(WindowSetter* window, GameConfig* config, int x, int y)
	:BaseEnemy::BaseEnemy(window, config, x, y),
	shootRecordI(BOSS_RECORDI),shootRecordII(BOSS_RECORDII),shootRecordIII(BOSS_RECORDIII)
{
	//初始化参数
	blood = BOSS_BLOOD;
	rec = Rec(this->x, this->y, BOSS_WIDTH, BOSS_HEIGHT);
}

void BossEnemy::move()
{
	//判断是否闲置以及是否到达移动时间
	//可以移动
	if (free == false && moveRecord.update())
	{
		//随机设置坐标信息
		this->y += rand() % 2;
		this->x += rand() % 3 - 1;

		//随机左右移动
		while (this->x > GAME_WIDTH - BOSS_WIDTH + 1 || this->x < 2)
		{
			this->x += rand() % 3 - 1;
		}
	}

	//重置矩形坐标信息
	rec.reset(x, y);
	//超出边界 销毁
	if (y > WINDOW_ALL_HEIGHT)
		free = true;
}

void BossEnemy::draw()
{
	//调用辅助函数绘制战机
	drawHelper();

	//绘制血条
	string bloodS;
	//计算血量剩余量
	for (int i = 0; i < blood/ENEMY_BLOOD_RATIO; ++i)
	{
		bloodS += "-";
	}
	window->paintSentence(x + 1, y - 1, 0x0F, bloodS);
}

void BossEnemy::shoot()
{
	//射击状态1刷新
	if (shootRecordI.update())
	{
		shootBulletB(this->x + 10, this->y + 9);
		shootBulletC(this->x + 26, this->y + 9);
	}
	//射击状态2刷新
	if (shootRecordII.update())
	{
		shootBulletD(this->x + 24, this->y + 9);
		shootBulletD(this->x + 12, this->y + 9);
	}
	//射击状态3刷新
	if (shootRecordIII.update())
	{
		for (int i = 0; i < 10; ++i)
			shootBulletA(this->x + 2*i + 10, this->y + 9);
	}
}

void BossEnemy::init()
{
	//调用基类初始化函数初始化
	BaseEnemy::init();
	//启动所有计时器
	shootRecordI.start();
	shootRecordII.start();
	shootRecordIII.start();
	//重置血量
	blood = BOSS_BLOOD;
}

void BossEnemy::destory()
{
	//调用基类销毁函数
	BaseEnemy::destroy();
	//重置血量
	blood = BOSS_BLOOD;
}

void BossEnemy::drawHelper()
{
	/// <summary>
	/// 以下代码是为了绘制复杂的战机
	/// 较为复杂 晦涩难懂
	/// 但由于所占内存不大
	/// 故直接放在内存中直接绘制
	/// </summary>
	string sentence;
	WORD color1 = 0x09;
	WORD color2 = 0x0B;
	WORD color3 = 0x0F;
	WORD color4 = 0x0C;
	sentence = "◢■◣                      ◢■◣";
	window->paintSentence(x + 2, y, color1, sentence);
	sentence = "◢      ◣                  ◢      ◣";
	window->paintSentence(x, y + 1, color1, sentence);
	sentence = "■      ■      ◣  ◢      ■      ■";
	window->paintSentence(x, y + 2, color1, sentence);
	sentence = "◥              ■■■              ◤";
	window->paintSentence(x, y + 3, color1, sentence);
	sentence = "■◣    ■  ■    ◢■";
	window->paintSentence(x + 8, y + 5, color1, sentence);
	sentence = "◢      ◣  ■■■  ◢      ◣";
	window->paintSentence(x + 4, y + 6, color1, sentence);
	sentence = "■      ■  ■  ■  ■      ■";
	window->paintSentence(x + 4, y + 7, color1, sentence);
	sentence = "◥      ◤  ■  ■  ◥      ◤";
	window->paintSentence(x + 4, y + 8, color1, sentence);
	sentence = "◥■◤    ◥  ◤    ◥■◤";
	window->paintSentence(x + 6, y + 9, color1, sentence);
	sentence = "◤  ◥";
	window->paintSentence(x + 2, y + 1, color2, sentence);
	window->paintSentence(x + 30, y + 1, color2, sentence);
	window->paintSentence(x + 6, y + 6, color2, sentence);
	window->paintSentence(x + 26, y + 6, color2, sentence);
	sentence = "◣  ◢";
	window->paintSentence(x + 2, y + 3, color2, sentence);
	window->paintSentence(x + 30, y + 3, color2, sentence);
	window->paintSentence(x + 6, y + 8, color2, sentence);
	window->paintSentence(x + 26, y + 8, color2, sentence);
	sentence = "■■■";
	window->paintSentence(x + 8, y + 3, color3, sentence);
	window->paintSentence(x + 8, y + 4, color3, sentence);
	window->paintSentence(x + 24, y + 3, color3, sentence);
	window->paintSentence(x + 24, y + 4, color3, sentence);
	sentence = "◢";
	window->paintSentence(x + 10, y + 2, color3, sentence);
	window->paintSentence(x + 12, y + 1, color3, sentence);
	sentence = "◣";
	window->paintSentence(x + 24, y + 1, color3, sentence);
	window->paintSentence(x + 26, y + 2, color3, sentence);
	sentence = "■";
	window->paintSentence(x + 24, y + 2, color3, sentence);
	window->paintSentence(x + 12, y + 2, color3, sentence);
	sentence = "◥";
	window->paintSentence(x + 12, y + 5, color3, sentence);
	sentence = "◤";
	window->paintSentence(x + 24, y + 5, color3, sentence);
	sentence = "■";
	for (int i = 0; i < 6; ++i)
	{
		window->paintSentence(x + 14, y + 1 + i, color4, sentence);
		window->paintSentence(x + 22, y + 1 + i, color4, sentence);
	}
	window->paintSentence(x + 4, y + 4, color4, sentence);
	window->paintSentence(x + 6, y + 4, color4, sentence);
	window->paintSentence(x + 30, y + 4, color4, sentence);
	window->paintSentence(x + 32, y + 4, color4, sentence);
	window->paintSentence(x + 6, y + 5, color4, sentence);
	window->paintSentence(x + 30, y + 5, color4, sentence);
	sentence = "◥";
	window->paintSentence(x + 2, y + 4, color4, sentence);
	window->paintSentence(x + 4, y + 5, color4, sentence);
	window->paintSentence(x + 14, y + 7, color4, sentence);
	sentence = "◤";
	window->paintSentence(x + 34, y + 4, color4, sentence);
	window->paintSentence(x + 32, y + 5, color4, sentence);
	window->paintSentence(x + 22, y + 7, color4, sentence);
}
