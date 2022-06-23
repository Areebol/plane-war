//WindowSetter.cpp

#include "WindowSetter.h"
WindowSetter::WindowSetter()
{
	swapFlag = true;//ѡ����������建�����ı�־Ϊtrue
	bytes = 0;//���ڵ��û����������Ĳ���

	//���ô��ڵĴ�С
	char chCmd[32];
	sprintf_s(chCmd, "mode con cols=%d lines=%d", WINDOW_ALL_WIDTH, WINDOW_ALL_HEIGHT);
	system(chCmd);
	//���û�������Ϣ
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	HWND hWnd = GetConsoleWindow(); //��ȡ���ھ��
	LONG_PTR sty = GetWindowLongPtrA(hWnd, GWL_STYLE); //��ȡ������ʽ
	sty = sty & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX;
	
	SetWindowLongPtrA(hWnd, GWL_STYLE, sty); //���ô��岻�ɸ��Ĵ�С,�������
	bufferA = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);//�Ի�����A�ĳ�ʼ��
	bufferB = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);//�Ի�����B�ĳ�ʼ��

	//�رջ�����AB�Ĺ��
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(bufferA, &cci);
	SetConsoleCursorInfo(bufferB, &cci);
}

void WindowSetter::paint_edge()
{
	WORD regularColor = COLOR_REGULAR;//�ı�����ɫ
	WORD color1 = 0x33;//��ɫ
	for (int i = 0; i < GAME_WIDTH; ++i)//���Ƶ�ͼ������ɫ��
	{
		paint(i + 2, 1, color1, ' ');
		paint(i + 2, WINDOW_ALL_HEIGHT - 2, color1, ' ');
	}
	for (int i = 0; i < CHOOSE_WIDTH; ++i)//������ʾ��������ɫ��
	{
		paint(i + 4 + GAME_WIDTH, 1, color1, ' ');
		paint(i + 4 + GAME_WIDTH, WINDOW_ALL_HEIGHT - 2, color1, ' ');
	}
	for (int i = 0; i < WINDOW_ALL_WIDTH; ++i)//���Ʊ߽����µĿ�
	{
		paint(i, 0, regularColor, 'H');
		paint(i, 2, regularColor, 'H');
		paint(i, WINDOW_ALL_HEIGHT - 3, regularColor, 'H');
		paint(i, WINDOW_ALL_HEIGHT - 1, regularColor, 'H');
	}
	for (int i = 0; i < WINDOW_ALL_WIDTH; ++i)//���Ʊ߽����ҵĸ�
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
	//�л���־Ϊ�ٵ�ʱ�� ��ʱ���������ΪA
	//Ӧ���л�������B
	if (swapFlag == false)
	{
		swapFlag = true; // ���±�־
		SetConsoleActiveScreenBuffer(bufferB);//���Ļ������
	}
	//�л���־Ϊ�ٵ�ʱ�� ��ʱ���������ΪB
	//Ӧ���л�������A
	else
	{
		swapFlag = false; // ���±�־
		SetConsoleActiveScreenBuffer(bufferA);//���Ļ������
	}
}

void WindowSetter::clear()
{
	//���ڴ������̨��������Ϣ
	//��������Ҫ��ȡ����̨��������С
	CONSOLE_SCREEN_BUFFER_INFO cinfo;
	DWORD recnum;
	COORD coord = { 0,0 };
	//�л���־Ϊ�� ���������ΪA
	//д�뻺����B
	if (swapFlag == false)
	{
		GetConsoleScreenBufferInfo(bufferB, &cinfo);
		FillConsoleOutputCharacterW(bufferB, L' ', cinfo.dwSize.X * cinfo.dwSize.Y, coord, & recnum);
		FillConsoleOutputAttribute(bufferB, 0, cinfo.dwSize.X * cinfo.dwSize.Y, coord, & recnum);
	}
	//�л���־Ϊ���ʱ�� ��ʱ���������ΪbufferB
	//д�����Ӧ�öԻ�����bufferA
	else
	{
		GetConsoleScreenBufferInfo(bufferA, &cinfo);
		FillConsoleOutputCharacterW(bufferA, L' ', cinfo.dwSize.X * cinfo.dwSize.Y, coord, & recnum);
		FillConsoleOutputAttribute(bufferA, 0, cinfo.dwSize.X * cinfo.dwSize.Y, coord, & recnum);
	}
}

