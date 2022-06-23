//MainControl.h
//log:2022/6/3
//MainControl��Ķ���

#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include"config.h"
#include"WindowSetter.h"
#include"InfiniteGame.h"
#include"HistoryScoreRecord.h"
#include"Timer.h"
#include"Plane.h"
#include"GameSet.h"
#include"GameConfig.h"
#include<conio.h>
#include<string>
using std::string;

//��Ϸ����Ҫ������
class MainControl
{
public:
	//���캯��
	MainControl(WindowSetter* window);

	//��������
	~MainControl();

	//����Ļ���ư�ť����غ���
	void paint_Button();
	
	//��������Ļ���ư�ť�ĺ���
	void paint_Button_Helper();
	
	//����Ļ������˸��ť�ĺ���
	void paint_Button_Flash();
	
	//����Ļ������Ϸ����ĺ���
	void paintTitle();

	//�˵�����
	void menu();

	//ˢ�²˵���Ļ����
	void updateMenuScreen();

	//��ʼ������
	void init();
private:
	//�˵�ѡ��enum��
	enum Choices { INFIT, SET, HISTORY,QUIT };
	//�洢�û�ѡ��
	Choices select;
	//���ڻ���ָ��
	WindowSetter* window;
	//��Ϸ����������
	GameConfig gameConfig;
	//�޾�ģʽ��
	InfiniteGame* infiniteGame;
	//�鿴��ʷ������
	HistoryScoreRecord* scoreRecord;
	//��Ϸ������
	GameSet* gameSet;
	//��ʱ��
	Timer timer;
	//ս��
	Plane mPlane;
};

#endif

