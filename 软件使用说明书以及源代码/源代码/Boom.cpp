//Boom.cpp
//log:2022/6/3
//Boom��ĳ�Ա�����Ķ���

#include "Boom.h"

Boom::Boom(WindowSetter* window, int x, int y)
	:window(window), x(x), y(y),free(true),
	record(0)
{
	//������ʼ��
}

void Boom::paint()
{
	//�����ըЧ������ ����
	if (free)
		return;

	//���Ʊ�ըЧ��
	WORD color = 0x02;
	string sentence;
	sentence = "��";
	window->paintSentence(x+2, y, color, sentence);
	sentence = "����";
	window->paintSentence(x, y+1, color, sentence);
	sentence = "��";
	window->paintSentence(x+2, y+2, color, sentence);
	//��¼����
	record++;
}

void Boom::reset()
{
	//����ʱ���¼
	if (free||record<7)
		return;
	//����ʱ�����
	free = true;
	record = 0;
}

void Boom::resetPosition(int newX, int newY)
{
	//���ݲ���������������
	this->x = newX;
	this->y = newY;
}

bool Boom::isFree() const
{
	return free;
}

void Boom::setFree(bool state)
{
	free = state;
}
