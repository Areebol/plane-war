//HistroyScoreRecord.h
//log:2022/6/7
//HitsotyScoreRecord类的定义

#include"WindowSetter.h"
#include"ScoreFileRecord.h"
#include<conio.h>

#pragma once

/// <summary>
/// 显示历史最高分数的类
/// </summary>
class HistoryScoreRecord
{
public:
	//构造函数
	HistoryScoreRecord(WindowSetter* window,ScoreFileRecord* record);

	//显示历史最高分数记录
	void showHighestScore();

private:
	//刷新屏幕数据
	void updateScreen();

	//显示最高分数
	void showScore();

	//显示提示信息
	void showHelping();

	//读取操作返回读取信息
	int getKeyHit();

private:
	//用于绘制窗口
	WindowSetter* window;
	//用于获取文件分数
	ScoreFileRecord* scoreFileRecord;
};

