//BaseBuff.h
//log:2022/6/3
//����BaseBuff����

#ifndef BASEBUFF_H
#define BASEBUFF_H

#include"Rec.h"
#include"config.h"
#include"WindowSetter.h"
#include"Plane.h"
#include"Timer.h"
#include"BossEnemy.h"
#include"MaxEnemy.h"
#include"MiniEnemy.h"
#include<time.h>
#include<random>

//�л�����������궨��
#define ENEMY_MAX_MAX 4
#define ENEMY_MINI_MAX 6

class BuffAntidote;
class BuffAward;
class BuffBoming;
class BuffInvisible;
class BuffShield;
class BaseBuff
{
	friend class BuffAntidote;
	friend class BuffAward;
	friend class BuffBoming;
	friend class BuffInvisible;
	friend class BuffShield;
public:
	//���캯��
	BaseBuff(WindowSetter* window=0,Plane*plane=0,int* score=0,int x=0,int y=0);

	//����buff����
	virtual void draw()=0;

	//��ʾbuff���ܺ���
	virtual void showInformation()=0;

	//ʹ��buff���ܺ���
	virtual void use()=0;

	//�ƶ�buff����
	void move();

	//������ʾbuff���ܺ���
	void showInformation(string& sentence)const;

	//����buff���꺯��
	void setPosition(int x, int y);

	//��������״̬
	bool& Free();
private:
	//����ָ�������
	WindowSetter* window;
	//�����Ϸ�ɻ�ʵ�ֹ���
	Plane* plane;
	//�ƶ���ʱ��
	Timer record;
	//��ŷ���ʵ�ֹ���
	int* score;
	//������Ϣ
	int x;
	int y;
	//������Ϣ
	int width;
	int height;
	//������Ϣ
	bool free;
public:
	//����������ײ
	Rec rec;
	//�Ƿ��������
	bool beUsing;
};

#endif
