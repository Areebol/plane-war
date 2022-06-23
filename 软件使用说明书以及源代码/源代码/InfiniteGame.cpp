//InfiniteGame.cpp
//log:2022/6/4
//InfiniteGame类的成员函数的定义

#include "InfiniteGame.h"

using namespace std;
InfiniteGame::InfiniteGame(WindowSetter* window, GameConfig* config, Plane* plane)
	:window(window), config(config), mPlane(plane),gameRecorder(GAME_RATE),
	keyboardRecorder(KEYBOARD_RATE),enemyReleaseRecorder(config->getEnemyReleaseInterval()),
	enemyMoveRecorder(config->getEnemyMoveInterval()),score(0),
	releaseBuffRecorder(50000)
{
	//设置随机数
	srand((unsigned)time(NULL));
	//对游戏数据进行初始化操作
	init();
}

InfiniteGame::~InfiniteGame()
{
	//清除堆区的数据
	delete bossEnemy;
	for (int i = 0; i < BOOM_MAX; ++i)
		delete booms[i];

	for (int i = 0; i < MINI_MAX; ++i)
		delete miniEnemys[i];

	for (int i = 0; i < MAX_MAX; ++i)
		delete maxEnemys[i];	
}



void InfiniteGame::game()
{
	//对战机数据初始化
	int key = 0;
	//初始化数据
	init();
	releaseEnemyI();
	//如果战机未死亡 游戏继续
	while (mPlane->isDead()==false)
	{
		gameUpdate();

		if (_kbhit())
		{
			key = _getch();

			//输入为上下左右
			if (key == 0xE0)//防止其他键干扰
			{
				key = _getch();
				switch (key)
				{
				case 72://向上移动
					mPlane->move(Plane::UP);
					break;
				case 75://向左移动
					mPlane->move(Plane::LEFT);
					break;
				case 77://向右移动
					mPlane->move(Plane::RIGHT);
					break;
				case 80://向下移动
					mPlane->move(Plane::DOWN);
					break;
				}
			}
			//输入为ESc 暂停
			else if (key == 27)
			{
				//停止菜单
				if (pause())
				{
					//判断为真退出并销毁
					destroy();
					return;
				}
			}
		}
	}
	//判断该次得分是否破纪录
	//破纪录写入文件中保存
	if (config->getScoreFileRecord()->writeHighestScores(score))
		paintBreaking();
	//否则 绘制死亡面板
	else
		paintDead();
	//销毁数据
	destroy();
}

bool InfiniteGame::pause()
{
	//初始化屏幕数据
	//存放选择
	int key = 0;
	int select = 0;
	while (true)
	{
		//绘制选择数据
		//清空选项区域
		window->clear_choose();
		//清空游戏区域
		window->clear_game();
		//绘制停止菜单
		paintPause(select);
		//更新屏幕
		window->update();

		if (_kbhit())
		{
			//输入为回车
			key = _getch();
			if (key == 13)
			{
				switch (select)
				{
					//选择继续游戏
				case 0:
					return false;
					//选择返回菜单
				case 1:
					return true;
				}
			}
			if (key == 0xE0)
			{
				key = _getch();
				if (key == 72 || key == 80)
				{
					//上滚选择
					if (key == 72)
						select=(select+2-1)%2;
					//下滚选择
					else
						select=(select+1)%2;
				}
			}
		}
	}
}

void InfiniteGame::gameUpdate()
{
	//清空游戏区域
	window->clear_game();
	window->clear_choose();
	//绘制其他游戏信息
	paintOther();
	//检测所有的碰撞
	collisionAll();
	//控制战机
	controlPlane();
	//控制buff类行为
	controlBuffs();
	//控制敌机行为
	controlEnemy();
	//绘制爆炸效果
	paintBoom();
	//更新窗口
	window->update();
}




void InfiniteGame::paintBoom()
{
	//将所有未闲置的爆炸效果绘制
	for (int i = 0; i < BOOM_MAX; ++i)
	{
		booms[i]->reset();
		//将所有不闲置地爆炸效果绘制
		if (booms[i]->isFree() == false)
			booms[i]->paint();
	}
}

