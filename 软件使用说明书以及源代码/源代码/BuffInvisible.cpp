//BuffInvisble.cpp
//log:2022/6/3
//BuffInvisible���Ա�����Ķ���

#include "BuffInvisible.h"

BuffInvisible::BuffInvisible(WindowSetter* window, Plane* plane, int* score,  int x, int y)
	:BaseBuff(window, plane, score, x, y),useRecord(USE_TIME)
{
	//�Բ������г�ʼ��
	beUsing = true;
}

void BuffInvisible::draw()
{
	//����Ϸ������ʾbuffͼ��
	string sentence;
	sentence = "������";
	window->paintSentence(x + 2, y + 1, 0x06, sentence);
	sentence = "�����";
	window->paintSentence(x + 2, y + 2, 0x08, sentence);
	sentence = "������";
	window->paintSentence(x + 2, y + 3, 0x06, sentence);
}

void BuffInvisible::showInformation()
{
	//����Ϸ������ʾbuff������Ϣ
	string sentence = "�������Ϳ�㣬��ʱ�����ӵ�";
	BaseBuff::showInformation(sentence);
	//ʹ������ʼ��ʱ
	useRecord.start();
}

void BuffInvisible::use()
{
	//��ս���ƶ�������Զ��
	plane->getRec().reset(10000, 10000);

	//���»��Ʒɻ�����ʾЧ��
	WORD color = 0x0F;
	string sentence;
	sentence = "��  ";
	window->paintSentence(plane->getX() + 6, plane->getY(), 0x01, sentence);
	sentence = "��  ��";
	window->paintSentence(plane->getX() + 4, plane->getY() + 1, 0x01, sentence);
	sentence = "��";
	window->paintSentence(plane->getX() + 6, plane->getY() + 1, 0x01, sentence);
	sentence = "����  ����";
	window->paintSentence(plane->getX() + 2, plane->getY() + 2, 0x01, sentence);
	sentence = "��";
	window->paintSentence(plane->getX() + 6, plane->getY() + 2, 0x01, sentence);
	
	//����ʱ�����
	if (useRecord.update())
	{
		//��������
		free = true;
		beUsing = false;
		plane->getRec().reset(plane->getX() + 2, plane->getY());
	}
}
