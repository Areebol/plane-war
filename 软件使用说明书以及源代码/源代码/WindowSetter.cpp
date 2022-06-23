//WindowSetter.cpp

#include "WindowSetter.h"
WindowSetter::WindowSetter()
{
	swapFlag = true;//选择输出到具体缓冲区的标志为true
	bytes = 0;//用于调用缓冲区函数的参数

	//设置窗口的大小
	char chCmd[32];
	sprintf_s(chCmd, "mode con cols=%d lines=%d", WINDOW_ALL_WIDTH, WINDOW_ALL_HEIGHT);
	system(chCmd);
	//设置缓冲区信息
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	HWND hWnd = GetConsoleWindow(); //获取窗口句柄
	LONG_PTR sty = GetWindowLongPtrA(hWnd, GWL_STYLE); //获取窗口样式
	sty = sty & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX;
	
	SetWindowLongPtrA(hWnd, GWL_STYLE, sty); //设置窗体不可更改大小,不可最大化
	bufferA = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);//对缓冲区A的初始化
	bufferB = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);//对缓冲区B的初始化

	//关闭缓冲区AB的光标
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(bufferA, &cci);
	SetConsoleCursorInfo(bufferB, &cci);
}

void WindowSetter::paint_edge()
{
	WORD regularColor = COLOR_REGULAR;//文本的颜色
	WORD color1 = 0x33;//绿色
	for (int i = 0; i < GAME_WIDTH; ++i)//绘制地图上下颜色条
	{
		paint(i + 2, 1, color1, ' ');
		paint(i + 2, WINDOW_ALL_HEIGHT - 2, color1, ' ');
	}
	for (int i = 0; i < CHOOSE_WIDTH; ++i)//绘制提示栏上下颜色条
	{
		paint(i + 4 + GAME_WIDTH, 1, color1, ' ');
		paint(i + 4 + GAME_WIDTH, WINDOW_ALL_HEIGHT - 2, color1, ' ');
	}
	for (int i = 0; i < WINDOW_ALL_WIDTH; ++i)//绘制边界上下的宽
	{
		paint(i, 0, regularColor, 'H');
		paint(i, 2, regularColor, 'H');
		paint(i, WINDOW_ALL_HEIGHT - 3, regularColor, 'H');
		paint(i, WINDOW_ALL_HEIGHT - 1, regularColor, 'H');
	}
	for (int i = 0; i < WINDOW_ALL_WIDTH; ++i)//绘制边界左右的高
	{
		paint(0, i, regularColor, 'H');
		paint(1, i, regularColor, 'H');
		paint(2 + GAME_WIDTH, i, regularColor, 'H');
		paint(3 + GAME_WIDTH, i, regularColor, 'H');
		paint(WINDOW_ALL_WIDTH - 1, i, regularColor, 'H');
		paint(WINDOW_ALL_WIDTH - 2, i, regularColor, 'H');
	}
}

void WindowSetter::update()
{
	//切换标志为假的时候 此时输出缓冲区为A
	//应该切换缓冲区B
	if (swapFlag == false)
	{
		swapFlag = true; // 更新标志
		SetConsoleActiveScreenBuffer(bufferB);//更改活动缓冲区
	}
	//切换标志为假的时候 此时输出缓冲区为B
	//应该切换缓冲区A
	else
	{
		swapFlag = false; // 更新标志
		SetConsoleActiveScreenBuffer(bufferA);//更改活动缓冲区
	}
}

