//BuffAntidote.cpp
//log:2022/6/3
//BuffAntidote��ĳ�Ա��������

#include "BuffAntidote.h"

BuffAntidote::BuffAntidote(WindowSetter* window, Plane* plane, int* score, 
	 int x, int y)
	:BaseBuff(window ,  plane ,  score,  x, y )
{
	//�Բ������г�ʼ��
}

void BuffAntidote::draw()
{
	//����buff��ͼ��
	string sentence;
	sentence = "������";
	window->paintSentence(x + 2, y + 1, 0x06, sentence);
	sentence = "�����";
	window->paintSentence(x + 2, y + 2, 0x07, sentence);
	sentence = "������";
	window->paintSentence(x + 2, y + 3, 0x06, sentence);
}

void BuffAntidote::showInformation()
{
	//����Ϸ������ʾbuff����
	string sentence = "��ò�����ս���;�����";
	BaseBuff::showInformation(sentence);
}

void BuffAntidote::use()
{
	//ս��Ѫ������
	plane->addBlood(50);
}
