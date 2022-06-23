//BaseBuff.cpp
//log:2022/6/3
//BaseBuff��ĳ�Ա����ʵ��

#include "BaseBuff.h"

BaseBuff::BaseBuff(WindowSetter* window , Plane* plane , int* score ,
	 int x , int y)
	:window(window),free(false), plane(plane),height(4), width(6)
	,beUsing(false),score(score),record(5000)
{
	//�Բ������г�ʼ��
	srand((unsigned(time(0))));
	setPosition(x, y);
	rec = Rec(this->x, this->y, width, height);
	record.start();
}


void BaseBuff::showInformation(string& sentence)const
{
	//����Ϸ������ʾbuff����
	window->clear_game();
	window->paintSentence((GAME_WIDTH - (short)sentence.size()) / 2 + 2,
		WINDOW_HEIGHT / 2 + 2, 0x09, sentence);
	window->update();

	//������ʾһ��ʱ��
	Timer windowRecord(1000);
	windowRecord.start();
	while (!windowRecord.update())
		;
	return;
}



void BaseBuff::move()
{
	//���ݼ�ʱ�������ƶ�
	if (record.update())
	{
		//����ƶ�
		int choose = rand() % 2;
		int edgeX = GAME_WIDTH - PLANE_REC_WIDTH * 2;
		int edgeY = 3 + WINDOW_HEIGHT - PLANE_REC_HEIGHT;
		switch (choose)
		{
		case 0://���ƶ�
			if (this->x - 1 < 2)
				;
			else
				--this->x;
			break;
		default://���ƶ�
			if (this->x + 1 > edgeX)
				;
			else
				++this->x;
		}

		//Խ�����buff
		if (this->y == edgeY)
			free = true;
		else
			++this->y;
	}
	//�ƶ�����
	rec.reset(this->x, this->y);
}

void BaseBuff::setPosition(int x, int y)
{
	//�ı�������Ϣ
	this->x = x;
	this->y = y;
}

bool& BaseBuff::Free()
{
	return free;
}

