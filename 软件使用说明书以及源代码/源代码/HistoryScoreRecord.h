//HistroyScoreRecord.h
//log:2022/6/7
//HitsotyScoreRecord��Ķ���

#include"WindowSetter.h"
#include"ScoreFileRecord.h"
#include<conio.h>

#pragma once

/// <summary>
/// ��ʾ��ʷ��߷�������
/// </summary>
class HistoryScoreRecord
{
public:
	//���캯��
	HistoryScoreRecord(WindowSetter* window,ScoreFileRecord* record);

	//��ʾ��ʷ��߷�����¼
	void showHighestScore();

private:
	//ˢ����Ļ����
	void updateScreen();

	//��ʾ��߷���
	void showScore();

	//��ʾ��ʾ��Ϣ
	void showHelping();

	//��ȡ�������ض�ȡ��Ϣ
	int getKeyHit();

private:
	//���ڻ��ƴ���
	WindowSetter* window;
	//���ڻ�ȡ�ļ�����
	ScoreFileRecord* scoreFileRecord;
};

