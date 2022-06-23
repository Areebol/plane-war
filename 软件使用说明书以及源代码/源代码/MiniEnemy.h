//MiniEnemy.h
//log:2022/6/3
//MiniEnemy�Ķ���

#pragma once
#include "BaseEnemy.h"

//mini�ľ�����Ϣ
#define MINI_WIDTH 10
#define MINI_HEIGHT 3
//mini��Ѫ����Ϣ
#define MINI_BLOOD 8*ENEMY_BLOOD_RATIO
//״̬�ļ�ʱ��
#define MINI_RECORDI 5000

//mini����ս��
class MiniEnemy :
    public BaseEnemy//�̳л���ս��
{
public:
    //���캯��
    MiniEnemy(WindowSetter* window=0, GameConfig* config=0, int x = 0, int y = 0);

    //��д�ƶ�����
    virtual void move()override;

    //��д���ƺ���
    virtual void draw()override;

    //��д�������
    virtual void shoot()override;

    //���ٺ���
    void destroy();

    //��ʼ������
    void init();
private:
    //���״̬�ļ�ʱ��
    Timer shootRecordI;
};

