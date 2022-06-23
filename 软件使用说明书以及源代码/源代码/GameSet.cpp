//GameSet.cpp
//log:2022/6/4
//GameSet��ĳ�Ա��������

#include "GameSet.h"

GameSet::GameSet(WindowSetter* window,GameConfig* config,Plane* plane)
	:window(window),config(config),select(SETBULLET),mPlane(plane),
	buttonFlashRecorder(SET_BUTTON_FLASH_RATE)
{
	//��ʼ����Ϸ���õ���Ϣ
	buttonFlashRecorder.start();
}

void GameSet::paint_Button()
{
	//���ư�ť��Ϣ
	string button;
	//������
	window->clear_choose();
	//���ư�ť
	paint_Button_Helper();
}

void GameSet::paint_Button_Helper()
{
	//�������ư�ť��Ϣ
	string button;
	//������
	window->clear_choose();
	WORD buttonColor = COLOR_WHITE_BLACK;
	//�������ְ�ť
	button = SET_BUTTON1;
	window->paintSentence(SET_BUTTON1_X, SET_BUTTON1_Y, buttonColor, button);
	button = SET_BUTTON2;
	window->paintSentence(SET_BUTTON2_X, SET_BUTTON2_Y, buttonColor, button);
	button = SET_BUTTON3;
	window->paintSentence(SET_BUTTON3_X, SET_BUTTON3_Y, buttonColor, button);
}

void GameSet::paint_Button_Flash()
{
	//����ѡ����ư�ť��˸����Ϣ
	string button;
	WORD flashColor = COLOR_REGULAR;
	//���ø����������ư�ť
	paint_Button_Helper();
	//����ѡ������˸
	switch (select)
	{
		//ѡ�����ð�ť
	case SETBULLET:
		button = SET_BUTTON1;
		window->paintSentence(SET_BUTTON1_X, SET_BUTTON1_Y, flashColor, button);
		break;
		//ѡ�������Ѷ�
	case SELECTLEVEL:
		button = SET_BUTTON2;
		window->paintSentence(SET_BUTTON2_X, SET_BUTTON2_Y, flashColor, button);
		break;
		//ѡ�񷵻ز˵�
	case RETURN:
		button = SET_BUTTON3;
		window->paintSentence(SET_BUTTON3_X, SET_BUTTON3_Y, flashColor, button);
		break;
	}
}

void GameSet::menu()
{
	//������Ļ��ʾ��Ϣ
	int key = 0;
	//��ս���ƶ�����ʼλ��
	mPlane->moveTo(PLANE_BEGIN_X, PLANE_BEGIN_Y);
	//���ư�ť����
	paint_Button();

	while (true)
	{
		menuUpdate();
		//�ж��û�����
		if (_kbhit())
		{
			key = _getch();
			//����Ϊ�س�
			if (key == 13)
			{
				switch (select)
				{
				case SETBULLET:
					//���������ӵ���Ϣ
					setBullet();
					return;
				case SELECTLEVEL:
					//���������Ѷ���Ϣ
					setLevel();
					return;
				case RETURN:
					//������һ���˵�
					return;
				}
			}
			if (key == 0xE0)
			{
				key = _getch();
				if (key == 72 || key == 80)
				{
					//�Ϲ�ѡ��
					if (key == 72)
						select = (Choices)((select +SET_BUTTON_MAX- 1) % SET_BUTTON_MAX);
					//�¹�ѡ��
					else
						select = (Choices)((select + 1) % SET_BUTTON_MAX);
				}
			}
		}
	}
}

void GameSet::setBullet()
{
	int key = 0;
	while (true)
	{
		//�������
		window->clear_choose();
		window->clear_game();
		//���������Ѷ����
		paintSetBullet();
		mPlane->paint();
		mPlane->shootBulletA();
		mPlane->moveBulletA();
		mPlane->drawBulletA();
		//������Ļ
		window->update();

		//�ж��û�����
		if (_kbhit())
		{
			key = _getch();
			//����Ϊ�س�
			if (key == 13)
			{
				//ȷ��ѡ�� �����ϼ��˵�
				return;
			}
			if (key == 0xE0)
			{
				//����ѡ��
				key = _getch();
				if (key == 72 || key == 80)
				{
					//�Ϲ�ѡ��
					if (key == 72)
						config->setBulletIndex((config->getBulletIndex() + SOURCE_BULLET_MAX - 1) % SOURCE_BULLET_MAX);
					//�¹�ѡ��
					else
						config->setBulletIndex((config->getBulletIndex() + SOURCE_BULLET_MAX + 1) % SOURCE_BULLET_MAX);
				}
			}
		}
	}
}

