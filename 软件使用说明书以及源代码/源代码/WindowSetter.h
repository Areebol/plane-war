//WindowSetter.h
//log:2022/6/3
//WindowSetter��Ķ���

#ifndef WINDOWSETTER_H
#define WINDOWSETTER_H

#include"config.h"
#include<stdio.h>
#include<Windows.h>

//���ڻ�����
class WindowSetter
{
public:
	//���캯��
	WindowSetter();

	//������Ļ�߽�
	void paint_edge();

	//������Ļ����
	void update();

	//�����Ļ����
	void clear();
	
	//�����Ϸ��������
	void clear_game();
	
	//��ղ�����������
	void clear_choose();
	
	//�ڶ�Ӧλ�û���һ����λ����
	void paint(short x, short y, WORD color, char ch);
	
	//�ڶ�Ӧλ�û���һ��������
	void paintSentence(short x, short y, WORD color, string sentence);
private:
	//�ж��Ƿ��л��������ı�־��
	bool swapFlag;
	//���������л��Ļ�����
	HANDLE bufferA;
	HANDLE bufferB;
	//���ڵ���API�����Ĳ���
	DWORD bytes;
};

#endif
