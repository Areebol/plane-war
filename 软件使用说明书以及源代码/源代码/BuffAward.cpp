//BuffAward.h
//log:2022/6/3
//BuffAward�ĳ�Ա��������

#include "BuffAward.h"

BuffAward::BuffAward(WindowSetter* window, Plane* plane, int* score,  int x, int y)
	:BaseBuff(window, plane, score, x, y)
{
	//�Բ�����ʼ��
}

void BuffAward::draw()
{
	//����Ϸ�������buffͼ��
	string sentence;
	sentence = "������";
	window->paintSentence(x + 2, y + 1, 0x06, sentence);
	sentence = "�����";
	window->paintSentence(x + 2, y + 2, 0x04, sentence);
	sentence = "������";
	window->paintSentence(x + 2, y + 3, 0x06, sentence);
}

void BuffAward::showInformation()
{
	//����Ϸ������ʾbuff����
	string sentence = "��ý����򣬵÷�����";
	BaseBuff::showInformation(sentence);
}

void BuffAward::use()
{
	//��������
	*score += 100;
}
