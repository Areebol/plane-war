//BaseEnemy.h
//log:2022/6/3
//BaseEnemy类的成员函数的定义

#include "BaseEnemy.h"

BaseEnemy::BaseEnemy(WindowSetter* window, GameConfig* config, int x, int y)
	:window(window), x(x), y(y),  config(config),moveRecord(MOVE_INTERVAL),shootRecord(SHOOT_INTERVAL),
	blood(BASE_BLOOD),free(true)
{
	//初始化战机
	init();

	//初始化所有类型子弹
	for (int i = 0; i < BULLETA_MAX; ++i)
	{
		bulletA[i] = EnemyBulletA(window);
	}
	for (int i = 0; i < BULLETB_MAX; ++i)
	{
		bulletB[i] = EnemyBulletB(window);
	}
	for (int i = 0; i < BULLETC_MAX; ++i)
	{
		bulletC[i] = EnemyBulletC(window);
	}
	for (int i = 0; i < BULLETD_MAX; ++i)
	{
		bulletD[i] = EnemyBulletD(window);
	}
}

void BaseEnemy::reset(int x, int y)
{
	//重置位置
	this->x = x;
	this->y = y;
}

void BaseEnemy::subBlood(int sub)
{
	//扣除血量
	if(sub>0)
	blood -= sub;
}

bool BaseEnemy::isDead()const
{
	//血量少于0
	return blood <= 0;
}

void BaseEnemy::destroy()
{
	//闲置状态为真 重置位置
	free = true;
	rec.reset(0, 0);

	//销毁所有子弹
	for (int i = 0; i < BULLETA_MAX; ++i)
	{
		bulletA[i].destroy();
	}
	for (int i = 0; i < BULLETB_MAX; ++i)
	{
		bulletB[i].destroy();
	}
	for (int i = 0; i < BULLETC_MAX; ++i)
	{
		bulletC[i].destroy();
	}
	for (int i = 0; i < BULLETD_MAX; ++i)
	{
		bulletD[i].destroy();
	}
}

void BaseEnemy::init()
{
	//射击计时器开始计时
	shootRecord.start();
	//闲置状态为真
	free = true;
}

void BaseEnemy::moveAllBullet()
{
	//遍历所有处于射击状态的子弹 进行移动
	for (auto it=movingBulletsA.begin();it!=movingBulletsA.end();)
	{
		if ((*it)->isShoot())
		{
			(*it)->move();
			++it;
		}
		else
			it = movingBulletsA.erase(it);
	}
	for (auto it = movingBulletsB.begin(); it != movingBulletsB.end();)
	{
		if ((*it)->isShoot())
		{
			(*it)->move();
			++it;
		}
		else
			it = movingBulletsB.erase(it);
	}
	for (auto it = movingBulletsC.begin(); it != movingBulletsC.end();)
	{
		if ((*it)->isShoot())
		{
			(*it)->move();
			++it;
		}
		else
			it = movingBulletsC.erase(it);
	}
	for (auto it = movingBulletsD.begin(); it != movingBulletsD.end();)
	{
		if ((*it)->isShoot())
		{
			(*it)->move();
			++it;
		}
		else
			it = movingBulletsD.erase(it);
	}
}

void BaseEnemy::drawAllBullet()
{
	//遍历所有处于射击状态的子弹 进行绘制
	for (auto it = movingBulletsA.begin(); it != movingBulletsA.end();++it)
	{
		if ((*it)->isShoot())
		{
			(*it)->draw();
		}
	}
	for (auto it = movingBulletsB.begin(); it != movingBulletsB.end(); ++it)
	{
		if ((*it)->isShoot())
		{
			(*it)->draw();
		}
	}
	for (auto it = movingBulletsC.begin(); it != movingBulletsC.end(); ++it)
	{
		if ((*it)->isShoot())
		{
			(*it)->draw();
		}
	}
	for (auto it = movingBulletsD.begin(); it != movingBulletsD.end(); ++it)
	{
		if ((*it)->isShoot())
		{
			(*it)->draw();
		}
	}
}

void BaseEnemy::controlAllBullet()
{
	//移动子弹
	moveAllBullet();

	//绘制子弹
	drawAllBullet();
}

