//EnemyBulletB.cpp
//log:2022/6/3
//EnemyBulletB��ĳ�Ա�����Ķ���

#include "EnemyBulletB.h"

EnemyBulletB::EnemyBulletB(WindowSetter* window, int x, int y, int speed)
	:BaseBullet::BaseBullet(window, x, y, speed)
{
	//������ʼ��
	rec = Rec(x, y, ENEMY_BULLET_B_WIDTH, ENEMY_BULLET_B_HEIGHT);
	swag = true;//���ʱ�������ƶ�
}

void EnemyBulletB::destroy()
{
	//���û�������ٺ���
	BaseBullet::destroy();
	//��ʼ��������
	swag = true;
}

void EnemyBulletB::move()
{
	//����ӵ������߽� 
	//�ӵ������߽�
	if (free || y > WINDOW_ALL_HEIGHT || y <= 3||x<=1||x>GAME_WIDTH+2)
	{
		//�ӵ�����
		destroy();
		return;
	}

	//�ﵽ�ƶ�ʱ����
	if (moveRecord.update())
	{
		if (swag)//�����ƶ�
		{
			//ÿ���ƶ�2��
			if (x > 3)
			{
				x -= 2;
			}
			else if (x > 2)
			{
				x -= 1;
			}
			//�ӵ�������߽� �л�����
			else
			{
				x += 2;
				swag = false;
			}
		}
		else//�����ƶ�
		{
			//ÿ���ƶ�2��
			if (x < GAME_WIDTH - 1)
				x += 2;
			else if (x < GAME_WIDTH)
				x += 1;
			//�ӵ������ұ߽� �л�����
			else
			{
				x -= 2;
				swag = true;
			}
		}
		//�ӵ������ƶ�һ��
		y += 1;
	}
	//�ƶ�����λ��
	rec.reset(x, y);
}

void EnemyBulletB::draw(int index)
{
	//�����ӵ�
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
