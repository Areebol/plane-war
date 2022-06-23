//BuffInvisble.cpp
//log:2022/6/3
//BuffInvisible类成员函数的定义

#include "BuffInvisible.h"

BuffInvisible::BuffInvisible(WindowSetter* window, Plane* plane, int* score,  int x, int y)
	:BaseBuff(window, plane, score, x, y),useRecord(USE_TIME)
{
	//对参数进行初始化
	beUsing = true;
}

void BuffInvisible::draw()
{
	//在游戏区域显示buff图标
	string sentence;
	sentence = "◢■◣";
	window->paintSentence(x + 2, y + 1, 0x06, sentence);
	sentence = "■●■";
	window->paintSentence(x + 2, y + 2, 0x08, sentence);
	sentence = "◥■◤";
	window->paintSentence(x + 2, y + 3, 0x06, sentence);
}

void BuffInvisible::showInformation()
{
	//在游戏区域显示buff功能信息
	string sentence = "获得隐形涂层，暂时无视子弹";
	BaseBuff::showInformation(sentence);
	//使用器开始计时
	useRecord.start();
}

void BuffInvisible::use()
{
	//将战机移动到无穷远处
	plane->getRec().reset(10000, 10000);

	//重新绘制飞机的显示效果
	WORD color = 0x0F;
	string sentence;
	sentence = "▲  ";
	window->paintSentence(plane->getX() + 6, plane->getY(), 0x01, sentence);
	sentence = "◢  ◣";
	window->paintSentence(plane->getX() + 4, plane->getY() + 1, 0x01, sentence);
	sentence = "●";
	window->paintSentence(plane->getX() + 6, plane->getY() + 1, 0x01, sentence);
	sentence = "◢◤  ◥◣";
	window->paintSentence(plane->getX() + 2, plane->getY() + 2, 0x01, sentence);
	sentence = "▼";
	window->paintSentence(plane->getX() + 6, plane->getY() + 2, 0x01, sentence);
	
	//持续时间结束
	if (useRecord.update())
	{
		//销毁数据
		free = true;
		beUsing = false;
		plane->getRec().reset(plane->getX() + 2, plane->getY());
	}
}