void BaseEnemy::shootBulletA(int x,int y)
{
	//寻找处于空闲状态的子弹进行射击
	for (int i = 0; i < BULLETA_MAX; ++i)
	{
		//子弹可以射击
		if (bulletA[i].isShoot() == false)
		{
			//将子弹移动到对应位置
			//射击子弹并退出循环
			bulletA[i].reset(x, y);
			bulletA[i].shoot();
			movingBulletsA.push_back(&bulletA[i]);
			break;
		}
	}
}

void BaseEnemy::shootBulletB(int x,int y)
{
	//寻找处于空闲状态的子弹进行射击
	for (int i = 0; i < BULLETB_MAX; ++i)
	{
		//子弹可以射击
		if (bulletB[i].isShoot() == false)
		{
			//将子弹移动到对应位置
			//射击子弹并退出循环
			bulletB[i].reset(x, y);
			bulletB[i].shoot();
			movingBulletsB.push_back(&bulletB[i]);
			break;
		}
	}
}

void BaseEnemy::shootBulletC(int x,int y)
{
	//寻找处于空闲状态的子弹进行射击
	for (int i = 0; i < BULLETC_MAX; ++i)
	{
		//子弹可以射击
		if (bulletC[i].isShoot() == false)
		{
			//将子弹移动到对应位置
			//射击子弹并退出循环
			bulletC[i].reset(x, y);
			bulletC[i].shoot();
			movingBulletsC.push_back(&bulletC[i]);
			break;
		}
	}
}

void BaseEnemy::shootBulletD(int x,int y)
{
	//寻找处于空闲状态的子弹进行射击
	for (int i = 0; i < BULLETD_MAX; ++i)
	{
		//子弹可以射击
		if (bulletD[i].isShoot() == false)
		{
			//将子弹移动到对应位置
			//射击子弹并退出循环
			bulletD[i].reset(x, y);
			bulletD[i].shoot();
			movingBulletsD.push_back(&bulletD[i]);
			break;
		}
	}
}

int BaseEnemy::hitObjectA(Rec& rhs)
{
	//记录命中的子弹数量
	int sign = 0;
	//遍历移动的子弹
	for (auto it=movingBulletsA.begin(); it != movingBulletsA.end();)
	{
		if ((*it)->isFree() == false && (*it)->collision(rhs))
		{
			++sign;
			it = movingBulletsA.erase(it);
		}
		else
			++it;
	}
	return sign;
}

int BaseEnemy::hitObjectB(Rec& rhs)
{
	//操作与hitObjectA类似
	int sign = 0;
	for (auto it = movingBulletsB.begin(); it != movingBulletsB.end();)
	{
		if ((*it)->isFree() == false && (*it)->collision(rhs))
		{
			++sign;
			it = movingBulletsB.erase(it);
		}
		else
			++it;
	}
	return sign;
}

int BaseEnemy::hitObjectC(Rec& rhs)
{
	//操作与hitObjectA类似
	int sign =0;
	for (auto it = movingBulletsC.begin(); it != movingBulletsC.end();)
	{
		if ((*it)->isFree() == false && (*it)->collision(rhs))
		{
			++sign;
			it = movingBulletsC.erase(it);
		}
		else
			++it;
	}
	return sign;
}

int BaseEnemy::hitObjectD(Rec& rhs)
{
	//操作与hitObjectA类似
	int sign = 0;
	for (auto it = movingBulletsD.begin(); it != movingBulletsD.end();)
	{
		if ((*it)->isFree() == false && (*it)->collision(rhs))
		{
			++sign;
			it = movingBulletsD.erase(it);
		}
		else
			++it;
	}
	return sign;
}

Rec& BaseEnemy::getRec()
{
	return this->rec;
}

int BaseEnemy::getX() const
{
	return x;
}

int BaseEnemy::getY() const
{
	return y;
}

double& BaseEnemy::getBlood()
{
	return this->blood;
}

bool BaseEnemy::isFree() const
{
	return free;
}

void BaseEnemy::setFree(bool state)
{
	this->free = state;
}

