//BuffAward.h
//log:2022/6/3
//BuffAward的成员函数定义

#include "BuffAward.h"

BuffAward::BuffAward(WindowSetter* window, Plane* plane, int* score,  int x, int y)
	:BaseBuff(window, plane, score, x, y)
{
	//对参数初始化
}

void BuffAward::draw()
{
	//在游戏区域绘制buff图标
	string sentence;
	sentence = "◢■◣";
	window->paintSentence(x + 2, y + 1, 0x06, sentence);
	sentence = "■●■";
	window->paintSentence(x + 2, y + 2, 0x04, sentence);
	sentence = "◥■◤";
	window->paintSentence(x + 2, y + 3, 0x06, sentence);
}

void BuffAward::showInformation()
{
	//在游戏区域显示buff功能
	string sentence = "获得奖励球，得分增加";
	BaseBuff::showInformation(sentence);
}

void BuffAward::use()
{
	//分数增加
	*score += 100;
}
