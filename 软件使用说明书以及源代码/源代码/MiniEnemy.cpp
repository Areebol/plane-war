//MiniEnemy.cpp
//log:2022/6/3
//MiniEnemy��ĳ�Ա�����Ķ���

#include "MiniEnemy.h"

MiniEnemy::MiniEnemy(WindowSetter* window, GameConfig* config, int x, int y)
	:BaseEnemy::BaseEnemy(window,config,x,y),
	shootRecordI(MINI_RECORDI)
{
	//������ʼ��
	blood = MINI_BLOOD;
	rec = Rec(this->x, this->y, MINI_WIDTH, MINI_HEIGHT);
}

void MiniEnemy::move()
{
	//ս�������ƶ�״̬
	if (free == false && moveRecord.update())
	{
		//�����ƶ�
		this->y += 1;
	}
	//ˢ�¾�����Ϣ
	rec.reset(x, y);
	//Խ������
	if (y > WINDOW_ALL_HEIGHT)
		free = true;
}

void MiniEnemy::draw()
{
	//����ս����״
	string sentence;
	sentence = "����  ����";
	window->paintSentence(x, y + 1, 0x06, sentence);
	sentence = "����������";
	window->paintSentence(x, y + 2, 0x04, sentence);
	sentence = "����";
	window->paintSentence(x+3, y + 3, 0x0F, sentence);

	//����Ѫ��
	string bloodS;
	//����Ѫ�����Ƴ���
	for (int i = 0; i < blood/ENEMY_BLOOD_RATIO; ++i)
	{
		bloodS += "-";
	}
	window->paintSentence(x + 1, y - 1, 0x0F, bloodS);
}

void MiniEnemy::shoot()
{
	//���״̬1ˢ��
	if (shootRecordI.update())
	{
		//���
		for(int i=0;i<4;++i)
		shootBulletA(this->x + 4, this->y+i-1);
	}
}

void MiniEnemy::destroy()
{
	//���û������ٺ���
	BaseEnemy::destroy();
	//����Ѫ��
	blood = MINI_BLOOD;
}

void MiniEnemy::init()
{
	//���û����ʼ������
	BaseEnemy::init();
	//������ʱ��
	shootRecordI.start();
	//����Ѫ��
	blood = MINI_BLOOD;
}