void InfiniteGame::setBoom(int x, int y)
{
	//将闲置的爆炸放置
	for (int i = 0; i < BOOM_MAX; ++i)
	{
		if (booms[i]->isFree() == true)
		{
			//放置boom
			booms[i]->resetPosition(x, y);
			booms[i]->setFree(false);
			break;
		}
	}
}

void InfiniteGame::collisionAll()
{
	//检测敌机与战机碰撞
	collisionEnemyWithPlane();
	//检测敌机与战机子弹碰撞
	collisionEnemyWithPlaneBullet();
	//检测战机与敌机子弹碰撞
	collisionPlaneWithEnemyBullet();
}

void InfiniteGame::collisionEnemyWithPlaneBullet()
{
	//遍历mini的子弹
	for (int i = 0; i < MINI_MAX; ++i)
	{
		if (miniEnemys[i]->isFree() == false)
		{
			if (mPlane->hitObject(miniEnemys[i]->getRec()))
			{
				miniEnemys[i]->getBlood() -= mPlane->bulletHurt;
				//碰撞放置爆炸效果
				setBoom(miniEnemys[i]->getX() + 2, miniEnemys[i]->getY() + 3);
			}
		}
	}
	//遍历max的子弹
	for (int i = 0; i < MAX_MAX; ++i)
	{
		if (maxEnemys[i]->isFree() == false)
		{
			if (mPlane->hitObject(maxEnemys[i]->getRec()))
			{
				maxEnemys[i]->getBlood() -= mPlane->bulletHurt;
				//碰撞放置爆炸效果
				setBoom(maxEnemys[i]->getX() + 4, maxEnemys[i]->getY() + 3);
			}
		}
	}
	//遍历boss的子弹
	if (bossEnemy->isFree() == false)
	{
		if (mPlane->hitObject(bossEnemy->getRec()))
		{
			bossEnemy->getBlood() -= mPlane->bulletHurt;
			//碰撞放置爆炸效果
			setBoom(bossEnemy->getX() + 16, bossEnemy->getY() + 6);
		}
	}
}

void InfiniteGame::collisionEnemyWithPlane()
{
	//遍历mini
	for (int i = 0; i < MINI_MAX; ++i)
	{
		if (miniEnemys[i]->isFree() == false)
		{
			if (mPlane->getRec().collision(miniEnemys[i]->getRec()))
			{
				//判断是否与战机发生碰撞
				miniEnemys[i]->getBlood() -= mPlane->hurt;
				mPlane->subBlood(mPlane->hurt);
				//扣除战机以及敌机血量
				setBoom(miniEnemys[i]->getX()+4, miniEnemys[i]->getY()+3);
			}
		}
	}
	//遍历max
	for (int i = 0; i < MAX_MAX; ++i)
	{
		if (mPlane->getRec().collision(miniEnemys[i]->getRec()))
		{
			if (mPlane->hitObject(maxEnemys[i]->getRec()))
			{
				//判断是否与战机发生碰撞
				maxEnemys[i]->getBlood() -= mPlane->hurt;
				mPlane->subBlood(mPlane->hurt);
				//扣除战机以及敌机血量
				setBoom(maxEnemys[i]->getX()+4, maxEnemys[i]->getY()+3);
			}
		}
	}
	//对boss判断
	if (bossEnemy->isFree() == false)
	{
		if (mPlane->getRec().collision(bossEnemy->getRec()))
		{
			//判断是否与战机发生碰撞
			bossEnemy->getBlood() -= mPlane->hurt;
			mPlane->subBlood(mPlane->hurt);
			//扣除战机以及敌机血量
			setBoom(bossEnemy->getX()+18, bossEnemy->getY()+6);
		}
	}
}

