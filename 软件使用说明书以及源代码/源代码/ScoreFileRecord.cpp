//ScoreFileRecord.cpp
//log:2022/6/6
//ScoreFileRecord的成员函数的定义

#include "ScoreFileRecord.h"

ScoreFileRecord::ScoreFileRecord()
{
	//在堆区创建数据
	highestScores = new int[3]();
	//尝试打开文件存放数据
	fstream tryOpenFile(SCORE_FILE_NAME);
	
	//如果文件不存在 创建文件
	if (!tryOpenFile)
	{
		fstream createFile;
		//输入方式打开文件
		createFile.open(SCORE_FILE_NAME, ios::out);
		int emptyRecord = 0;
		if (!createFile)
		{
			cerr << "File failed to open!";
			exit(EXIT_FAILURE);
		}
		//以二进制方式输入数据
		for (int i = 0; i < 3; ++i)
		{
			createFile.seekp(i * sizeof(int));
			createFile.write(reinterpret_cast<const char*>(&emptyRecord), sizeof(int));
		}createFile.seekg(0);
		createFile.close();
	}
	//将数据存放到类中
	readHighestScores();
	tryOpenFile.close();
}

ScoreFileRecord::~ScoreFileRecord()
{
	//释放堆区数据
	delete[] highestScores;
}

void ScoreFileRecord::readHighestScores()
{
	//以输出的方式打开文件
	fstream readFromFile(SCORE_FILE_NAME,ios::in);
	if (!readFromFile)
	{
		cerr << "File failed to open!";
		exit(EXIT_FAILURE);
	}
	//以二进制的方式输出数据
	for (int i = 0; i < 3; ++i)
	{
		readFromFile.seekg(i * sizeof(int));
		readFromFile.read(reinterpret_cast<char*>(&highestScores[i]), sizeof(int));
	}
	readFromFile.close();
}

bool ScoreFileRecord::writeHighestScores(int newRecord)
{
	//判断数据是否合理
	if (newRecord <= highestScores[2])
		return false;
	//存放新的记录
	highestScores[2] = newRecord;
	
	//进行排序
	for (int i = 0; i < 3 - 1; i++)
	{
		int max = i;
		for (int j = i + 1; j < 3; j++)
			if (highestScores[j] > highestScores[max])
				max = j;
		std::swap(highestScores[i], highestScores[max]);
	}

	fstream writeToFile(SCORE_FILE_NAME, ios::out);
	if (!writeToFile)
	{
		cerr << "wrong";
		exit(1);
	}

	//重新写入新的数据
	for (int i = 0; i < 3; ++i)
	{
		writeToFile.seekp(i * sizeof(int));
		writeToFile.write(reinterpret_cast<const char*>(&highestScores[i]), sizeof(int));
	}
	writeToFile.close();

	//写入成功
	return true;
}

const int* ScoreFileRecord::getHighestScores()
{
	//将最高分数返回
	return highestScores;
}
