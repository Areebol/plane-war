//WindowSetter.h
//log:2022/6/3
//WindowSetter类的定义

#ifndef WINDOWSETTER_H
#define WINDOWSETTER_H

#include"config.h"
#include<stdio.h>
#include<Windows.h>

//窗口绘制类
class WindowSetter
{
public:
	//构造函数
	WindowSetter();

	//绘制屏幕边界
	void paint_edge();

	//更新屏幕数据
	void update();

	//清空屏幕数据
	void clear();
	
	//清空游戏区域数据
	void clear_game();
	
	//清空侧栏区域数据
	void clear_choose();
	
	//在对应位置绘制一个单位数据
	void paint(short x, short y, WORD color, char ch);
	
	//在对应位置绘制一整行数据
	void paintSentence(short x, short y, WORD color, string sentence);
private:
	//判断是否切换缓冲区的标志量
	bool swapFlag;
	//两个可以切换的缓冲区
	HANDLE bufferA;
	HANDLE bufferB;
	//用于调用API函数的参数
	DWORD bytes;
};

#endif
