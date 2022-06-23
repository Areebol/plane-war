//BuffBoming.cpp
//log:2022/6/3
//BuffBoming��ĳ�Ա��������

#include "BuffBoming.h"
BuffBoming::BuffBoming(BossEnemy* boss, MiniEnemy** minis, MaxEnemy** maxs, WindowSetter* window, Plane* plane, int* score, int x, int y)
	:BaseBuff(window, plane, score, x, y), bossEnemy(boss),maxEnemys(maxs),miniEnemys(minis)
{
	//��ʼ������
}

void BuffBoming::draw()
{
	//����Ϸ�������buffͼ��
	string sentence;
	sentence = "������";
	window->paintSentence(x + 2, y + 1, 0x06, sentence);
	sentence = "�����";
	window->paintSentence(x + 2, y + 2, 0x03, sentence);
	sentence = "������";
	window->paintSentence(x + 2, y + 3, 0x06, sentence);
}

void BuffBoming::showInformation()
{
	//����Ϸ������ʾbuff������Ϣ
	string sentence = "����������ը";
	BaseBuff::showInformation(sentence);
}

void BuffBoming::use()
{
	//�����д�����Ϸ�����mini�л�����˺�
	for (int i = 0; i < ENEMY_MAX_MAX; ++i)
	{
		if (maxEnemys[i]->isFree() == false)
		{
			maxEnemys[i]->subBlood(BOMING_HURT);
		}
	}
	//�����д�����Ϸ�����max�л�����˺�
	for (int i = 0; i < ENEMY_MINI_MAX; ++i)
	{
		if (miniEnemys[i]->isFree() == false)
		{
			miniEnemys[i]->subBlood(BOMING_HURT);
		}
	}
	//��boss�л�����˺�
	if (bossEnemy->isFree() == false)
	{
		bossEnemy->subBlood(BOMING_HURT);
	}
}
