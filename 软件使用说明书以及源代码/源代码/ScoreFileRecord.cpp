//ScoreFileRecord.cpp
//log:2022/6/6
//ScoreFileRecord�ĳ�Ա�����Ķ���

#include "ScoreFileRecord.h"

ScoreFileRecord::ScoreFileRecord()
{
	//�ڶ�����������
	highestScores = new int[3]();
	//���Դ��ļ��������
	fstream tryOpenFile(SCORE_FILE_NAME);
	
	//����ļ������� �����ļ�
	if (!tryOpenFile)
	{
		fstream createFile;
		//���뷽ʽ���ļ�
		createFile.open(SCORE_FILE_NAME, ios::out);
		int emptyRecord = 0;
		if (!createFile)
		{
			cerr << "File failed to open!";
			exit(EXIT_FAILURE);
		}
		//�Զ����Ʒ�ʽ��������
		for (int i = 0; i < 3; ++i)
		{
			createFile.seekp(i * sizeof(int));
			createFile.write(reinterpret_cast<const char*>(&emptyRecord), sizeof(int));
		}createFile.seekg(0);
		createFile.close();
	}
	//�����ݴ�ŵ�����
	readHighestScores();
	tryOpenFile.close();
}

ScoreFileRecord::~ScoreFileRecord()
{
	//�ͷŶ�������
	delete[] highestScores;
}

void ScoreFileRecord::readHighestScores()
{
	//������ķ�ʽ���ļ�
	fstream readFromFile(SCORE_FILE_NAME,ios::in);
	if (!readFromFile)
	{
		cerr << "File failed to open!";
		exit(EXIT_FAILURE);
	}
	//�Զ����Ƶķ�ʽ�������
	for (int i = 0; i < 3; ++i)
	{
		readFromFile.seekg(i * sizeof(int));
		readFromFile.read(reinterpret_cast<char*>(&highestScores[i]), sizeof(int));
	}
	readFromFile.close();
}

bool ScoreFileRecord::writeHighestScores(int newRecord)
{
	//�ж������Ƿ����
	if (newRecord <= highestScores[2])
		return false;
	//����µļ�¼
	highestScores[2] = newRecord;
	
	//��������
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

	//����д���µ�����
	for (int i = 0; i < 3; ++i)
	{
		writeToFile.seekp(i * sizeof(int));
		writeToFile.write(reinterpret_cast<const char*>(&highestScores[i]), sizeof(int));
	}
	writeToFile.close();

	//д��ɹ�
	return true;
}

const int* ScoreFileRecord::getHighestScores()
{
	//����߷�������
	return highestScores;
}
