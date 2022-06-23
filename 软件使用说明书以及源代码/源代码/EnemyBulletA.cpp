//EnemyBulletA.cpp
//log:2022/6/3
//EnemyBulletA��Ĺ��캯���Ķ���

#include "EnemyBulletA.h"

EnemyBulletA::EnemyBulletA(WindowSetter* window, int x, int y, int speed)
	:BaseBullet::BaseBullet(window, x, y, speed)
{
	//�Բ�����ʼ��
	rec = Rec(x, y, ENEMY_BULLET_A_WIDTH, ENEMY_BULLET_A_HEIGHT);
}

void EnemyBulletA::move()
{
	//����ӵ������˱߽�
	if (free || y > WINDOW_ALL_HEIGHT || y <= 3)
	{
		//�ӵ������˳�
		destroy();
		return;
	}
	//ʱ���ʱ��ˢ��
	if (moveRecord.update())
		++y;//�ӵ�����ˢ��

	//���������ӵ���λ����Ϣ
	rec.reset(x, y);
}

void EnemyBulletA::draw(int index)
{
	//�����ӵ���״
	WORD color;//��ɫ����
	string sentence;

	//�����±�������Ʋ�ͬ���ӵ�ͼ��
	switch (index)
	{
	case 0:
		color = 0x04;//��ɫ
		sentence = "��";
		window->paintSentence(x, y, color, sentence);
		break;
	default:
		color = 0x05;//��ɫ
		sentence = "��";
		window->paintSentence(x, y, color, sentence);
	}
}
