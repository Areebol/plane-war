//HistoryScoreRecord.cpp
//log:2022/6/7
//HistroyScoreRecord类的成员函数的定义

#include "HistoryScoreRecord.h"

using std::to_string;
HistoryScoreRecord::HistoryScoreRecord(WindowSetter* window,ScoreFileRecord* record)
	:window(window),scoreFileRecord(record)
{

}

void HistoryScoreRecord::showHighestScore()
{
	//显示历史分数数据
	updateScreen();

	//获取输入返回
	while(getKeyHit()!=27)
	{
		return;
	}
}

void HistoryScoreRecord::updateScreen()
{
	//清空屏幕
	window->clear_choose();
	window->clear_game();

	//显示分数
	showScore();

	//显示帮助信息
	showHelping();

	window->update();
}

void HistoryScoreRecord::showScore()
{
	//获取最高分数
	const int* recordPtr = scoreFileRecord->getHighestScores();
	window->paint_edge();

	//绘制最高分数信息
	string sentence = "历史最高分数";
	window->paintSentence(28, 10, 0x03, sentence);

	for (int i = 0; i < 3; ++i)
	{
		sentence = to_string(recordPtr[i]);
		window->paintSentence(36, 4 * (i + 4), 0x06, sentence);
		sentence = "record ";
		sentence += to_string(i + 1);
		sentence += ": ";
		window->paintSentence(25, 4 * (i + 4), 0x07, sentence);
	}
}

void HistoryScoreRecord::showHelping()
{
	//绘制提示信息
	string sentence = "按任意键返回......";
	window->paintSentence(24, 30, 0x02, sentence);
}

int HistoryScoreRecord::getKeyHit()
{
	//返回输入
	return _getch();
}
