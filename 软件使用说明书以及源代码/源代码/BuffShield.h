//BuffShiled.h
//log:2022/6/3
//BuffShield��Ķ���

#pragma once
#include "BaseBuff.h"

//Ϊս�����ӻ���Ч��
class BuffShield :
	public BaseBuff
{
public:
	//���캯��
	BuffShield(BossEnemy* boss, MiniEnemy** minis, MaxEnemy** maxs, WindowSetter* window = 0,
		Plane* plane = 0, int* score = 0, int x = 0, int y = 0);

	//��д����buff����
	virtual void draw()override;

	//��д��ʾbuff���ܺ���
	virtual void showInformation()override;

	//��дʹ��buff���ܺ���
	virtual void use()override;
	
	//��⻤�ܵ���ײ
	void collision();

	//��⻤�����ӵ���ײ
	void collisionShieldWithEnemyBullet();


public:
	//���ܵ�λ����Ϣ
	Rec shieldRec;
	int shieldBlood;
private:
	//�л�����
	MiniEnemy** miniEnemys;
	MaxEnemy** maxEnemys;
	BossEnemy* bossEnemy;
};