void InfiniteGame::collisionPlaneWithEnemyBullet()
{
	//遍历所有的子弹
	//遍历mini的所有子弹
	for (int i = 0; i < MINI_MAX; ++i)
	{
		//调用函数
		mPlane->subBlood(ENEMY_BULLET_A_HURT * miniEnemys[i]->hitObjectA(mPlane->getRec()));
		mPlane->subBlood(ENEMY_BULLET_B_HURT * miniEnemys[i]->hitObjectB(mPlane->getRec()));
		mPlane->subBlood(ENEMY_BULLET_C_HURT * miniEnemys[i]->hitObjectC(mPlane->getRec()));
		mPlane->subBlood(ENEMY_BULLET_D_HURT * miniEnemys[i]->hitObjectD(mPlane->getRec()));
	}
	//遍历max的所有子弹
	for (int i = 0; i < MAX_MAX; ++i)
	{
		//调用函数
		mPlane->subBlood(ENEMY_BULLET_A_HURT * maxEnemys[i]->hitObjectA(mPlane->getRec()));
		mPlane->subBlood(ENEMY_BULLET_B_HURT * maxEnemys[i]->hitObjectB(mPlane->getRec()));
		mPlane->subBlood(ENEMY_BULLET_C_HURT * maxEnemys[i]->hitObjectC(mPlane->getRec()));
		mPlane->subBlood(ENEMY_BULLET_D_HURT * maxEnemys[i]->hitObjectD(mPlane->getRec()));
	}
	//遍历max的所有子弹
	mPlane->subBlood(ENEMY_BULLET_A_HURT * bossEnemy->hitObjectA(mPlane->getRec()));
	mPlane->subBlood(ENEMY_BULLET_B_HURT * bossEnemy->hitObjectB(mPlane->getRec()));
	mPlane->subBlood(ENEMY_BULLET_C_HURT * bossEnemy->hitObjectC(mPlane->getRec()));
	mPlane->subBlood(ENEMY_BULLET_D_HURT * bossEnemy->hitObjectD(mPlane->getRec()));
}


void InfiniteGame::paintPause(int select)
{
	//绘制暂停页面
	string sentence;
	sentence = "暂停菜单";
	//根据选择绘制提示信息
	window->paintSentence(PAUSE_X, PAUSE_Y, 0x04, sentence);
	switch (select)
	{
	case 0:
		sentence = "继续游戏";
		break;
	case 1:
		sentence = "返回菜单";
		break;
	}
	//绘制其他提示信息
	window->paintSentence(PAUSE1_X, PAUSE1_Y + 2, 0x0F, sentence);
	sentence = " 使用上下键选择 ";
	window->paintSentence(PAUSE2_X, PAUSE2_Y, 0x0F, sentence);
	sentence = "使用Enter确认选择";
	window->paintSentence(PAUSE3_X, PAUSE3_Y, 0x0F, sentence);

}

void InfiniteGame::paintOther()
{
	//绘制得分
	string scoreString = "你的得分:   "+to_string(score);
	window->paintSentence(SCORE_X, SCORE_Y, 0x06, scoreString);

	//绘制其他提示信息
	string sentence = "使用上下左右键控制战机";
	window->paintSentence(GUIDE1_X, GUIDE1_Y, 0x0F, sentence);
    sentence = " 使用Esc进入暂停菜单 ";
	window->paintSentence(GUIDE2_X, GUIDE2_Y, 0x0F, sentence);

	//float bloodRate = (float)(mPlane->blood) / PLANE_BLOOD;
	//float bloodWidth = bloodRate * (CHOOSE_WIDTH-2);
	string bloodString = "战机当前耐久值：  " + to_string(mPlane->getBlood());
	window->paintSentence(BLOOD_X, BLOOD_Y, 0x09, bloodString);
}

void InfiniteGame::paintDead()
{
	//清空屏幕数据方便绘制
	window->clear_choose();
	window->clear_game();
	//绘制提示信息
	string sentence = "战机耐久值耗尽，无法继续战斗！";
	int paintX = (GAME_WIDTH - (int)sentence.size()) / 2 + 3;
	window->paintSentence(paintX, 15, 0x04, sentence);
	sentence = "按任意键继续......";
	paintX = (GAME_WIDTH - (int)sentence.size()) / 2 + 3;
	window->paintSentence(paintX, 35, 0x0F, sentence);
	window->update();

	//输入任意键退出
	while (!_kbhit())
		;
	//防止造成干扰
	cin.ignore();
}

