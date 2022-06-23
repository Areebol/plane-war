//MainControl.cpp
//log:2022/6/3
//MainControl类的定义

#include "MainControl.h"

//初始化信息配置
MainControl::MainControl(WindowSetter* window)
	:window(window), select(INFIT), gameConfig(), mPlane(window, &gameConfig,PLANE_BEGIN_X, PLANE_BEGIN_Y),
	  timer(600)
{
	init();
	//进入开始菜单
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
	//绘制按钮数据
	window->clear_choose();

	//调用按钮绘制辅助函数
	paint_Button_Helper();
}

void MainControl::paint_Button_Helper()
{
	//辅助绘制按钮
	string button;
	window->clear_choose();
	//选择颜色基调
	WORD buttonColor = COLOR_WHITE_BLACK;

	//绘制按钮
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
	//根据选择绘制闪烁按钮信息
	string button;
	WORD flashColor = COLOR_REGULAR;
	paint_Button_Helper();

	//根据选择绘制闪烁的按钮
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
	//保存用户选择信息
	int key = 0;
	while (true)
	{
		//刷新屏幕数据
		updateMenuScreen();

		//读入用户输入
		if (_kbhit())
		{
			//防止连按
			if (!timer.update())
				int ignore = _getch();
			key = _getch();
			//输入为回车
			if (key == 13)
			{
				switch (select)
				{
				case INFIT:
					//进入无尽模式
					infiniteGame->game();
					break;
				case SET:
					//进入游戏设置
					gameSet->menu();
					break;
				case QUIT:
					//退出游戏
					exit(4);
					break;
				case HISTORY:
					//进入查看历史分数
					scoreRecord->showHighestScore();
				}
			}
			//输入为上下键 进行选择
			if (key == 0xE0)
			{
				key = _getch();
				if (key == 72 || key == 80)
				{
					//上滚选择
					if (key == 72)
						select = (Choices)((select +MAIN_BUTTON_MAX-1) % MAIN_BUTTON_MAX);
					//下滚选择
					else
						select = (Choices)((select + 1) % MAIN_BUTTON_MAX);
				}
			}
		}
	}
}

void MainControl::updateMenuScreen()
{
	//绘制提示信息
	window->clear();
	window->paint_edge();
	paintTitle();
	paint_Button();
	Sleep(MAIN_BUTTON_FLASH_RATE);
	window->update();

	//绘制提示信息闪烁状态
	window->clear();
	window->paint_edge();
	paintTitle();
	paint_Button_Flash();
	Sleep(MAIN_BUTTON_FLASH_RATE);
	window->update();
}

void MainControl::init()
{
	//计时器开始计时
	timer.start();
	gameSet = new GameSet(window, &gameConfig, &mPlane);
	infiniteGame = new InfiniteGame(window, &gameConfig, &mPlane);
	scoreRecord = new HistoryScoreRecord(window, gameConfig.getScoreFileRecord());
}

void MainControl::paintTitle()
{
	//绘制游戏标题信息
	string sentence;
	static WORD continueColor =0x0F;
	continueColor=(continueColor + 1) % 0x0F;
	sentence = "Plane War";
	window->paintSentence(TITLE1_X,TITLE1_Y,continueColor,sentence);
	sentence = "飞机大战";
	window->paintSentence(TITLE1_X, TITLE1_Y+2, continueColor, sentence);
	sentence = "使用上下键在菜单中进行选择";
	window->paintSentence(TITLE2_X, TITLE2_Y, 0x0F, sentence);
	sentence = "     使用Enter确认选择    ";
	window->paintSentence(TITLE3_X, TITLE3_Y, 0x0F, sentence);

	//绘制战机形象
	mPlane.moveTo(PLANE_BEGIN_X, PLANE_BEGIN_Y);
	mPlane.paint();
}
