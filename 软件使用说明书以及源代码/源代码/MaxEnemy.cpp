//MaxEnemy.h
//log:2022/6/3
//MaxEnemy��ĳ�Ա�����Ķ���

#include "MaxEnemy.h"

MaxEnemy::MaxEnemy(WindowSetter* window, GameConfig* config, int x, int y)
	:BaseEnemy::BaseEnemy(window, config, x, y),
	shootRecordI(MAX_RECORDI)
{
	//�����ĳ�ʼ��
	blood = MAX_BLOOD;
	rec = Rec(this->x, this->y, MAX_WIDTH, MAX_HEIGHT);
}

void MaxEnemy::move()
{
	//�ƶ�״̬ ���Ҽ�ʱ��ˢ��
	if (free == false && moveRecord.update())
	{
		//��ֱ�����ƶ�һ��
		this->y += 1;
	}
	//���þ���
	rec.reset(x, y);
	//�ж��Ƿ�Խ�� ����
	if (y > WINDOW_ALL_HEIGHT)
		free = true;
}

void MaxEnemy::draw()
{
	//���û��Ƹ�����������
	drawHelper();

	//����Ѫ��
	string bloodS;
	//������Ҫ���Ƶ�Ѫ������
	for (int i = 0; i < blood/ENEMY_BLOOD_RATIO; ++i)
	{
		bloodS += "-";
	}
	window->paintSentence(x + 1, y - 1, 0x0F, bloodS);
}

void MaxEnemy::shoot()
{
	//���״̬1ˢ�� ���
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
	//���û�������ٺ���
	BaseEnemy::destroy();
	//����Ѫ��
	blood = MAX_BLOOD;
}

void MaxEnemy::init()
{
	//���û���ĳ�ʼ������
	BaseEnemy::init();
	//�����м�ʱ����
	shootRecordI.start();
	//����Ѫ��
	blood = MAX_BLOOD;
}

void MaxEnemy::drawHelper()
{
	/// <summary>
	/// ���´���Ϊ�˻���max����ս��
	/// </summary>
	string sentence;
	sentence = "��";
	window->paintSentence(x, y, 0x08, sentence);
	sentence = "��  ��";
	window->paintSentence(x + 4, y, 0x09, sentence);
	sentence = "��";
	window->paintSentence(x + 12, y, 0x08, sentence);
	sentence = "��          ��";
	window->paintSentence(x, y + 1, 0x08, sentence);
	sentence = "������";
	window->paintSentence(x + 4, y + 1, 0x09, sentence);
	sentence = "��          ��";
	window->paintSentence(x, y + 2, 0x08, sentence);
	sentence = "����  ����";
	window->paintSentence(x + 2, y + 2, 0x09, sentence);
	sentence = "��";
	window->paintSentence(x + 6, y + 2, 0x04, sentence);
	sentence = "��          ��";
	window->paintSentence(x, y + 3, 0x08, sentence);
	sentence = "����  ����";
	window->paintSentence(x + 2, y + 3, 0x06, sentence);
	sentence = "��";
	window->paintSentence(x + 6, y + 3, 0x04, sentence);
	sentence = "��          ��";
	window->paintSentence(x, y + 4, 0x08, sentence);
	sentence = "��  ��";
	window->paintSentence(x + 4, y + 4, 0x06, sentence);
}
