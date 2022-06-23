//config.h
//log:2022/6/3
//�����ļ������ò����ĺ궨��

#ifndef CONFIG_H
#define CONFIG_H

#include<string>
#include<Windows.h>

using std::string;

//��������-----------------------------------------------------------------------

//�Դ����������� ----------------------------------------------------------------
//ѡ������Ŀ��
#define CHOOSE_WIDTH  30 
//����߶�
#define WINDOW_HEIGHT 40 
//��Ϸ���
#define GAME_WIDTH 60
//���ڼ��δ�С��Ϣ
#define WINDOW_ALL_HEIGHT WINDOW_HEIGHT+6 
#define WINDOW_ALL_WIDTH GAME_WIDTH + CHOOSE_WIDTH + 6 

//����Ϸ��������
#define GAME_RATE 10 //��Ϸ�ٶ�
#define LEVEL_MAX 3 //��Ϸ�Ѷȵ����ѡ������


//����ʾ��Ϣ����������-----------------------------------------------------------
//������������
#define SCORE_X  GAME_WIDTH+4+8 
#define SCORE_Y  3+12

#define BLOOD_X GAME_WIDTH+4+4
#define BLOOD_Y 3+8
//��ʾ1����
#define GUIDE1_X GAME_WIDTH+4+4
#define GUIDE1_Y 3+20
//��ʾ2����
#define GUIDE2_X GAME_WIDTH+4+4
#define GUIDE2_Y 3+25
//�����ӵ���ʾ1����
#define GUIDE1_SET_BULLET_X GAME_WIDTH+4+6
#define GUIDE1_SET_BULLET_Y 3+15
//�����ӵ���ʾ2����
#define GUIDE2_SET_BULLET_X GAME_WIDTH+4+6
#define GUIDE2_SET_BULLET_Y 3+20
//�����Ѷ���ʾ1����
#define GUIDE1_SET_LEVEL_X 2+25
#define GUIDE1_SET_LEVEL_Y 3+15
//�����Ѷ���ʾ2����
#define GUIDE2_SET_LEVEL_X 2+25 
#define GUIDE2_SET_LEVEL_Y 3+20
//��������1
#define TITLE1_X 2+26
#define TITLE1_Y 3+5
//��������2
#define TITLE2_X 2+17
#define TITLE2_Y 3+15
//��������3
#define TITLE3_X 2+17
#define TITLE3_Y 3+20
//��ͣ��������
#define PAUSE_X 2+26
#define PAUSE_Y 3+13
//��ͣ1����
#define PAUSE1_X  2+26
#define PAUSE1_Y  3+18
//��ͣ2����
#define PAUSE2_X GAME_WIDTH+4+6
#define PAUSE2_Y 3+15
//��ͣ3����
#define PAUSE3_X GAME_WIDTH+4+6
#define PAUSE3_Y 3+20







//��ըЧ����������-------------------------------------------------------------
//��ը���
#define BOOM_INTERVAL 1
//��ը�������
#define BOOM_MAX 15

//�ı���ɫ��������
#define COLOR_REGULAR 0x0F
#define COLOR_WHOLE_GREEN 0x22
#define COLOR_WHOLE_BLACK 0x00
#define COLOR_WHITE_BLACK 0xF0

//�����ڰ�ť��Ϣ����-----------------------------------------------------------
#define MAIN_BUTTON_MAX 4
#define MAIN_BUTTON1 " �޾�ģʽ "
#define MAIN_BUTTON2 " ��Ϸ���� "
#define MAIN_BUTTON3 " �˳���Ϸ "
#define MAIN_BUTTON4 " ��ʷ�߷� "
#define MAIN_BUTTON1_X GAME_WIDTH+4+8
#define MAIN_BUTTON2_X GAME_WIDTH+4+8
#define MAIN_BUTTON3_X GAME_WIDTH+4+8
#define MAIN_BUTTON4_X GAME_WIDTH+4+8
#define MAIN_BUTTON1_Y 3+12
#define MAIN_BUTTON2_Y 3+15
#define MAIN_BUTTON3_Y 3+21
#define MAIN_BUTTON4_Y 3+18
#define MAIN_BUTTON_FLASH_RATE 100

//���ô��ڰ�ť��Ϣ����------------------------------------------------------------
#define SET_BUTTON_MAX 3
#define SET_BUTTON1 " ѡ���ӵ� "
#define SET_BUTTON2 " ѡ���Ѷ� "
#define SET_BUTTON3 " ���ز˵� "
#define SET_BUTTON1_X GAME_WIDTH+4+8
#define SET_BUTTON2_X GAME_WIDTH+4+8
#define SET_BUTTON3_X GAME_WIDTH+4+8
#define SET_BUTTON1_Y 3+12
#define SET_BUTTON2_Y 3+15
#define SET_BUTTON3_Y 3+18
#define SET_BUTTON_FLASH_RATE 100


//�Լ��̶�ȡ��Ϣ����
#define KEYBOARD_RATE 50
#endif