void GameSet::setLevel()
{
	//��ʼ����Ļ����
	int key = 0;
	while (true)
	{
		//�����Ѷ�ѡ����ʾ�˵�
		//�������
		window->clear_choose();
		window->clear_game();
		//���������Ѷ����
		paintSetLevel();
		//�����Ѷ���ʾ
		paintLevel();
		//������Ļ
		window->update();

		//����û�����
		if (_kbhit())
		{
			//������Ϸ��������
			config->setLevel((level)config->getLevel());
			key = _getch();
			//����Ϊ�س�
			if (key == 13)
			{
				//ȷ��ѡ�� �����ϼ��˵�
				return;
			}
			if (key == 0xE0)
			{
				//ѡ��
				key = _getch();
				if (key == 72 || key == 80)
				{
					//�Ϲ�ѡ��
					if (key == 72)
						config->setLevel((level)((config->getLevel() + LEVEL_MAX - 1) % LEVEL_MAX));
					//�¹�ѡ��
					else
						config->setLevel((level)((config->getLevel() + LEVEL_MAX + 1) % LEVEL_MAX));
				}
			}
		}
	}
}

void GameSet::paintSetBullet()
{
	//���������ӵ��Ĳ˵�ѡ��
	string sentence;
	sentence = "ʹ�����¼�ѡ���ӵ�";
	window->paintSentence(GUIDE1_SET_BULLET_X, GUIDE1_SET_BULLET_Y, 0x0F, sentence);
	sentence = "  ʹ��Enter��ȷ�� ";
	window->paintSentence(GUIDE2_SET_BULLET_X, GUIDE2_SET_BULLET_Y, 0x0F, sentence);
}

void GameSet::paintSetLevel()
{
	//���������ѶȵĲ˵�ѡ��
	string sentence;
	sentence = "ʹ�����¼�ѡ���Ѷ�";
	window->paintSentence(GUIDE1_SET_BULLET_X, GUIDE1_SET_BULLET_Y, 0x0F, sentence);
	sentence = "  ʹ��Enter��ȷ�� ";
	window->paintSentence(GUIDE2_SET_BULLET_X, GUIDE2_SET_BULLET_Y, 0x0F, sentence);
}

void GameSet::paintLevel()
{
	//�����Ѷ���ʾ
	string sentence;
	sentence = "  ��ǰ�Ѷ�     ";
	window->paintSentence(GUIDE1_SET_LEVEL_X, GUIDE1_SET_LEVEL_Y, 0x0F, sentence);
	switch (config->getLevel())
	{
		//�Ѷ�Ϊ��
	case LOW:
		sentence = "    ��     ";
		window->paintSentence(GUIDE2_SET_LEVEL_X, GUIDE2_SET_LEVEL_Y, 0x0F, sentence);
		break;
		//�Ѷ�Ϊ�е�
	case MIDDLE:
		sentence = "    �е�     ";
		window->paintSentence(GUIDE2_SET_LEVEL_X, GUIDE2_SET_LEVEL_Y, 0x0F, sentence);
		break;
		//�Ѷ�Ϊ����
	case HIGH:
		sentence = "    ����     ";
		window->paintSentence(GUIDE2_SET_LEVEL_X, GUIDE2_SET_LEVEL_Y, 0x0F, sentence);
		break;
	}
}

void GameSet::menuUpdate()
{
	static bool sign = true;
	static bool swag = true;
	//�ж��Ƿ���Ҫ��˸��ť
	if (buttonFlashRecorder.update())
	{
		swag = true;
		if (sign)
			paint_Button_Flash();
		else
			paint_Button();
	}
	window->clear_game();
	//���Ʒɻ�
	mPlane->paint();
	//������Ļ
	window->update();
	//����ս������
	window->clear_game();
	//���Ʒɻ�
	mPlane->paint();

	//�԰�ť����˸����
	if (swag)
	{
		if (sign)
		{
			paint_Button_Flash();
			sign = false;
		}
		else
		{
			paint_Button();
			sign = true;
		}
		swag = false;
	}
	//����Ļ�������ݸ���
	window->update();
}

void GameSet::setSelect(Choices select)
{
	this->select = select;
}

Choices GameSet::getSelect() const
{
	return select;
}
