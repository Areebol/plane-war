//MiniEnemy.cpp
//log:2022/6/3
//MiniEnemy类的成员函数的定义

#include "MiniEnemy.h"

MiniEnemy::MiniEnemy(WindowSetter* window, GameConfig* config, int x, int y)
	:BaseEnemy::BaseEnemy(window,config,x,y),
	shootRecordI(MINI_RECORDI)
{
	//参数初始化
	blood = MINI_BLOOD;
	rec = Rec(this->x, this->y, MINI_WIDTH, MINI_HEIGHT);
}

void MiniEnemy::move()
{
	//战机符合移动状态
	if (free == false && moveRecord.update())
	{
		//向下移动
		this->y += 1;
	}
	//刷新矩形信息
	rec.reset(x, y);
	//越界销毁
	if (y > WINDOW_ALL_HEIGHT)
		free = true;
}

void MiniEnemy::draw()
{
	//绘制战机形状
	string sentence;
	sentence = "◣◢  ◣◢";
	window->paintSentence(x, y + 1, 0x06, sentence);
	sentence = "◥■■■◤";
	window->paintSentence(x, y + 2, 0x04, sentence);
	sentence = "◥◤";
	window->paintSentence(x+3, y + 3, 0x0F, sentence);

	//绘制血条
	string bloodS;
	//计算血条绘制长度
	for (int i = 0; i < blood/ENEMY_BLOOD_RATIO; ++i)
	{
		bloodS += "-";
	}
	window->paintSentence(x + 1, y - 1, 0x0F, bloodS);
}

void MiniEnemy::shoot()
{
	//射击状态1刷新
	if (shootRecordI.update())
	{
		//射击
		for(int i=0;i<4;++i)
		shootBulletA(this->x + 4, this->y+i-1);
	}
}

void MiniEnemy::destroy()
{
	//调用基类销毁函数
	BaseEnemy::destroy();
	//重置血量
	blood = MINI_BLOOD;
}

void MiniEnemy::init()
{
	//调用基类初始化函数
	BaseEnemy::init();
	//启动计时器
	shootRecordI.start();
	//重置血量
	blood = MINI_BLOOD;
}
