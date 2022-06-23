//BuffBoming.h
//log:2022/6/3
//BuffBoming�ඨ��

#pragma once
#include "BaseBuff.h"

#define BOMING_HURT 50

//ʹ�ö�ս�����к�ը
class BuffBoming :
	public BaseBuff
{
public:
	//���캯��
	BuffBoming(BossEnemy* boss,MiniEnemy** minis,MaxEnemy** maxs,WindowSetter* window = 0,
		Plane* plane = 0, int* score = 0, int x = 0, int y = 0);
	
	//��д����buff����
	virtual void draw()override;

	//��д��ʾbuff���ܺ���
	virtual void showInformation()override;

	//��дʹ��buff���ܺ���
	virtual void use()override;
private:
	//�л���������ʵ��buff����
	MiniEnemy** miniEnemys;
	MaxEnemy** maxEnemys;
	BossEnemy* bossEnemy;
};

