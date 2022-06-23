//GameSet.h
//log:2022/6/4
//��Ϸ�����ඨ��

#ifndef GAMESET_H
#define GAMESET_H

#include"config.h"
#include"WindowSetter.h"
#include"GameConfig.h"
#include"Plane.h"
#include<conio.h>
#include<string>

//�ӵ���Դ���ֵ
#define SOURCE_BULLET_MAX 4
//��Ϣ����enum
enum Choices { SETBULLET, SELECTLEVEL, RETURN };
//��Ϸ������
class GameSet
{
public:
	//���캯��
	GameSet(WindowSetter* window, GameConfig* config,Plane* plane);

	//���ư�ť����
	void paint_Button();
	
	//�������ư�ť����
	void paint_Button_Helper();
	
	//������˸��ť����
	void paint_Button_Flash();

	//�˵�����
	void menu();
	
	//�����ӵ�����
	void setBullet();
	
	//������Ϸ�ѶȺ���
	void setLevel();

	//���������ӵ���庯��
	void paintSetBullet();
	
	//���������Ѷ���庯��
	void paintSetLevel();
	
	//�����Ѷ�ѡ����ʾ
	void paintLevel();

	//����Ļ����ˢ��
	void menuUpdate();

	//����ѡ��
	void setSelect(Choices select);

	//����ѡ��
	Choices getSelect()const;
private:
	//�����û�������Ϣ
	Choices select;
	//���ƴ���ָ����ƴ�����
	WindowSetter* window;
	//��Ϸ����������ָ��
	GameConfig* config;
	//ս��ָ��
	Plane* mPlane;
	//��ʱ�� ���ư�ť��˸
	Timer buttonFlashRecorder;
};

#endif

