//BaseEnemy.h
//log:2022/6/3
//BaseEnemy��ĳ�Ա�����Ķ���

#include "BaseEnemy.h"

BaseEnemy::BaseEnemy(WindowSetter* window, GameConfig* config, int x, int y)
	:window(window), x(x), y(y),  config(config),moveRecord(MOVE_INTERVAL),shootRecord(SHOOT_INTERVAL),
	blood(BASE_BLOOD),free(true)
{
	//��ʼ��ս��
	init();

	//��ʼ�����������ӵ�
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
	//����λ��
	this->x = x;
	this->y = y;
}

void BaseEnemy::subBlood(int sub)
{
	//�۳�Ѫ��
	if(sub>0)
	blood -= sub;
}

bool BaseEnemy::isDead()const
{
	//Ѫ������0
	return blood <= 0;
}

void BaseEnemy::destroy()
{
	//����״̬Ϊ�� ����λ��
	free = true;
	rec.reset(0, 0);

	//���������ӵ�
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
	//�����ʱ����ʼ��ʱ
	shootRecord.start();
	//����״̬Ϊ��
	free = true;
}

void BaseEnemy::moveAllBullet()
{
	//�������д������״̬���ӵ� �����ƶ�
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
	//�������д������״̬���ӵ� ���л���
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
	//�ƶ��ӵ�
	moveAllBullet();

	//�����ӵ�
	drawAllBullet();
}

void BaseEnemy::shootBulletA(int x,int y)
{
	//Ѱ�Ҵ��ڿ���״̬���ӵ��������
	for (int i = 0; i < BULLETA_MAX; ++i)
	{
		//�ӵ��������
		if (bulletA[i].isShoot() == false)
		{
			//���ӵ��ƶ�����Ӧλ��
			//����ӵ����˳�ѭ��
			bulletA[i].reset(x, y);
			bulletA[i].shoot();
			movingBulletsA.push_back(&bulletA[i]);
			break;
		}
	}
}

void BaseEnemy::shootBulletB(int x,int y)
{
	//Ѱ�Ҵ��ڿ���״̬���ӵ��������
	for (int i = 0; i < BULLETB_MAX; ++i)
	{
		//�ӵ��������
		if (bulletB[i].isShoot() == false)
		{
			//���ӵ��ƶ�����Ӧλ��
			//����ӵ����˳�ѭ��
			bulletB[i].reset(x, y);
			bulletB[i].shoot();
			movingBulletsB.push_back(&bulletB[i]);
			break;
		}
	}
}

void BaseEnemy::shootBulletC(int x,int y)
{
	//Ѱ�Ҵ��ڿ���״̬���ӵ��������
	for (int i = 0; i < BULLETC_MAX; ++i)
	{
		//�ӵ��������
		if (bulletC[i].isShoot() == false)
		{
			//���ӵ��ƶ�����Ӧλ��
			//����ӵ����˳�ѭ��
			bulletC[i].reset(x, y);
			bulletC[i].shoot();
			movingBulletsC.push_back(&bulletC[i]);
			break;
		}
	}
}

void BaseEnemy::shootBulletD(int x,int y)
{
	//Ѱ�Ҵ��ڿ���״̬���ӵ��������
	for (int i = 0; i < BULLETD_MAX; ++i)
	{
		//�ӵ��������
		if (bulletD[i].isShoot() == false)
		{
			//���ӵ��ƶ�����Ӧλ��
			//����ӵ����˳�ѭ��
			bulletD[i].reset(x, y);
			bulletD[i].shoot();
			movingBulletsD.push_back(&bulletD[i]);
			break;
		}
	}
}

int BaseEnemy::hitObjectA(Rec& rhs)
{
	//��¼���е��ӵ�����
	int sign = 0;
	//�����ƶ����ӵ�
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
	//������hitObjectA����
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
	//������hitObjectA����
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
	//������hitObjectA����
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

