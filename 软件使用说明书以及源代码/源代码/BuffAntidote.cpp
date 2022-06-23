//BuffAntidote.cpp
//log:2022/6/3
//BuffAntidote类的成员函数定义

#include "BuffAntidote.h"

BuffAntidote::BuffAntidote(WindowSetter* window, Plane* plane, int* score, 
	 int x, int y)
	:BaseBuff(window ,  plane ,  score,  x, y )
{
	//对参数进行初始化
}

void BuffAntidote::draw()
{
	//绘制buff的图形
	string sentence;
	sentence = "◢■◣";
	window->paintSentence(x + 2, y + 1, 0x06, sentence);
	sentence = "■●■";
	window->paintSentence(x + 2, y + 2, 0x07, sentence);
	sentence = "◥■◤";
	window->paintSentence(x + 2, y + 3, 0x06, sentence);
}

void BuffAntidote::showInformation()
{
	//在游戏区域显示buff功能
	string sentence = "获得补给，战机耐久增加";
	BaseBuff::showInformation(sentence);
}

void BuffAntidote::use()
{
	//战机血量增加
	plane->addBlood(50);
}
