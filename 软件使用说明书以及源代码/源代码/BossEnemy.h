//BaseEnemy.h
//log:2022/6/3
//BaseEnemy��Ķ���

#pragma once
#include "BaseEnemy.h"

//boss�ľ�����Ϣ
#define BOSS_WIDTH 38
#define BOSS_HEIGHT 10
//boss��Ѫ����Ϣ
#define BOSS_BLOOD 36*ENEMY_BLOOD_RATIO

//��ʱ���Ĳ���
#define BOSS_RECORDI 500
#define BOSS_RECORDII 5000
#define BOSS_RECORDIII 7000

//boss����ս��
class BossEnemy :
    public BaseEnemy//�̳л���ս��
{
public:
    //���캯��
    BossEnemy(WindowSetter* window = 0, GameConfig* config = 0, int x = 0, int y = 0);

    //��д�ƶ�ս������
    virtual void move()override;

    //��д����ս������
    virtual void draw()override;

    //��д�������
    virtual void shoot()override;

    //��ʼ������
    void init();

    //���ٺ���
    void destory();

private:
    //��������ս������
    void drawHelper();
    //�����ӵ��������ʱ��
    Timer shootRecordI;
    Timer shootRecordII;
    Timer shootRecordIII;
};

