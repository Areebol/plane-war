//EnemyBulletD.h
//log:2022/6/3
//EnemyBulletD��ĳ�Ա�����Ķ���

#include "EnemyBulletD.h"

EnemyBulletD::EnemyBulletD(WindowSetter* window, int x, int y, int speed)
	:BaseBullet::BaseBullet(window, x, y, speed)
{
	//������ʼ��
	rec = Rec(x, y, ENEMY_BULLET_D_WIDTH, ENEMY_BULLET_D_HEIGHT);
}

void EnemyBulletD::move()
{
	//����ӵ������߽� 
	//�����߽�
	if (free || y > WINDOW_ALL_HEIGHT || y <= 3)
	{
		//�ӵ����ٲ��˳�
		destroy();
		return;
	}

	//�ﵽ�ƶ�ʱ����
	if (moveRecord.update())
		++y;//�����ƶ�
	//�ƶ�����λ��
	rec.reset(x, y);
}

void EnemyBulletD::draw(int index)
{
	//�����ӵ���״
	WORD color1;
	WORD color2;
	string sentence;
	//Ĭ�ϻ���
	switch (index)
	{
	case 0:
		color1 = 0x07;
		color2 = 0x04;
		sentence = "��";
		window->paintSentence(x, y, color2, sentence);
		sentence = "��";
		window->paintSentence(x+2, y, color1, sentence);
		sentence = "��";
		window->paintSentence(x+4, y, color2, sentence);
		sentence = "��";
		window->paintSentence(x + 2, y + 1, color1, sentence);
		sentence = "��";
		window->paintSentence(x + 2, y + 2, color1, sentence);
		break;
	default:
		;
	}
}