void WindowSetter::clear_game()
{
	//�����Ϸ���������
	string sentence = "                                                             ";
	sentence.resize(GAME_WIDTH);
	//��ʼ��յĺ�����λ��
	int x=2;
	for (int y = 3; y < WINDOW_ALL_HEIGHT-3; ++y)
		paintSentence(x, y, COLOR_REGULAR, sentence);
}

void WindowSetter::clear_choose()
{
	//���ѡ�����������
	string sentence = "                                                             ";
	sentence.resize(CHOOSE_WIDTH);
	//��ʼ��յĺ�����λ��
	int x = GAME_WIDTH+4;
	for (int y = 3; y < WINDOW_ALL_HEIGHT - 3; ++y)
		paintSentence(x, y, COLOR_REGULAR, sentence);
}

void WindowSetter::paint(short x, short y, WORD color, char character)
{
	if (x < 0 || x >= WINDOW_ALL_WIDTH || y < 0 || y >= WINDOW_ALL_HEIGHT)//���ݳ������� ���Ե�ԭ�����кܶ���������
		return;
	COORD coord = { x,y };
	char ch[1] = { character };
	//�л���־Ϊ�ٵ�ʱ�� ��ʱ���������ΪA
	//д�����Ӧ�öԻ�����B
	if (swapFlag == false)
	{
		WriteConsoleOutputAttribute(bufferB, &color, 1, coord, &bytes);//д�뵽Ļ�󻺳���
		WriteConsoleOutputCharacterA(bufferB, ch, 1, coord, &bytes);
	}
	//�л���־Ϊ�ٵ�ʱ�� ��ʱ���������ΪbufferB
	//д�����Ӧ�öԻ�����bufferA
	else
	{
		WriteConsoleOutputAttribute(bufferA, &color, 1, coord, &bytes);//д�뵽Ļ�󻺳���
		WriteConsoleOutputCharacterA(bufferA, ch, 1, coord, &bytes);
	}
}

void WindowSetter::paintSentence(short x, short y, WORD color, string sentence)
{
	if (y >= WINDOW_ALL_HEIGHT - 3||y<3)
		return;
	//����д�������λ��
	COORD coord = { x,y };
	char charSentence[GAME_WIDTH] = { '\0' };
	//����д��Ŀ��
	int width = (int)sentence.size();
	for (int i = 0; i < width; ++i)
		charSentence[i] = sentence[i];
	//�л���־Ϊ�ٵ�ʱ�� ��ʱ���������ΪA
	//д�����Ӧ�öԻ�����B
	if (swapFlag == false)
	{
		WriteConsoleOutputCharacterA(bufferB, charSentence, width, coord, &bytes);
		for (int i = 0; i < width; ++i)
		{
			WriteConsoleOutputAttribute(bufferB, &color, 1, coord, &bytes);//д�뵽Ļ�󻺳���
			++coord.X;
		}
	}
	//�л���־Ϊ�ٵ�ʱ�� ��ʱ���������ΪbufferB
	//д�����Ӧ�öԻ�����bufferA
	else
	{
		WriteConsoleOutputCharacterA(bufferA, charSentence, width, coord, &bytes);
		for (int i = 0; i < width; ++i)
		{
			WriteConsoleOutputAttribute(bufferA, &color, 1, coord, &bytes);//д�뵽Ļ�󻺳���
			++coord.X;
		}
	}
}

