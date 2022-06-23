//BaseBuff.cpp
//log:2022/6/3
//BaseBuff类的成员函数实现

#include "BaseBuff.h"

BaseBuff::BaseBuff(WindowSetter* window , Plane* plane , int* score ,
	 int x , int y)
	:window(window),free(false), plane(plane),height(4), width(6)
	,beUsing(false),score(score),record(5000)
{
	//对参数进行初始化
	srand((unsigned(time(0))));
	setPosition(x, y);
	rec = Rec(this->x, this->y, width, height);
	record.start();
}


void BaseBuff::showInformation(string& sentence)const
{
	//在游戏区域显示buff功能
	window->clear_game();
	window->paintSentence((GAME_WIDTH - (short)sentence.size()) / 2 + 2,
		WINDOW_HEIGHT / 2 + 2, 0x09, sentence);
	window->update();

	//持续显示一段时间
	Timer windowRecord(1000);
	windowRecord.start();
	while (!windowRecord.update())
		;
	return;
}



void BaseBuff::move()
{
	//根据计时器进行移动
	if (record.update())
	{
		//随机移动
		int choose = rand() % 2;
		int edgeX = GAME_WIDTH - PLANE_REC_WIDTH * 2;
		int edgeY = 3 + WINDOW_HEIGHT - PLANE_REC_HEIGHT;
		switch (choose)
		{
		case 0://左移动
			if (this->x - 1 < 2)
				;
			else
				--this->x;
			break;
		default://右移动
			if (this->x + 1 > edgeX)
				;
			else
				++this->x;
		}

		//越界清除buff
		if (this->y == edgeY)
			free = true;
		else
			++this->y;
	}
	//移动矩形
	rec.reset(this->x, this->y);
}

void BaseBuff::setPosition(int x, int y)
{
	//改变坐标信息
	this->x = x;
	this->y = y;
}

bool& BaseBuff::Free()
{
	return free;
}

