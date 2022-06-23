//EnemyBulletC.cpp
//log:2022/6/3
//EnemyBulletC��ĳ�Ա��������

#include "EnemyBulletC.h"

EnemyBulletC::EnemyBulletC(WindowSetter* window, int x, int y, int speed)
	:BaseBullet::BaseBullet(window, x, y, speed)
{
	//������ʼ��
	rec = Rec(x, y, ENEMY_BULLET_C_WIDTH, ENEMY_BULLET_C_HEIGHT);
	swag = true;//���ʱ�������ƶ�
}

void EnemyBulletC::destroy()
{
	//���û������ٺ���
	BaseBullet::destroy();
	//��ʼ��������
	swag = true;
}

void EnemyBulletC::move()
{
	//����ӵ������߽�
	//�ӵ������߽�
	if (free || y > WINDOW_ALL_HEIGHT || y <= 3||x<=1||x>GAME_WIDTH+2)
	{
		//�ӵ����ٲ�����
		destroy();
		return;
	}

	//�ﵽ�ƶ�ʱ����
	if (moveRecord.update())
	{
		if (!swag)//�����ƶ�
		{
			//�ƶ�2��
			if (x > 3)
			{
				x -= 2;
			}
			else if (x > 2)
			{
				x -= 1;
			}
			//������߽� �л�����
			else
			{
				x += 2;
				swag = true;
			}
		}
		else//�����ƶ�
		{
			//�ƶ�2��
			if (x < GAME_WIDTH - 1)
				x += 2;
			else if (x < GAME_WIDTH)
				x += 1;
			//�����ұ߽� �л�����
			else
			{
				x -= 2;
				swag = false;
			}
		}
		//�����ƶ�1��
		y += 1;
	}
	//�����ƶ�����
	rec.reset(x, y);
}

void EnemyBulletC::draw(int index)
{
	//�����ӵ���״
	WORD color;
	string sentence;
	//�����±��������ѡ��
	switch (index)
	{
	case 0:
		color = 0x05;
		sentence = "��";
		//�����ӵ�
		window->paintSentence(x, y, color, sentence);
		break;
	default:
		color = 0x05;
		sentence = "��";
		//�����ӵ�
		window->paintSentence(x, y, color, sentence);
	}
}
