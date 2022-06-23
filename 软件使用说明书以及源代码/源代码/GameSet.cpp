//GameSet.cpp
//log:2022/6/4
//GameSet类的成员函数定义

#include "GameSet.h"

GameSet::GameSet(WindowSetter* window,GameConfig* config,Plane* plane)
	:window(window),config(config),select(SETBULLET),mPlane(plane),
	buttonFlashRecorder(SET_BUTTON_FLASH_RATE)
{
	//初始化游戏设置的信息
	buttonFlashRecorder.start();
}

void GameSet::paint_Button()
{
	//绘制按钮信息
	string button;
	//先清屏
	window->clear_choose();
	//绘制按钮
	paint_Button_Helper();
}

void GameSet::paint_Button_Helper()
{
	//辅助绘制按钮信息
	string button;
	//先清屏
	window->clear_choose();
	WORD buttonColor = COLOR_WHITE_BLACK;
	//绘制三种按钮
	button = SET_BUTTON1;
	window->paintSentence(SET_BUTTON1_X, SET_BUTTON1_Y, buttonColor, button);
	button = SET_BUTTON2;
	window->paintSentence(SET_BUTTON2_X, SET_BUTTON2_Y, buttonColor, button);
	button = SET_BUTTON3;
	window->paintSentence(SET_BUTTON3_X, SET_BUTTON3_Y, buttonColor, button);
}

void GameSet::paint_Button_Flash()
{
	//根据选择绘制按钮闪烁的信息
	string button;
	WORD flashColor = COLOR_REGULAR;
	//调用辅助函数绘制按钮
	paint_Button_Helper();
	//根据选择来闪烁
	switch (select)
	{
		//选择设置按钮
	case SETBULLET:
		button = SET_BUTTON1;
		window->paintSentence(SET_BUTTON1_X, SET_BUTTON1_Y, flashColor, button);
		break;
		//选择设置难度
	case SELECTLEVEL:
		button = SET_BUTTON2;
		window->paintSentence(SET_BUTTON2_X, SET_BUTTON2_Y, flashColor, button);
		break;
		//选择返回菜单
	case RETURN:
		button = SET_BUTTON3;
		window->paintSentence(SET_BUTTON3_X, SET_BUTTON3_Y, flashColor, button);
		break;
	}
}

