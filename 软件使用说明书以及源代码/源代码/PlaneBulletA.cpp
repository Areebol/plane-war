//PlaneBulletA.cpp
//log:2022/6/3
//PlaneBulletA��ĳ�Ա�����Ķ���

#include "PlaneBulletA.h"

PlaneBulletA::PlaneBulletA(WindowSetter* window, int x, int y, int speed)
	:BaseBullet::BaseBullet(window, x, y, speed)
{
	//������ʼ��
	rec = Rec(x, y, PLANE_BULLET_A_WIDTH, PLANE_BULLET_A_HEIGHT);
}

void PlaneBulletA::move()
{
	//����ӵ������߽�
	if (free||y > WINDOW_ALL_HEIGHT || y <= 3)
	{
		//�����߽� ����
		destroy();
		return;
	}

	//�ﵽ�ƶ�ʱ����
	if (moveRecord.update())
	--y;//�����ƶ�
	//�����ӵ��ľ�����Ϣ
	rec.reset(x, y);
}

void PlaneBulletA::draw(int index)
{
	//�����ӵ���״
	WORD color=0x02;
	static WORD continueColor = 0x00;
	string sentence;
	//�����±��������ѡ��
	switch (index)
	{
	case 0:
		//����1
		color = 0x02;
		sentence = "01";
		//�����ӵ�
		window->paintSentence(x, y, color, sentence);
		sentence = "10";
		//�����ӵ�
		window->paintSentence(x, y+1, color, sentence);
		break;
	case 1:
		//����2
		color = 0x07;
		sentence = "��";
		//�����ӵ�
		window->paintSentence(x, y, color, sentence);
		color = 0x04;
		sentence = "��";
		//�����ӵ�
		window->paintSentence(x, y + 1, color, sentence); 
		break;
	case 2:
		//����3
		continueColor = (continueColor + 1) % 0x0F;
		sentence = "01";
		//�����ӵ�
		window->paintSentence(x, y, continueColor, sentence);
		continueColor = (continueColor + 1) % 0x0F;
		sentence = "10";
		//�����ӵ�
		window->paintSentence(x, y + 1, continueColor, sentence); 
		break;
	default:
		//����4
		continueColor = (continueColor + 1) % 0x0F;
		sentence = "��";
		//�����ӵ�
		window->paintSentence(x, y, continueColor, sentence);
		continueColor = (continueColor + 1) % 0x0F;
		sentence = "��";
		//�����ӵ�
		window->paintSentence(x, y + 1, continueColor, sentence);
	}

}
