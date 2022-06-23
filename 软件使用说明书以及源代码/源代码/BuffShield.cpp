//BuffShield.cpp
//log:2022/6/3
//BuffShield���Ա��������

#include "BuffShield.h"

//����Ѫ��
const int shieldBloodMax = 1000;


BuffShield::BuffShield(BossEnemy* boss, MiniEnemy** minis, MaxEnemy** maxs, WindowSetter* window, Plane* plane, int* score, int x, int y)
	:BaseBuff(window, plane, score, x, y), bossEnemy(boss), maxEnemys(maxs), miniEnemys(minis),
	 shieldRec(0, 0, PLANE_REC_WIDTH+2, PLANE_REC_HEIGHT+2),
	shieldBlood(shieldBloodMax)
{
	beUsing = true;
	//�������г�ʼ��
}

void BuffShield::draw()
{
	//����Ϸ������ʾbuffͼ��
	string sentence;
	sentence = "������";
	window->paintSentence(x + 2, y + 1, 0x06, sentence);
	sentence = "�����";
	window->paintSentence(x + 2, y + 2, 0x02, sentence);
	sentence = "������";
	window->paintSentence(x + 2, y + 3, 0x06, sentence);
}

void BuffShield::showInformation()
{
	//����Ϸ������ʾbuff������Ϣ
	string sentence = "ս����û��ܱ���";
	BaseBuff::showInformation(sentence);
}

void BuffShield::use()
{
	//����Ѫ���ľ�
	if (shieldBlood <= 0)
	{
		//������Ϣ
		free = true;
		beUsing = false;
		return;
	}
	//�ƶ����ܾ���
	shieldRec.reset(plane->getX()+1, plane->getY()-1);

	//���»��Ʒɻ�ͼ��
	WORD color = 0x0F;
	string sentence;
	sentence = "��  ";
	window->paintSentence(plane->getX() + 6, plane->getY(), color, sentence);
	sentence = "��  ��";
	window->paintSentence(plane->getX() + 4, plane->getY() + 1, color, sentence);
	sentence = "��";
	window->paintSentence(plane->getX() + 6, plane->getY() + 1, color, sentence);
	sentence = "����  ����";
	window->paintSentence(plane->getX() + 2, plane->getY() + 2, color, sentence);
	sentence = "��";
	window->paintSentence(plane->getX() + 6, plane->getY() + 2, color, sentence);

	//�����ײ
	collision();
}

void BuffShield::collision()
{
	//��⻤�����ӵ�����ײ
	collisionShieldWithEnemyBullet();
}

void BuffShield::collisionShieldWithEnemyBullet()
{
	//�����ӵ������۳�shield��Ѫ��

	//���mini�ɻ��������ӵ�
	for (int i = 0; i < ENEMY_MINI_MAX; ++i)
	{
		this->shieldBlood -= ENEMY_BULLET_A_HURT * miniEnemys[i]->hitObjectA(this->shieldRec);
		this->shieldBlood -= ENEMY_BULLET_B_HURT * miniEnemys[i]->hitObjectB(this->shieldRec);
		this->shieldBlood -= ENEMY_BULLET_C_HURT * miniEnemys[i]->hitObjectC(this->shieldRec);
		this->shieldBlood -= ENEMY_BULLET_D_HURT * miniEnemys[i]->hitObjectD(this->shieldRec);
	}
	//���max�ɻ��������ӵ�
	for (int i = 0; i < ENEMY_MAX_MAX; ++i)
	{
		this->shieldBlood -= ENEMY_BULLET_A_HURT * maxEnemys[i]->hitObjectA(this->shieldRec);
		this->shieldBlood -= ENEMY_BULLET_B_HURT * maxEnemys[i]->hitObjectB(this->shieldRec);
		this->shieldBlood -= ENEMY_BULLET_C_HURT * maxEnemys[i]->hitObjectC(this->shieldRec);
		this->shieldBlood -= ENEMY_BULLET_D_HURT * maxEnemys[i]->hitObjectD(this->shieldRec);
	}
	//���boss�ɻ��������ӵ�
	this->shieldBlood -= ENEMY_BULLET_A_HURT * bossEnemy->hitObjectA(this->shieldRec);
	this->shieldBlood -= ENEMY_BULLET_B_HURT * bossEnemy->hitObjectB(this->shieldRec);
	this->shieldBlood -= ENEMY_BULLET_C_HURT * bossEnemy->hitObjectC(this->shieldRec);
	this->shieldBlood -= ENEMY_BULLET_D_HURT * bossEnemy->hitObjectD(this->shieldRec);
}