void GameSet::menu()
{
	//绘制屏幕提示信息
	int key = 0;
	//将战机移动到开始位置
	mPlane->moveTo(PLANE_BEGIN_X, PLANE_BEGIN_Y);
	//绘制按钮数据
	paint_Button();

	while (true)
	{
		menuUpdate();
		//判断用户输入
		if (_kbhit())
		{
			key = _getch();
			//输入为回车
			if (key == 13)
			{
				switch (select)
				{
				case SETBULLET:
					//进入设置子弹信息
					setBullet();
					return;
				case SELECTLEVEL:
					//进入设置难度信息
					setLevel();
					return;
				case RETURN:
					//返回上一级菜单
					return;
				}
			}
			if (key == 0xE0)
			{
				key = _getch();
				if (key == 72 || key == 80)
				{
					//上滚选择
					if (key == 72)
						select = (Choices)((select +SET_BUTTON_MAX- 1) % SET_BUTTON_MAX);
					//下滚选择
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
		//清空数据
		window->clear_choose();
		window->clear_game();
		//绘制设置难度面板
		paintSetBullet();
		mPlane->paint();
		mPlane->shootBulletA();
		mPlane->moveBulletA();
		mPlane->drawBulletA();
		//更新屏幕
		window->update();

		//判断用户输入
		if (_kbhit())
		{
			key = _getch();
			//输入为回车
			if (key == 13)
			{
				//确认选择 返回上级菜单
				return;
			}
			if (key == 0xE0)
			{
				//进行选择
				key = _getch();
				if (key == 72 || key == 80)
				{
					//上滚选择
					if (key == 72)
						config->setBulletIndex((config->getBulletIndex() + SOURCE_BULLET_MAX - 1) % SOURCE_BULLET_MAX);
					//下滚选择
					else
						config->setBulletIndex((config->getBulletIndex() + SOURCE_BULLET_MAX + 1) % SOURCE_BULLET_MAX);
				}
			}
		}
	}
}

void GameSet::setLevel()
{
	//初始化屏幕数据
	int key = 0;
	while (true)
	{
		//绘制难度选择提示菜单
		//清空数据
		window->clear_choose();
		window->clear_game();
		//绘制设置难度面板
		paintSetLevel();
		//绘制难度提示
		paintLevel();
		//更新屏幕
		window->update();

		//获得用户输入
		if (_kbhit())
		{
			//更新游戏配置数据
			config->setLevel((level)config->getLevel());
			key = _getch();
			//输入为回车
			if (key == 13)
			{
				//确认选择 返回上级菜单
				return;
			}
			if (key == 0xE0)
			{
				//选择
				key = _getch();
				if (key == 72 || key == 80)
				{
					//上滚选择
					if (key == 72)
						config->setLevel((level)((config->getLevel() + LEVEL_MAX - 1) % LEVEL_MAX));
					//下滚选择
					else
						config->setLevel((level)((config->getLevel() + LEVEL_MAX + 1) % LEVEL_MAX));
				}
			}
		}
	}
}

void GameSet::paintSetBullet()
{
	//绘制设置子弹的菜单选项
	string sentence;
	sentence = "使用上下键选择子弹";
	window->paintSentence(GUIDE1_SET_BULLET_X, GUIDE1_SET_BULLET_Y, 0x0F, sentence);
	sentence = "  使用Enter键确认 ";
	window->paintSentence(GUIDE2_SET_BULLET_X, GUIDE2_SET_BULLET_Y, 0x0F, sentence);
}

void GameSet::paintSetLevel()
{
	//绘制设置难度的菜单选项
	string sentence;
	sentence = "使用上下键选择难度";
	window->paintSentence(GUIDE1_SET_BULLET_X, GUIDE1_SET_BULLET_Y, 0x0F, sentence);
	sentence = "  使用Enter键确认 ";
	window->paintSentence(GUIDE2_SET_BULLET_X, GUIDE2_SET_BULLET_Y, 0x0F, sentence);
}

void GameSet::paintLevel()
{
	//绘制难度提示
	string sentence;
	sentence = "  当前难度     ";
	window->paintSentence(GUIDE1_SET_LEVEL_X, GUIDE1_SET_LEVEL_Y, 0x0F, sentence);
	switch (config->getLevel())
	{
		//难度为简单
	case LOW:
		sentence = "    简单     ";
		window->paintSentence(GUIDE2_SET_LEVEL_X, GUIDE2_SET_LEVEL_Y, 0x0F, sentence);
		break;
		//难度为中等
	case MIDDLE:
		sentence = "    中等     ";
		window->paintSentence(GUIDE2_SET_LEVEL_X, GUIDE2_SET_LEVEL_Y, 0x0F, sentence);
		break;
		//难度为困难
	case HIGH:
		sentence = "    困难     ";
		window->paintSentence(GUIDE2_SET_LEVEL_X, GUIDE2_SET_LEVEL_Y, 0x0F, sentence);
		break;
	}
}

void GameSet::menuUpdate()
{
	static bool sign = true;
	static bool swag = true;
	//判断是否需要闪烁按钮
	if (buttonFlashRecorder.update())
	{
		swag = true;
		if (sign)
			paint_Button_Flash();
		else
			paint_Button();
	}
	window->clear_game();
	//绘制飞机
	mPlane->paint();
	//更新屏幕
	window->update();
	//绘制战机动画
	window->clear_game();
	//绘制飞机
	mPlane->paint();

	//对按钮的闪烁处理
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
	//对屏幕进行数据更新
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
