//BuffShield.cpp
//log:2022/6/3
//BuffShield类成员函数定义

#include "BuffShield.h"

//护盾血量
const int shieldBloodMax = 1000;


BuffShield::BuffShield(BossEnemy* boss, MiniEnemy** minis, MaxEnemy** maxs, WindowSetter* window, Plane* plane, int* score, int x, int y)
	:BaseBuff(window, plane, score, x, y), bossEnemy(boss), maxEnemys(maxs), miniEnemys(minis),
	 shieldRec(0, 0, PLANE_REC_WIDTH+2, PLANE_REC_HEIGHT+2),
	shieldBlood(shieldBloodMax)
{
	beUsing = true;
	//参数进行初始化
}

void BuffShield::draw()
{
	//在游戏区域显示buff图标
	string sentence;
	sentence = "◢■◣";
	window->paintSentence(x + 2, y + 1, 0x06, sentence);
	sentence = "■●■";
	window->paintSentence(x + 2, y + 2, 0x02, sentence);
	sentence = "◥■◤";
	window->paintSentence(x + 2, y + 3, 0x06, sentence);
}

void BuffShield::showInformation()
{
	//在游戏区域显示buff功能信息
	string sentence = "战机获得护盾保护";
	BaseBuff::showInformation(sentence);
}

void BuffShield::use()
{
	//护盾血量耗尽
	if (shieldBlood <= 0)
	{
		//重置信息
		free = true;
		beUsing = false;
		return;
	}
	//移动护盾矩形
	shieldRec.reset(plane->getX()+1, plane->getY()-1);

	//重新绘制飞机图形
	WORD color = 0x0F;
	string sentence;
	sentence = "▲  ";
	window->paintSentence(plane->getX() + 6, plane->getY(), color, sentence);
	sentence = "◢  ◣";
	window->paintSentence(plane->getX() + 4, plane->getY() + 1, color, sentence);
	sentence = "●";
	window->paintSentence(plane->getX() + 6, plane->getY() + 1, color, sentence);
	sentence = "◢◤  ◥◣";
	window->paintSentence(plane->getX() + 2, plane->getY() + 2, color, sentence);
	sentence = "▼";
	window->paintSentence(plane->getX() + 6, plane->getY() + 2, color, sentence);

	//检测碰撞
	collision();
}

void BuffShield::collision()
{
	//检测护盾与子弹的碰撞
	collisionShieldWithEnemyBullet();
}

void BuffShield::collisionShieldWithEnemyBullet()
{
	//根据子弹数量扣除shield的血量

	//检测mini飞机的所有子弹
	for (int i = 0; i < ENEMY_MINI_MAX; ++i)
	{
		this->shieldBlood -= ENEMY_BULLET_A_HURT * miniEnemys[i]->hitObjectA(this->shieldRec);
		this->shieldBlood -= ENEMY_BULLET_B_HURT * miniEnemys[i]->hitObjectB(this->shieldRec);
		this->shieldBlood -= ENEMY_BULLET_C_HURT * miniEnemys[i]->hitObjectC(this->shieldRec);
		this->shieldBlood -= ENEMY_BULLET_D_HURT * miniEnemys[i]->hitObjectD(this->shieldRec);
	}
	//检测max飞机的所有子弹
	for (int i = 0; i < ENEMY_MAX_MAX; ++i)
	{
		this->shieldBlood -= ENEMY_BULLET_A_HURT * maxEnemys[i]->hitObjectA(this->shieldRec);
		this->shieldBlood -= ENEMY_BULLET_B_HURT * maxEnemys[i]->hitObjectB(this->shieldRec);
		this->shieldBlood -= ENEMY_BULLET_C_HURT * maxEnemys[i]->hitObjectC(this->shieldRec);
		this->shieldBlood -= ENEMY_BULLET_D_HURT * maxEnemys[i]->hitObjectD(this->shieldRec);
	}
	//检测boss飞机的所有子弹
	this->shieldBlood -= ENEMY_BULLET_A_HURT * bossEnemy->hitObjectA(this->shieldRec);
	this->shieldBlood -= ENEMY_BULLET_B_HURT * bossEnemy->hitObjectB(this->shieldRec);
	this->shieldBlood -= ENEMY_BULLET_C_HURT * bossEnemy->hitObjectC(this->shieldRec);
	this->shieldBlood -= ENEMY_BULLET_D_HURT * bossEnemy->hitObjectD(this->shieldRec);
}
