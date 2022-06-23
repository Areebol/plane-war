//ScoreFileRecord.h
//log:2022/6/6
//ScoreFileRecord类的定义

#pragma once

#include<iostream>
#include<fstream>

//存放游戏最高分数的文件名
#define SCORE_FILE_NAME "PlaneWarScoreRecord.dat"
using std::fstream;
using std::ios;
using std::cerr;
/// <summary>
/// 处理文件中的分数
/// 将游戏的最高分记录
/// 将游戏的最高分记录读出
/// </summary>
class ScoreFileRecord
{
public:
	//构造函数 创建文件
	ScoreFileRecord();

	//析构函数
	~ScoreFileRecord();

	//将文件数据读入数组
	void readHighestScores();

	//将一个新分数写入文件
	bool writeHighestScores(int newRecord);

	//返回最高分数的数组
	const int* getHighestScores();
private:
	//存放数组
	int* highestScores;
};

