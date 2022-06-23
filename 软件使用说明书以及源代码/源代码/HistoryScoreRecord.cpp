//HistoryScoreRecord.cpp
//log:2022/6/7
//HistroyScoreRecord��ĳ�Ա�����Ķ���

#include "HistoryScoreRecord.h"

using std::to_string;
HistoryScoreRecord::HistoryScoreRecord(WindowSetter* window,ScoreFileRecord* record)
	:window(window),scoreFileRecord(record)
{

}

void HistoryScoreRecord::showHighestScore()
{
	//��ʾ��ʷ��������
	updateScreen();

	//��ȡ���뷵��
	while(getKeyHit()!=27)
	{
		return;
	}
}

void HistoryScoreRecord::updateScreen()
{
	//�����Ļ
	window->clear_choose();
	window->clear_game();

	//��ʾ����
	showScore();

	//��ʾ������Ϣ
	showHelping();

	window->update();
}

void HistoryScoreRecord::showScore()
{
	//��ȡ��߷���
	const int* recordPtr = scoreFileRecord->getHighestScores();
	window->paint_edge();

	//������߷�����Ϣ
	string sentence = "��ʷ��߷���";
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
	//������ʾ��Ϣ
	string sentence = "�����������......";
	window->paintSentence(24, 30, 0x02, sentence);
}

int HistoryScoreRecord::getKeyHit()
{
	//��������
	return _getch();
}
