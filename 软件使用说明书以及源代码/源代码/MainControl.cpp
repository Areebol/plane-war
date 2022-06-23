//MainControl.cpp
//log:2022/6/3
//MainControl��Ķ���

#include "MainControl.h"

//��ʼ����Ϣ����
MainControl::MainControl(WindowSetter* window)
	:window(window), select(INFIT), gameConfig(), mPlane(window, &gameConfig,PLANE_BEGIN_X, PLANE_BEGIN_Y),
	  timer(600)
{
	init();
	//���뿪ʼ�˵�
	menu();
}

MainControl::~MainControl()
{
	delete gameSet;
	delete infiniteGame;
	delete scoreRecord;
}

void MainControl::paint_Button()
{
	string button;
	//���ư�ť����
	window->clear_choose();

	//���ð�ť���Ƹ�������
	paint_Button_Helper();
}

void MainControl::paint_Button_Helper()
{
	//�������ư�ť
	string button;
	window->clear_choose();
	//ѡ����ɫ����
	WORD buttonColor = COLOR_WHITE_BLACK;

	//���ư�ť
	button = MAIN_BUTTON1;
	window->paintSentence(MAIN_BUTTON1_X, MAIN_BUTTON1_Y, buttonColor, button);
	button = MAIN_BUTTON2;
	window->paintSentence(MAIN_BUTTON2_X, MAIN_BUTTON2_Y, buttonColor, button);
	button = MAIN_BUTTON3;
	window->paintSentence(MAIN_BUTTON3_X, MAIN_BUTTON3_Y, buttonColor, button);
	button = MAIN_BUTTON4;
	window->paintSentence(MAIN_BUTTON4_X, MAIN_BUTTON4_Y, buttonColor, button);
}

void MainControl::paint_Button_Flash()
{
	//����ѡ�������˸��ť��Ϣ
	string button;
	WORD flashColor = COLOR_REGULAR;
	paint_Button_Helper();

	//����ѡ�������˸�İ�ť
	switch (select)
	{
	case INFIT:
		button = MAIN_BUTTON1;
		window->paintSentence(MAIN_BUTTON1_X, MAIN_BUTTON1_Y, flashColor, button);
		break;
	case SET:
		button = MAIN_BUTTON2;
		window->paintSentence(MAIN_BUTTON2_X, MAIN_BUTTON2_Y, flashColor, button);
		break;
	case QUIT:
		button = MAIN_BUTTON3;
		window->paintSentence(MAIN_BUTTON3_X, MAIN_BUTTON3_Y, flashColor, button);
		break;
	case HISTORY:
		button = MAIN_BUTTON4;
		window->paintSentence(MAIN_BUTTON4_X, MAIN_BUTTON4_Y, flashColor, button);
		break;
	}
}

void MainControl::menu()
{
	//�����û�ѡ����Ϣ
	int key = 0;
	while (true)
	{
		//ˢ����Ļ����
		updateMenuScreen();

		//�����û�����
		if (_kbhit())
		{
			//��ֹ����
			if (!timer.update())
				int ignore = _getch();
			key = _getch();
			//����Ϊ�س�
			if (key == 13)
			{
				switch (select)
				{
				case INFIT:
					//�����޾�ģʽ
					infiniteGame->game();
					break;
				case SET:
					//������Ϸ����
					gameSet->menu();
					break;
				case QUIT:
					//�˳���Ϸ
					exit(4);
					break;
				case HISTORY:
					//����鿴��ʷ����
					scoreRecord->showHighestScore();
				}
			}
			//����Ϊ���¼� ����ѡ��
			if (key == 0xE0)
			{
				key = _getch();
				if (key == 72 || key == 80)
				{
					//�Ϲ�ѡ��
					if (key == 72)
						select = (Choices)((select +MAIN_BUTTON_MAX-1) % MAIN_BUTTON_MAX);
					//�¹�ѡ��
					else
						select = (Choices)((select + 1) % MAIN_BUTTON_MAX);
				}
			}
		}
	}
}

void MainControl::updateMenuScreen()
{
	//������ʾ��Ϣ
	window->clear();
	window->paint_edge();
	paintTitle();
	paint_Button();
	Sleep(MAIN_BUTTON_FLASH_RATE);
	window->update();

	//������ʾ��Ϣ��˸״̬
	window->clear();
	window->paint_edge();
	paintTitle();
	paint_Button_Flash();
	Sleep(MAIN_BUTTON_FLASH_RATE);
	window->update();
}

void MainControl::init()
{
	//��ʱ����ʼ��ʱ
	timer.start();
	gameSet = new GameSet(window, &gameConfig, &mPlane);
	infiniteGame = new InfiniteGame(window, &gameConfig, &mPlane);
	scoreRecord = new HistoryScoreRecord(window, gameConfig.getScoreFileRecord());
}

void MainControl::paintTitle()
{
	//������Ϸ������Ϣ
	string sentence;
	static WORD continueColor =0x0F;
	continueColor=(continueColor + 1) % 0x0F;
	sentence = "Plane War";
	window->paintSentence(TITLE1_X,TITLE1_Y,continueColor,sentence);
	sentence = "�ɻ���ս";
	window->paintSentence(TITLE1_X, TITLE1_Y+2, continueColor, sentence);
	sentence = "ʹ�����¼��ڲ˵��н���ѡ��";
	window->paintSentence(TITLE2_X, TITLE2_Y, 0x0F, sentence);
	sentence = "     ʹ��Enterȷ��ѡ��    ";
	window->paintSentence(TITLE3_X, TITLE3_Y, 0x0F, sentence);

	//����ս������
	mPlane.moveTo(PLANE_BEGIN_X, PLANE_BEGIN_Y);
	mPlane.paint();
}
