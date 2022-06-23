//BuffBoming.cpp
//log:2022/6/3
//BuffBoming类的成员函数定义

#include "BuffBoming.h"
BuffBoming::BuffBoming(BossEnemy* boss, MiniEnemy** minis, MaxEnemy** maxs, WindowSetter* window, Plane* plane, int* score, int x, int y)
	:BaseBuff(window, plane, score, x, y), bossEnemy(boss),maxEnemys(maxs),miniEnemys(minis)
{
	//初始化参数
}

void BuffBoming::draw()
{
	//在游戏区域绘制buff图标
	string sentence;
	sentence = "◢■◣";
	window->paintSentence(x + 2, y + 1, 0x06, sentence);
	sentence = "■●■";
	window->paintSentence(x + 2, y + 2, 0x03, sentence);
	sentence = "◥■◤";
	window->paintSentence(x + 2, y + 3, 0x06, sentence);
}

void BuffBoming::showInformation()
{
	//在游戏区域显示buff功能信息
	string sentence = "发动火力轰炸";
	BaseBuff::showInformation(sentence);
}

void BuffBoming::use()
{
	//对所有处在游戏区域的mini敌机造成伤害
	for (int i = 0; i < ENEMY_MAX_MAX; ++i)
	{
		if (maxEnemys[i]->isFree() == false)
		{
			maxEnemys[i]->subBlood(BOMING_HURT);
		}
	}
	//对所有处在游戏区域的max敌机造成伤害
	for (int i = 0; i < ENEMY_MINI_MAX; ++i)
	{
		if (miniEnemys[i]->isFree() == false)
		{
			miniEnemys[i]->subBlood(BOMING_HURT);
		}
	}
	//对boss敌机造成伤害
	if (bossEnemy->isFree() == false)
	{
		bossEnemy->subBlood(BOMING_HURT);
	}
}