void WindowSetter::clear()
{
	//用于储存控制台缓冲区信息
	//在这里主要获取控制台缓冲区大小
	CONSOLE_SCREEN_BUFFER_INFO cinfo;
	DWORD recnum;
	COORD coord = { 0,0 };
	//切换标志为假 输出缓冲区为A
	//写入缓冲区B
	if (swapFlag == false)
	{
		GetConsoleScreenBufferInfo(bufferB, &cinfo);
		FillConsoleOutputCharacterW(bufferB, L' ', cinfo.dwSize.X * cinfo.dwSize.Y, coord, & recnum);
		FillConsoleOutputAttribute(bufferB, 0, cinfo.dwSize.X * cinfo.dwSize.Y, coord, & recnum);
	}
	//切换标志为真的时候 此时输出缓冲区为bufferB
	//写入操作应该对缓冲区bufferA
	else
	{
		GetConsoleScreenBufferInfo(bufferA, &cinfo);
		FillConsoleOutputCharacterW(bufferA, L' ', cinfo.dwSize.X * cinfo.dwSize.Y, coord, & recnum);
		FillConsoleOutputAttribute(bufferA, 0, cinfo.dwSize.X * cinfo.dwSize.Y, coord, & recnum);
	}
}

void WindowSetter::clear_game()
{
	//清空游戏区域的内容
	string sentence = "                                                             ";
	sentence.resize(GAME_WIDTH);
	//开始清空的横坐标位置
	int x=2;
	for (int y = 3; y < WINDOW_ALL_HEIGHT-3; ++y)
		paintSentence(x, y, COLOR_REGULAR, sentence);
}

void WindowSetter::clear_choose()
{
	//清空选择区域的内容
	string sentence = "                                                             ";
	sentence.resize(CHOOSE_WIDTH);
	//开始清空的横坐标位置
	int x = GAME_WIDTH+4;
	for (int y = 3; y < WINDOW_ALL_HEIGHT - 3; ++y)
		paintSentence(x, y, COLOR_REGULAR, sentence);
}

void WindowSetter::paint(short x, short y, WORD color, char character)
{
	if (x < 0 || x >= WINDOW_ALL_WIDTH || y < 0 || y >= WINDOW_ALL_HEIGHT)//数据超出界面 忽略的原因是有很多操作会溢出
		return;
	COORD coord = { x,y };
	char ch[1] = { character };
	//切换标志为假的时候 此时输出缓冲区为A
	//写入操作应该对缓冲区B
	if (swapFlag == false)
	{
		WriteConsoleOutputAttribute(bufferB, &color, 1, coord, &bytes);//写入到幕后缓冲区
		WriteConsoleOutputCharacterA(bufferB, ch, 1, coord, &bytes);
	}
	//切换标志为假的时候 此时输出缓冲区为bufferB
	//写入操作应该对缓冲区bufferA
	else
	{
		WriteConsoleOutputAttribute(bufferA, &color, 1, coord, &bytes);//写入到幕后缓冲区
		WriteConsoleOutputCharacterA(bufferA, ch, 1, coord, &bytes);
	}
}

void WindowSetter::paintSentence(short x, short y, WORD color, string sentence)
{
	if (y >= WINDOW_ALL_HEIGHT - 3||y<3)
		return;
	//设置写入的坐标位置
	COORD coord = { x,y };
	char charSentence[GAME_WIDTH] = { '\0' };
	//设置写入的宽度
	int width = (int)sentence.size();
	for (int i = 0; i < width; ++i)
		charSentence[i] = sentence[i];
	//切换标志为假的时候 此时输出缓冲区为A
	//写入操作应该对缓冲区B
	if (swapFlag == false)
	{
		WriteConsoleOutputCharacterA(bufferB, charSentence, width, coord, &bytes);
		for (int i = 0; i < width; ++i)
		{
			WriteConsoleOutputAttribute(bufferB, &color, 1, coord, &bytes);//写入到幕后缓冲区
			++coord.X;
		}
	}
	//切换标志为假的时候 此时输出缓冲区为bufferB
	//写入操作应该对缓冲区bufferA
	else
	{
		WriteConsoleOutputCharacterA(bufferA, charSentence, width, coord, &bytes);
		for (int i = 0; i < width; ++i)
		{
			WriteConsoleOutputAttribute(bufferA, &color, 1, coord, &bytes);//写入到幕后缓冲区
			++coord.X;
		}
	}
}

