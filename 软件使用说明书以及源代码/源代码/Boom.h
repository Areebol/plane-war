//Boom.h
//log:2022/6/3
//Boom�Ķ���

#ifndef BOOM_H
#define BOOM_H

#include"Timer.h"
#include"config.h"
#include"Rec.h"
#include"WindowSetter.h"

//��ըЧ����
class Boom
{
public:
	//���캯��
	Boom(WindowSetter* window, int x = 0, int y = 0);

	//���Ʊ�ըЧ������
	void paint();
	
	//�������ñ�ըЧ��
	void reset();
	
	//������������λ�ú���
	void resetPosition(int newX, int newY);

	//�����Ƿ����
	bool isFree()const;

	//�����Ƿ����
	void setFree(bool state);
private:
	//����״̬����
	bool free;
	//����λ��
	int x;
	int y;
	//������ָ��
	WindowSetter* window;
	//��¼ʱ��
	int record;
};
#endif

