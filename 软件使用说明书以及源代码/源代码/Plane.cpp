//Plane.cpp
//log:2022/6/3
//Plane��ĳ�Ա�����Ķ���

#include "Plane.h"

Plane::Plane(WindowSetter* window,GameConfig* config,int x,int y)
	:window(window),x(x),y(y),bulletTimer(BULLET_INTERVAL),
	bulletSpeedTimer(BULLET_SPEED),config(config),
	bulletHurt(bulletsA[0].hurt)
{
	//�������ӵ���ʼ��
	for (int i = 0; i < PLANE_BULLETSA_MAX; ++i)
		bulletsA[i] = PlaneBulletA(window,x,y);
	//��ʼ�����β���
	rec = Rec(x, y, PLANE_REC_WIDTH, PLANE_REC_HEIGHT);
	//����Ѫ��
	blood = PLANE_BLOOD;
	//������ʱ��
	bulletTimer.start();
	bulletSpeedTimer.start();
}

void Plane::move(direction d)
{
	//�ƶ��ɻ�
	//����Լ������
	int edgeX=  GAME_WIDTH - PLANE_REC_WIDTH;
	int edgeY= 3 + WINDOW_HEIGHT - PLANE_REC_HEIGHT;
	//�����ƶ�������������ƶ�
	switch (d)
	{
	case UP:
		//�����ƶ�
		if (x < 0 || y - 1 < 3 || x > edgeX ||
			y - 1>edgeY)
			;
		else if (y - 2 < 3)
			--y;
		else
			y -= 2;
		break;
	case DOWN:
		//�����ƶ�
		if (x < 0 || y + 1 < 3 || x > edgeX ||
			y + 1>edgeY)
			;
		else if (y + 2 > edgeY)
			++y;
		else
			y += 2;
		break;
	case LEFT:
		//�����ƶ�
		if (x - 1 < 0 || y < 3 || x - 1>edgeX ||
			y > edgeY)
			;
		else if (x - 2 < 0)
			--x;
		else
			x -= 2;
		break;
	case RIGHT:
		//�����ƶ�
		if (x + 1 < 0 || y < 3 || x + 1>edgeX ||
			y > edgeY)
			;
		else if (x + 2 > edgeX)
			++x;
		else
			x += 2;
		break;
	}
	//�������þ���λ��
	rec.reset(x+2, y);
}

void Plane::moveTo(int x, int y)
{
	//���ɻ��ƶ�����Ӧ����λ��
	this->x = x;
	this->y = y;
	//���þ�����Ϣ
	rec.reset(x, y);
}



void Plane::paint()
{
	//�����ҷ�ս��ͼ��
	WORD color = 0x0F;
	string sentence;
	sentence = "��";
	window->paintSentence(x+6, y, color, sentence);
	sentence = "��  ��";
	window->paintSentence(x+4, y+1, 0x04, sentence);
	sentence = "��";
	window->paintSentence(x+6, y + 1, 0x06, sentence);
	sentence = "����  ����";
	window->paintSentence(x+2, y+2, 0x04, sentence);
	sentence = "��";
	window->paintSentence(x+6, y + 2, 0x0F, sentence);
}



bool Plane::isDead()
{
	//ս��Ѫ��Ϊ��
	return blood <= 0;
}

void Plane::shootBulletA()
{
	//�ж�������
	//����������
	if (bulletTimer.update())
	{
		//����ӵ�1
		for (int i = 0; i < PLANE_BULLETSA_MAX; ++i)
		{
			if (bulletsA[i].isShoot() == false)
			{
				bulletsA[i].reset(x+4, y);
				bulletsA[i].shoot();
				break;
			}
		}
		//����ӵ�2
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
	//�����ӵ������ƶ�
	for (int i = 0; i < PLANE_BULLETSA_MAX; ++i)
	{
		if(bulletsA[i].isFree() == false)
		bulletsA[i].move();
	}
}

void Plane::drawBulletA()
{
	//�����ӵ����л���
	for (int i = 0; i < PLANE_BULLETSA_MAX; ++i)
	{
		if(bulletsA[i].isFree()==false)
		bulletsA[i].draw(config->getBulletIndex());
	}
}

bool Plane::hitObject(Rec& rhs)
{
	//�����ӵ��ж��Ƿ��������ײ
	for (int i = 0; i < PLANE_BULLETSA_MAX; ++i)
	{
		if (bulletsA[i].isFree() == false)
		{
			if (bulletsA[i].collision(rhs))
			{
				bulletsA[i].destroy();
				//��ײ ������
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
