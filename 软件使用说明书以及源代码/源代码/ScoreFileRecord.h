//ScoreFileRecord.h
//log:2022/6/6
//ScoreFileRecord��Ķ���

#pragma once

#include<iostream>
#include<fstream>

//�����Ϸ��߷������ļ���
#define SCORE_FILE_NAME "PlaneWarScoreRecord.dat"
using std::fstream;
using std::ios;
using std::cerr;
/// <summary>
/// �����ļ��еķ���
/// ����Ϸ����߷ּ�¼
/// ����Ϸ����߷ּ�¼����
/// </summary>
class ScoreFileRecord
{
public:
	//���캯�� �����ļ�
	ScoreFileRecord();

	//��������
	~ScoreFileRecord();

	//���ļ����ݶ�������
	void readHighestScores();

	//��һ���·���д���ļ�
	bool writeHighestScores(int newRecord);

	//������߷���������
	const int* getHighestScores();
private:
	//�������
	int* highestScores;
};