void InfiniteGame::paintBreaking()
{
	//清空屏幕数据方便绘制
	window->clear_choose();
	window->clear_game();
	//绘制提示信息
	string sentence = "飞行员，尽管你的飞机坠毁了";
	int paintX = (GAME_WIDTH - (int)sentence.size()) / 2 + 3;
	window->paintSentence(paintX, 13, 0x03, sentence);
	sentence = "但你的战绩会被记录在高分榜上";
	paintX = (GAME_WIDTH - (int)sentence.size()) / 2 + 3;
	window->paintSentence(paintX, 15, 0x03, sentence);
	sentence = "按任意键继续......";
	paintX = (GAME_WIDTH - (int)sentence.size()) / 2 + 3;
	window->paintSentence(paintX, 35, 0x0F, sentence);
	window->update();
	//输入任意键退出
	while (!_kbhit())
		;
	//防止造成干扰
	cin.ignore();
}

void InfiniteGame::releaseEnemy()
{
	//随机选择释放
	int choose = rand() % 3;
	//释放敌机的计时器刷新可以释放敌机
	if (enemyReleaseRecorder.update() == false)
		return;
	if (choose == 0)
		//第一类释放敌机
		releaseEnemyI();
	else if(choose==1)
		//第二类释放敌机
		releaseEnemyII();
	else
		//第三类释放敌机
		releaseEnemyIII();
}

void InfiniteGame::releaseEnemyI()
{
	//释放3个minis
	int minisReleased = 0;
	for (int i = 0; i < MINI_MAX; ++i)
		if (miniEnemys[i]->isFree() == true)
		{
			miniEnemys[i]->setFree(false);
			miniEnemys[i]->reset(rand() % (GAME_WIDTH - MINI_WIDTH) + 2, 4*minisReleased);
			minisReleased++;//记录释放的mini数量
			if (minisReleased == 3)
				break;//释放足够退出
		}
}

void InfiniteGame::releaseEnemyII()
{
	//释放一个bos敌机
		for (int i = 0; i < MAX_MAX; ++i)
			if (maxEnemys[i]->isFree() == true)
			{
				maxEnemys[i]->setFree(false);
				maxEnemys[i]->reset(rand() % (GAME_WIDTH - MAX_WIDTH) + 2, 0);
				break;
			}
		//释放2个minis
		int minisReleased = 0;
		for (int i = 0; i < MINI_MAX; ++i)
			if (miniEnemys[i]->isFree() == true)
			{
				miniEnemys[i]->setFree(false);
				miniEnemys[i]->reset(rand() % (GAME_WIDTH - MINI_WIDTH) + 2, 3*(minisReleased+1));
				if (minisReleased == 2)
					break;//释放足够退出
			}
}

void InfiniteGame::releaseEnemyIII()
{
	//释放一个boss敌机
		if (bossEnemy->isFree() == true)
		{
			bossEnemy->setFree(false);
			bossEnemy->reset(rand() % (GAME_WIDTH - BOSS_WIDTH) + 2, 0);
		}
}

void InfiniteGame::moveAllEnemy()
{
	//遍历mini敌机进行移动
	for (int i = 0; i < MINI_MAX; ++i)
		if (miniEnemys[i]->isFree() == false)
		{
			miniEnemys[i]->move();
		}
	//遍历max敌机进行移动
	for (int i = 0; i < MAX_MAX; ++i)
		if (maxEnemys[i]->isFree() == false)
		{
			maxEnemys[i]->move();
		}
	//遍历boss敌机移动
	if (bossEnemy->isFree() == false)
		bossEnemy->move();
}

void InfiniteGame::drawAllEnemy()
{
	//遍历mini敌机进行绘制
	for (int i = 0; i < MINI_MAX; ++i)
		if (miniEnemys[i]->isFree() == false)
		{
			miniEnemys[i]->draw();
		}
	//遍历max敌机进行绘制
	for (int i = 0; i < MAX_MAX; ++i)
		if (maxEnemys[i]->isFree() == false)
		{
			maxEnemys[i]->draw();
		}
	//遍历boss敌机绘制
	if (bossEnemy->isFree() == false)
		bossEnemy->draw();
}

