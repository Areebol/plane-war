//Plane.cpp
//log:2022/6/3
//Plane类的成员函数的定义

#include "Plane.h"

Plane::Plane(WindowSetter* window,GameConfig* config,int x,int y)
	:window(window),x(x),y(y),bulletTimer(BULLET_INTERVAL),
	bulletSpeedTimer(BULLET_SPEED),config(config),
	bulletHurt(bulletsA[0].hurt)
{
	//对所有子弹初始化
	for (int i = 0; i < PLANE_BULLETSA_MAX; ++i)
		bulletsA[i] = PlaneBulletA(window,x,y);
	//初始化矩形参数
	rec = Rec(x, y, PLANE_REC_WIDTH, PLANE_REC_HEIGHT);
	//设置血量
	blood = PLANE_BLOOD;
	//启动计时器
	bulletTimer.start();
	bulletSpeedTimer.start();
}

void Plane::move(direction d)
{
	//移动飞机
	//建立约束变量
	int edgeX=  GAME_WIDTH - PLANE_REC_WIDTH;
	int edgeY= 3 + WINDOW_HEIGHT - PLANE_REC_HEIGHT;
	//根据移动方向参数进行移动
	switch (d)
	{
	case UP:
		//向上移动
		if (x < 0 || y - 1 < 3 || x > edgeX ||
			y - 1>edgeY)
			;
		else if (y - 2 < 3)
			--y;
		else
			y -= 2;
		break;
	case DOWN:
		//向下移动
		if (x < 0 || y + 1 < 3 || x > edgeX ||
			y + 1>edgeY)
			;
		else if (y + 2 > edgeY)
			++y;
		else
			y += 2;
		break;
	case LEFT:
		//向左移动
		if (x - 1 < 0 || y < 3 || x - 1>edgeX ||
			y > edgeY)
			;
		else if (x - 2 < 0)
			--x;
		else
			x -= 2;
		break;
	case RIGHT:
		//向右移动
		if (x + 1 < 0 || y < 3 || x + 1>edgeX ||
			y > edgeY)
			;
		else if (x + 2 > edgeX)
			++x;
		else
			x += 2;
		break;
	}
	//重新设置矩形位置
	rec.reset(x+2, y);
}

void Plane::moveTo(int x, int y)
{
	//将飞机移动到对应坐标位置
	this->x = x;
	this->y = y;
	//重置矩形信息
	rec.reset(x, y);
}



void Plane::paint()
{
	//绘制我方战机图案
	WORD color = 0x0F;
	string sentence;
	sentence = "▲";
	window->paintSentence(x+6, y, color, sentence);
	sentence = "◢  ◣";
	window->paintSentence(x+4, y+1, 0x04, sentence);
	sentence = "●";
	window->paintSentence(x+6, y + 1, 0x06, sentence);
	sentence = "◢◤  ◥◣";
	window->paintSentence(x+2, y+2, 0x04, sentence);
	sentence = "▼";
	window->paintSentence(x+6, y + 2, 0x0F, sentence);
}



bool Plane::isDead()
{
	//战机血量为空
	return blood <= 0;
}

void Plane::shootBulletA()
{
	//判断射击间隔
	//射击间隔到达
	if (bulletTimer.update())
	{
		//射击子弹1
		for (int i = 0; i < PLANE_BULLETSA_MAX; ++i)
		{
			if (bulletsA[i].isShoot() == false)
			{
				bulletsA[i].reset(x+4, y);
				bulletsA[i].shoot();
				break;
			}
		}
		//射击子弹2
		for (int i = 0; i < PLANE_BULLETSA_MAX; ++i)
		{
			if (bulletsA[i].isShoot() == false)
			{
				bulletsA[i].reset(x +8, y);
				bulletsA[i].shoot();
				break;
			}
		}
	}
}

void Plane::moveBulletA()
{
	//遍历子弹进行移动
	for (int i = 0; i < PLANE_BULLETSA_MAX; ++i)
	{
		if(bulletsA[i].isFree() == false)
		bulletsA[i].move();
	}
}

void Plane::drawBulletA()
{
	//遍历子弹进行绘制
	for (int i = 0; i < PLANE_BULLETSA_MAX; ++i)
	{
		if(bulletsA[i].isFree()==false)
		bulletsA[i].draw(config->getBulletIndex());
	}
}

bool Plane::hitObject(Rec& rhs)
{
	//遍历子弹判断是否与矩形碰撞
	for (int i = 0; i < PLANE_BULLETSA_MAX; ++i)
	{
		if (bulletsA[i].isFree() == false)
		{
			if (bulletsA[i].collision(rhs))
			{
				bulletsA[i].destroy();
				//碰撞 返回真
				return true;
			}
		}
	}
	return false;
}

void Plane::destroyBullet(int index)
{
	if (index >= 0 && index < PLANE_BULLETSA_MAX)
		bulletsA[index].destroy();
}

int Plane::getX()const
{
	return x;
}

int Plane::getY()const
{
	return y;
}

Rec& Plane::getRec()
{
	return this->rec;
}

void Plane::subBlood(int sub)
{
	if (sub > 0)
		blood -= sub;
}

void Plane::addBlood(int add)
{
	if (add > 0)
		blood += add;
}

void Plane::setBlood(int blood)
{
	this->blood = blood;
}

int Plane::getBlood() const
{
	return this->blood;
}
