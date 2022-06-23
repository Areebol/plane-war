//bossEnemy->cpp
//log:2022/6/3
//BossEnemy��ĳ�Ա�����Ķ���

#include "BossEnemy.h"

BossEnemy::BossEnemy(WindowSetter* window, GameConfig* config, int x, int y)
	:BaseEnemy::BaseEnemy(window, config, x, y),
	shootRecordI(BOSS_RECORDI),shootRecordII(BOSS_RECORDII),shootRecordIII(BOSS_RECORDIII)
{
	//��ʼ������
	blood = BOSS_BLOOD;
	rec = Rec(this->x, this->y, BOSS_WIDTH, BOSS_HEIGHT);
}

void BossEnemy::move()
{
	//�ж��Ƿ������Լ��Ƿ񵽴��ƶ�ʱ��
	//�����ƶ�
	if (free == false && moveRecord.update())
	{
		//�������������Ϣ
		this->y += rand() % 2;
		this->x += rand() % 3 - 1;

		//��������ƶ�
		while (this->x > GAME_WIDTH - BOSS_WIDTH + 1 || this->x < 2)
		{
			this->x += rand() % 3 - 1;
		}
	}

	//���þ���������Ϣ
	rec.reset(x, y);
	//�����߽� ����
	if (y > WINDOW_ALL_HEIGHT)
		free = true;
}

void BossEnemy::draw()
{
	//���ø�����������ս��
	drawHelper();

	//����Ѫ��
	string bloodS;
	//����Ѫ��ʣ����
	for (int i = 0; i < blood/ENEMY_BLOOD_RATIO; ++i)
	{
		bloodS += "-";
	}
	window->paintSentence(x + 1, y - 1, 0x0F, bloodS);
}

void BossEnemy::shoot()
{
	//���״̬1ˢ��
	if (shootRecordI.update())
	{
		shootBulletB(this->x + 10, this->y + 9);
		shootBulletC(this->x + 26, this->y + 9);
	}
	//���״̬2ˢ��
	if (shootRecordII.update())
	{
		shootBulletD(this->x + 24, this->y + 9);
		shootBulletD(this->x + 12, this->y + 9);
	}
	//���״̬3ˢ��
	if (shootRecordIII.update())
	{
		for (int i = 0; i < 10; ++i)
			shootBulletA(this->x + 2*i + 10, this->y + 9);
	}
}

void BossEnemy::init()
{
	//���û����ʼ��������ʼ��
	BaseEnemy::init();
	//�������м�ʱ��
	shootRecordI.start();
	shootRecordII.start();
	shootRecordIII.start();
	//����Ѫ��
	blood = BOSS_BLOOD;
}

void BossEnemy::destory()
{
	//���û������ٺ���
	BaseEnemy::destroy();
	//����Ѫ��
	blood = BOSS_BLOOD;
}

void BossEnemy::drawHelper()
{
	/// <summary>
	/// ���´�����Ϊ�˻��Ƹ��ӵ�ս��
	/// ��Ϊ���� ��ɬ�Ѷ�
	/// ��������ռ�ڴ治��
	/// ��ֱ�ӷ����ڴ���ֱ�ӻ���
	/// </summary>
	string sentence;
	WORD color1 = 0x09;
	WORD color2 = 0x0B;
	WORD color3 = 0x0F;
	WORD color4 = 0x0C;
	sentence = "������                      ������";
	window->paintSentence(x + 2, y, color1, sentence);
	sentence = "��      ��                  ��      ��";
	window->paintSentence(x, y + 1, color1, sentence);
	sentence = "��      ��      ��  ��      ��      ��";
	window->paintSentence(x, y + 2, color1, sentence);
	sentence = "��              ������              ��";
	window->paintSentence(x, y + 3, color1, sentence);
	sentence = "����    ��  ��    ����";
	window->paintSentence(x + 8, y + 5, color1, sentence);
	sentence = "��      ��  ������  ��      ��";
	window->paintSentence(x + 4, y + 6, color1, sentence);
	sentence = "��      ��  ��  ��  ��      ��";
	window->paintSentence(x + 4, y + 7, color1, sentence);
	sentence = "��      ��  ��  ��  ��      ��";
	window->paintSentence(x + 4, y + 8, color1, sentence);
	sentence = "������    ��  ��    ������";
	window->paintSentence(x + 6, y + 9, color1, sentence);
	sentence = "��  ��";
	window->paintSentence(x + 2, y + 1, color2, sentence);
	window->paintSentence(x + 30, y + 1, color2, sentence);
	window->paintSentence(x + 6, y + 6, color2, sentence);
	window->paintSentence(x + 26, y + 6, color2, sentence);
	sentence = "��  ��";
	window->paintSentence(x + 2, y + 3, color2, sentence);
	window->paintSentence(x + 30, y + 3, color2, sentence);
	window->paintSentence(x + 6, y + 8, color2, sentence);
	window->paintSentence(x + 26, y + 8, color2, sentence);
	sentence = "������";
	window->paintSentence(x + 8, y + 3, color3, sentence);
	window->paintSentence(x + 8, y + 4, color3, sentence);
	window->paintSentence(x + 24, y + 3, color3, sentence);
	window->paintSentence(x + 24, y + 4, color3, sentence);
	sentence = "��";
	window->paintSentence(x + 10, y + 2, color3, sentence);
	window->paintSentence(x + 12, y + 1, color3, sentence);
	sentence = "��";
	window->paintSentence(x + 24, y + 1, color3, sentence);
	window->paintSentence(x + 26, y + 2, color3, sentence);
	sentence = "��";
	window->paintSentence(x + 24, y + 2, color3, sentence);
	window->paintSentence(x + 12, y + 2, color3, sentence);
	sentence = "��";
	window->paintSentence(x + 12, y + 5, color3, sentence);
	sentence = "��";
	window->paintSentence(x + 24, y + 5, color3, sentence);
	sentence = "��";
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
	sentence = "��";
	window->paintSentence(x + 2, y + 4, color4, sentence);
	window->paintSentence(x + 4, y + 5, color4, sentence);
	window->paintSentence(x + 14, y + 7, color4, sentence);
	sentence = "��";
	window->paintSentence(x + 34, y + 4, color4, sentence);
	window->paintSentence(x + 32, y + 5, color4, sentence);
	window->paintSentence(x + 22, y + 7, color4, sentence);
}