void InfiniteGame::clearDeadEnemy()
{
	//遍历mini敌机进行清空
	for (int i = 0; i < MINI_MAX; ++i)
	{
		//判断敌机是否死亡
		if (miniEnemys[i]->isDead())
		{
			//初始化敌机并且得分增加
			miniEnemys[i]->init();
			score += 10;
		}
	}
	//遍历max敌机进行绘制
	for (int i = 0; i < MAX_MAX; ++i)
	{
		//判断敌机是否死亡
		if (maxEnemys[i]->isDead())
		{
			//初始化敌机并且得分增加
			maxEnemys[i]->init();
			score += 30;
		}
	}
	//遍历boss敌机进行绘制
	if (bossEnemy->isDead())
	{
		//初始化敌机并且得分增加
		score += 100;

		//击败boss释放buff
		BaseBuff* buffPtr = nullptr;
		buffPtr = new BuffAward(window, mPlane, &score, bossEnemy->getX()+2, bossEnemy->getY());
		if (buffPtr != nullptr)
			buffs.push_back(buffPtr);
		buffPtr = new BuffAntidote(window, mPlane, &score, bossEnemy->getX()+6, bossEnemy->getY()+2);
		if (buffPtr != nullptr)
			buffs.push_back(buffPtr);
		bossEnemy->init();
	}
}

void InfiniteGame::shootEnemy()
{
	//遍历mini敌机进行射击子弹
	for (int i = 0; i < MINI_MAX; ++i)
		if (miniEnemys[i]->isFree() == false)
		{
			miniEnemys[i]->shoot();
		}
	//遍历max敌机进行射击子弹
	for (int i = 0; i < MAX_MAX; ++i)
		if (maxEnemys[i]->isFree() == false)
		{
			maxEnemys[i]->shoot();;
		}
	//遍历boss敌机进行射击子弹
	if (bossEnemy->isFree() == false)
		bossEnemy->shoot();
}

void InfiniteGame::controlEnemyBullet()
{
	//遍历mini
	for (int i = 0; i < MINI_MAX; ++i)
	{
		//移动以及绘制子弹
		miniEnemys[i]->moveAllBullet();
		miniEnemys[i]->drawAllBullet();
	}
	//遍历max
	for (int i = 0; i < MAX_MAX; ++i)
	{
		//移动以及绘制子弹
		maxEnemys[i]->moveAllBullet();
		maxEnemys[i]->drawAllBullet();
	}
	//遍历max
	{
		//移动以及绘制子弹
		bossEnemy->moveAllBullet();
		bossEnemy->drawAllBullet();
	}
}

void InfiniteGame::controlEnemy()
{
	//控制子弹行为
	controlEnemyBullet();
	//清除死亡敌机
	clearDeadEnemy();
	//释放敌机
	releaseEnemy();
	//移动敌机
	moveAllEnemy();
	//绘制敌机
	drawAllEnemy();
	//射击子弹
	shootEnemy();
	//判断敌机是否越界
	winEnemy();
}

void InfiniteGame::winEnemy()
{
	//判断是否有敌机越过地图
	//遍历mini类
	for (int i = 0; i < MINI_MAX; ++i)
	{
		if (miniEnemys[i]->isFree()==false&&miniEnemys[i]->getY() == WINDOW_ALL_HEIGHT - 3)
		{
			//得分扣除
			score -= 10;
			miniEnemys[i]->destroy();
		}
	}
	//遍历max类
	for (int i = 0; i < MAX_MAX; ++i)
	{
		if (maxEnemys[i]->isFree() == false && maxEnemys[i]->getY() == WINDOW_ALL_HEIGHT - 3)
		{
			//得分扣除
			score -= 20;
			maxEnemys[i]->destroy();
		}
	}
	//检查boss类
	if (bossEnemy->isFree() == false && bossEnemy->getY() == WINDOW_ALL_HEIGHT - 3)
	{
		//得分扣除
		score -= 50;
		bossEnemy->destroy();
	}
}

