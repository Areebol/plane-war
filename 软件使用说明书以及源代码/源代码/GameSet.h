//GameSet.h
//log:2022/6/4
//游戏设置类定义

#ifndef GAMESET_H
#define GAMESET_H

#include"config.h"
#include"WindowSetter.h"
#include"GameConfig.h"
#include"Plane.h"
#include<conio.h>
#include<string>

//子弹资源最大值
#define SOURCE_BULLET_MAX 4
//信息输入enum
enum Choices { SETBULLET, SELECTLEVEL, RETURN };
//游戏设置类
class GameSet
{
public:
	//构造函数
	GameSet(WindowSetter* window, GameConfig* config,Plane* plane);

	//绘制按钮函数
	void paint_Button();
	
	//辅助绘制按钮函数
	void paint_Button_Helper();
	
	//绘制闪烁按钮函数
	void paint_Button_Flash();

	//菜单函数
	void menu();
	
	//设置子弹函数
	void setBullet();
	
	//设置游戏难度函数
	void setLevel();

	//绘制设置子弹面板函数
	void paintSetBullet();
	
	//绘制设置难度面板函数
	void paintSetLevel();
	
	//绘制难度选择提示
	void paintLevel();

	//对屏幕数据刷新
	void menuUpdate();

	//设置选择
	void setSelect(Choices select);

	//返回选择
	Choices getSelect()const;
private:
	//保存用户输入信息
	Choices select;
	//绘制窗口指针绘制窗口用
	WindowSetter* window;
	//游戏配置数据类指针
	GameConfig* config;
	//战机指针
	Plane* mPlane;
	//计时器 控制按钮闪烁
	Timer buttonFlashRecorder;
};

#endif

