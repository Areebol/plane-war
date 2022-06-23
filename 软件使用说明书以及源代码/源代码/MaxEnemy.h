//MaxEnemy.h
//log:2022/6/3
//MaxEnemy��Ķ���

#pragma once
#include "BaseEnemy.h"

//maxս���ľ�����Ϣ
#define MAX_WIDTH 14
#define MAX_HEIGHT 5
//max��Ѫ����Ϣ
#define MAX_BLOOD 12*ENEMY_BLOOD_RATIO
//max���ӵ�����������
#define MAX_RECORDI 1000

//max����ս��
class MaxEnemy :
    public BaseEnemy//�̳л���ս��
{
public:
    //���캯��
    MaxEnemy(WindowSetter* window = 0, GameConfig* config = 0, int x = 0, int y = 0);

    //��дս���ƶ�����
    virtual void move()override;

    //��дս�����ƺ���
    virtual void draw()override;

    //��дս���������
    virtual void shoot()override;

    //ս�����ٺ���
    void destroy();

    //ս����ʼ������
    void init();

    //ս���������ƺ���
    void drawHelper();
private:
    //ս�����״̬�ļ�ʱ��
    Timer shootRecordI;
};