void InfiniteGame::releaseBuffs()
{
	//释放buff的计时器刷新可以释放buff
	if (releaseBuffRecorder.update())
	{
		//随机选择释放
		int choose = rand() % 5;
		//设置随机释放的坐标位置
		int pX = rand() % (GAME_WIDTH - 6);
		BaseBuff* buffPtr=nullptr;
		switch (choose)
		{
		case 0:
			//释放护盾类buff
			buffPtr = new BuffShield(bossEnemy, miniEnemys, maxEnemys, window, mPlane, &score, pX, 4);
			break;
		case 1:
			//释放隐形类buff
			buffPtr = new BuffInvisible(window, mPlane, &score,  pX, 4);
			break;
		case 2:
			//释放奖励类buff
			buffPtr = new BuffAward(window, mPlane, &score,  pX, 4);
			break;
		case 3:
			//释放补给类buff
			buffPtr = new BuffAntidote(window, mPlane, &score,  pX, 4);
			break;
		default:
			//释放轰炸类buff
			buffPtr = new BuffBoming(bossEnemy, miniEnemys, maxEnemys, window, mPlane, &score, pX, 4);
			break;
		}
		if(buffPtr!=nullptr)
			//存放buff
		buffs.push_back(buffPtr);
	}
}

void InfiniteGame::drawBuffs()
{
	//对每一个存在的buff进行绘制
	for_each(buffs.begin(), buffs.end(), [](BaseBuff* elem) {
		if (elem->Free() == false)
			elem->draw();
		});
}

void InfiniteGame::moveBuffs()
{
	//对每一存在的buff进行移动
	for_each(buffs.begin(), buffs.end(), [](BaseBuff* elem) {
		if (elem->Free() == false)
			elem->move();
		});
}

void InfiniteGame::pickBuffs()
{
	//判断是否有buff在地图上可以发生拾取行为
	for (auto it = buffs.begin(); it != buffs.end(); it++)
	{
		//buff可以被拾取
		if ((*it)->Free() == false && (*it)->rec.collision(mPlane->getRec()))
		{
			(*it)->Free() = true;
			//显示buff的作用效果
			(*it)->showInformation();
			//使用buff
			(*it)->use();
		}
	}
}

void InfiniteGame::useBuffs()
{
	//判断是否有持续性buff需要使用
	for (auto it = buffs.begin(); it != buffs.end(); it++)
	{
		if ((*it)->Free() == true && (*it)->beUsing == true)
			(*it)->use();
	}
}

void InfiniteGame::controlPlane()
{
	//战机射击子弹
	mPlane->shootBulletA();
	//战机移动子弹
	mPlane->moveBulletA();
	//绘制战机子弹
	mPlane->drawBulletA();
	//绘制战机
	mPlane->paint();
}

void InfiniteGame::deleteBuffs()
{
	//判断buff是否使用完毕 进行删除
	for (auto it = buffs.begin(); it != buffs.end(); ++it)
	{
		if ((*it)->Free() == true&&(*it)->beUsing==false)
		{
			BaseBuff* tempPtr = (*it);
			buffs.erase(it);
			//清除其在堆区数据
			delete tempPtr;
			break;
		}
	}
}

void InfiniteGame::controlBuffs()
{
	//释放对应的buff类
	releaseBuffs();
	//绘制所有的buff类
	drawBuffs();
	//拾取现存的buff类
	pickBuffs();
	//移动现存的buff类
	moveBuffs();
	//对于buff的销毁
	deleteBuffs();
	//使用暂时性buff
	useBuffs();
}

void InfiniteGame::init()
{
	//移动飞机到开始位置
	mPlane->moveTo(PLANE_BEGIN_X, PLANE_BEGIN_Y);
	//重新设置血量
	mPlane->setBlood(PLANE_BLOOD);
	//重新设置分数
	score = 0;
	//设置爆炸效果
	for (int i = 0; i < BOOM_MAX; ++i)
		booms[i] = new Boom(window);

	for (int i = 0; i < MINI_MAX; ++i)
		miniEnemys[i] = new MiniEnemy(window, config, 0, 0);

	for (int i = 0; i < MAX_MAX; ++i)
		maxEnemys[i] = new MaxEnemy(window, config, 0, 0);

	bossEnemy = new BossEnemy(window, config, 0, 0);
	//启动计时器
	gameRecorder.start();
	keyboardRecorder.start();
	enemyReleaseRecorder.start();
	enemyMoveRecorder.start();
	releaseBuffRecorder.start();
}

void InfiniteGame::destroy()
{
	//对数据初始化
	init();
	for(int i=0;i<PLANE_BULLETSA_MAX;++i)
		mPlane->destroyBullet(i);
}



