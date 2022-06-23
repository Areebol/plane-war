//MainControl.h
//log:2022/6/3
//MainControl类的定义

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

//游戏的主要控制类
class MainControl
{
public:
	//构造函数
	MainControl(WindowSetter* window);

	//析构函数
	~MainControl();

	//在屏幕绘制按钮的相关函数
	void paint_Button();
	
	//辅助在屏幕绘制按钮的函数
	void paint_Button_Helper();
	
	//在屏幕绘制闪烁按钮的函数
	void paint_Button_Flash();
	
	//在屏幕绘制游戏标题的函数
	void paintTitle();

	//菜单函数
	void menu();

	//刷新菜单屏幕函数
	void updateMenuScreen();

	//初始化函数
	void init();
private:
	//菜单选择enum类
	enum Choices { INFIT, SET, HISTORY,QUIT };
	//存储用户选择
	Choices select;
	//窗口绘制指针
	WindowSetter* window;
	//游戏配置数据类
	GameConfig gameConfig;
	//无尽模式类
	InfiniteGame* infiniteGame;
	//查看历史分数类
	HistoryScoreRecord* scoreRecord;
	//游戏设置类
	GameSet* gameSet;
	//计时器
	Timer timer;
	//战机
	Plane mPlane;
};

#endif

