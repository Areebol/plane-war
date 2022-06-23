//InfiniteGame.cpp
//log:2022/6/4
//InfiniteGame��ĳ�Ա�����Ķ���

#include "InfiniteGame.h"

using namespace std;
InfiniteGame::InfiniteGame(WindowSetter* window, GameConfig* config, Plane* plane)
	:window(window), config(config), mPlane(plane),gameRecorder(GAME_RATE),
	keyboardRecorder(KEYBOARD_RATE),enemyReleaseRecorder(config->getEnemyReleaseInterval()),
	enemyMoveRecorder(config->getEnemyMoveInterval()),score(0),
	releaseBuffRecorder(50000)
{
	//���������
	srand((unsigned)time(NULL));
	//����Ϸ���ݽ��г�ʼ������
	init();
}

InfiniteGame::~InfiniteGame()
{
	//�������������
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
	//��ս�����ݳ�ʼ��
	int key = 0;
	//��ʼ������
	init();
	releaseEnemyI();
	//���ս��δ���� ��Ϸ����
	while (mPlane->isDead()==false)
	{
		gameUpdate();

		if (_kbhit())
		{
			key = _getch();

			//����Ϊ��������
			if (key == 0xE0)//��ֹ����������
			{
				key = _getch();
				switch (key)
				{
				case 72://�����ƶ�
					mPlane->move(Plane::UP);
					break;
				case 75://�����ƶ�
					mPlane->move(Plane::LEFT);
					break;
				case 77://�����ƶ�
					mPlane->move(Plane::RIGHT);
					break;
				case 80://�����ƶ�
					mPlane->move(Plane::DOWN);
					break;
				}
			}
			//����ΪESc ��ͣ
			else if (key == 27)
			{
				//ֹͣ�˵�
				if (pause())
				{
					//�ж�Ϊ���˳�������
					destroy();
					return;
				}
			}
		}
	}
	//�жϸôε÷��Ƿ��Ƽ�¼
	//�Ƽ�¼д���ļ��б���
	if (config->getScoreFileRecord()->writeHighestScores(score))
		paintBreaking();
	//���� �����������
	else
		paintDead();
	//��������
	destroy();
}

bool InfiniteGame::pause()
{
	//��ʼ����Ļ����
	//���ѡ��
	int key = 0;
	int select = 0;
	while (true)
	{
		//����ѡ������
		//���ѡ������
		window->clear_choose();
		//�����Ϸ����
		window->clear_game();
		//����ֹͣ�˵�
		paintPause(select);
		//������Ļ
		window->update();

		if (_kbhit())
		{
			//����Ϊ�س�
			key = _getch();
			if (key == 13)
			{
				switch (select)
				{
					//ѡ�������Ϸ
				case 0:
					return false;
					//ѡ�񷵻ز˵�
				case 1:
					return true;
				}
			}
			if (key == 0xE0)
			{
				key = _getch();
				if (key == 72 || key == 80)
				{
					//�Ϲ�ѡ��
					if (key == 72)
						select=(select+2-1)%2;
					//�¹�ѡ��
					else
						select=(select+1)%2;
				}
			}
		}
	}
}

void InfiniteGame::gameUpdate()
{
	//�����Ϸ����
	window->clear_game();
	window->clear_choose();
	//����������Ϸ��Ϣ
	paintOther();
	//������е���ײ
	collisionAll();
	//����ս��
	controlPlane();
	//����buff����Ϊ
	controlBuffs();
	//���Ƶл���Ϊ
	controlEnemy();
	//���Ʊ�ըЧ��
	paintBoom();
	//���´���
	window->update();
}




void InfiniteGame::paintBoom()
{
	//������δ���õı�ըЧ������
	for (int i = 0; i < BOOM_MAX; ++i)
	{
		booms[i]->reset();
		//�����в����õر�ըЧ������
		if (booms[i]->isFree() == false)
			booms[i]->paint();
	}
}

void InfiniteGame::setBoom(int x, int y)
{
	//�����õı�ը����
	for (int i = 0; i < BOOM_MAX; ++i)
	{
		if (booms[i]->isFree() == true)
		{
			//����boom
			booms[i]->resetPosition(x, y);
			booms[i]->setFree(false);
			break;
		}
	}
}

void InfiniteGame::collisionAll()
{
	//���л���ս����ײ
	collisionEnemyWithPlane();
	//���л���ս���ӵ���ײ
	collisionEnemyWithPlaneBullet();
	//���ս����л��ӵ���ײ
	collisionPlaneWithEnemyBullet();
}

void InfiniteGame::collisionEnemyWithPlaneBullet()
{
	//����mini���ӵ�
	for (int i = 0; i < MINI_MAX; ++i)
	{
		if (miniEnemys[i]->isFree() == false)
		{
			if (mPlane->hitObject(miniEnemys[i]->getRec()))
			{
				miniEnemys[i]->getBlood() -= mPlane->bulletHurt;
				//��ײ���ñ�ըЧ��
				setBoom(miniEnemys[i]->getX() + 2, miniEnemys[i]->getY() + 3);
			}
		}
	}
	//����max���ӵ�
	for (int i = 0; i < MAX_MAX; ++i)
	{
		if (maxEnemys[i]->isFree() == false)
		{
			if (mPlane->hitObject(maxEnemys[i]->getRec()))
			{
				maxEnemys[i]->getBlood() -= mPlane->bulletHurt;
				//��ײ���ñ�ըЧ��
				setBoom(maxEnemys[i]->getX() + 4, maxEnemys[i]->getY() + 3);
			}
		}
	}
	//����boss���ӵ�
	if (bossEnemy->isFree() == false)
	{
		if (mPlane->hitObject(bossEnemy->getRec()))
		{
			bossEnemy->getBlood() -= mPlane->bulletHurt;
			//��ײ���ñ�ըЧ��
			setBoom(bossEnemy->getX() + 16, bossEnemy->getY() + 6);
		}
	}
}

void InfiniteGame::collisionEnemyWithPlane()
{
	//����mini
	for (int i = 0; i < MINI_MAX; ++i)
	{
		if (miniEnemys[i]->isFree() == false)
		{
			if (mPlane->getRec().collision(miniEnemys[i]->getRec()))
			{
				//�ж��Ƿ���ս��������ײ
				miniEnemys[i]->getBlood() -= mPlane->hurt;
				mPlane->subBlood(mPlane->hurt);
				//�۳�ս���Լ��л�Ѫ��
				setBoom(miniEnemys[i]->getX()+4, miniEnemys[i]->getY()+3);
			}
		}
	}
	//����max
	for (int i = 0; i < MAX_MAX; ++i)
	{
		if (mPlane->getRec().collision(miniEnemys[i]->getRec()))
		{
			if (mPlane->hitObject(maxEnemys[i]->getRec()))
			{
				//�ж��Ƿ���ս��������ײ
				maxEnemys[i]->getBlood() -= mPlane->hurt;
				mPlane->subBlood(mPlane->hurt);
				//�۳�ս���Լ��л�Ѫ��
				setBoom(maxEnemys[i]->getX()+4, maxEnemys[i]->getY()+3);
			}
		}
	}
	//��boss�ж�
	if (bossEnemy->isFree() == false)
	{
		if (mPlane->getRec().collision(bossEnemy->getRec()))
		{
			//�ж��Ƿ���ս��������ײ
			bossEnemy->getBlood() -= mPlane->hurt;
			mPlane->subBlood(mPlane->hurt);
			//�۳�ս���Լ��л�Ѫ��
			setBoom(bossEnemy->getX()+18, bossEnemy->getY()+6);
		}
	}
}

void InfiniteGame::collisionPlaneWithEnemyBullet()
{
	//�������е��ӵ�
	//����mini�������ӵ�
	for (int i = 0; i < MINI_MAX; ++i)
	{
		//���ú���
		mPlane->subBlood(ENEMY_BULLET_A_HURT * miniEnemys[i]->hitObjectA(mPlane->getRec()));
		mPlane->subBlood(ENEMY_BULLET_B_HURT * miniEnemys[i]->hitObjectB(mPlane->getRec()));
		mPlane->subBlood(ENEMY_BULLET_C_HURT * miniEnemys[i]->hitObjectC(mPlane->getRec()));
		mPlane->subBlood(ENEMY_BULLET_D_HURT * miniEnemys[i]->hitObjectD(mPlane->getRec()));
	}
	//����max�������ӵ�
	for (int i = 0; i < MAX_MAX; ++i)
	{
		//���ú���
		mPlane->subBlood(ENEMY_BULLET_A_HURT * maxEnemys[i]->hitObjectA(mPlane->getRec()));
		mPlane->subBlood(ENEMY_BULLET_B_HURT * maxEnemys[i]->hitObjectB(mPlane->getRec()));
		mPlane->subBlood(ENEMY_BULLET_C_HURT * maxEnemys[i]->hitObjectC(mPlane->getRec()));
		mPlane->subBlood(ENEMY_BULLET_D_HURT * maxEnemys[i]->hitObjectD(mPlane->getRec()));
	}
	//����max�������ӵ�
	mPlane->subBlood(ENEMY_BULLET_A_HURT * bossEnemy->hitObjectA(mPlane->getRec()));
	mPlane->subBlood(ENEMY_BULLET_B_HURT * bossEnemy->hitObjectB(mPlane->getRec()));
	mPlane->subBlood(ENEMY_BULLET_C_HURT * bossEnemy->hitObjectC(mPlane->getRec()));
	mPlane->subBlood(ENEMY_BULLET_D_HURT * bossEnemy->hitObjectD(mPlane->getRec()));
}


void InfiniteGame::paintPause(int select)
{
	//������ͣҳ��
	string sentence;
	sentence = "��ͣ�˵�";
	//����ѡ�������ʾ��Ϣ
	window->paintSentence(PAUSE_X, PAUSE_Y, 0x04, sentence);
	switch (select)
	{
	case 0:
		sentence = "������Ϸ";
		break;
	case 1:
		sentence = "���ز˵�";
		break;
	}
	//����������ʾ��Ϣ
	window->paintSentence(PAUSE1_X, PAUSE1_Y + 2, 0x0F, sentence);
	sentence = " ʹ�����¼�ѡ�� ";
	window->paintSentence(PAUSE2_X, PAUSE2_Y, 0x0F, sentence);
	sentence = "ʹ��Enterȷ��ѡ��";
	window->paintSentence(PAUSE3_X, PAUSE3_Y, 0x0F, sentence);

}

void InfiniteGame::paintOther()
{
	//���Ƶ÷�
	string scoreString = "��ĵ÷�:   "+to_string(score);
	window->paintSentence(SCORE_X, SCORE_Y, 0x06, scoreString);

	//����������ʾ��Ϣ
	string sentence = "ʹ���������Ҽ�����ս��";
	window->paintSentence(GUIDE1_X, GUIDE1_Y, 0x0F, sentence);
    sentence = " ʹ��Esc������ͣ�˵� ";
	window->paintSentence(GUIDE2_X, GUIDE2_Y, 0x0F, sentence);

	//float bloodRate = (float)(mPlane->blood) / PLANE_BLOOD;
	//float bloodWidth = bloodRate * (CHOOSE_WIDTH-2);
	string bloodString = "ս����ǰ�;�ֵ��  " + to_string(mPlane->getBlood());
	window->paintSentence(BLOOD_X, BLOOD_Y, 0x09, bloodString);
}

void InfiniteGame::paintDead()
{
	//�����Ļ���ݷ������
	window->clear_choose();
	window->clear_game();
	//������ʾ��Ϣ
	string sentence = "ս���;�ֵ�ľ����޷�����ս����";
	int paintX = (GAME_WIDTH - (int)sentence.size()) / 2 + 3;
	window->paintSentence(paintX, 15, 0x04, sentence);
	sentence = "�����������......";
	paintX = (GAME_WIDTH - (int)sentence.size()) / 2 + 3;
	window->paintSentence(paintX, 35, 0x0F, sentence);
	window->update();

	//����������˳�
	while (!_kbhit())
		;
	//��ֹ��ɸ���
	cin.ignore();
}

void InfiniteGame::paintBreaking()
{
	//�����Ļ���ݷ������
	window->clear_choose();
	window->clear_game();
	//������ʾ��Ϣ
	string sentence = "����Ա��������ķɻ�׹����";
	int paintX = (GAME_WIDTH - (int)sentence.size()) / 2 + 3;
	window->paintSentence(paintX, 13, 0x03, sentence);
	sentence = "�����ս���ᱻ��¼�ڸ߷ְ���";
	paintX = (GAME_WIDTH - (int)sentence.size()) / 2 + 3;
	window->paintSentence(paintX, 15, 0x03, sentence);
	sentence = "�����������......";
	paintX = (GAME_WIDTH - (int)sentence.size()) / 2 + 3;
	window->paintSentence(paintX, 35, 0x0F, sentence);
	window->update();
	//����������˳�
	while (!_kbhit())
		;
	//��ֹ��ɸ���
	cin.ignore();
}

void InfiniteGame::releaseEnemy()
{
	//���ѡ���ͷ�
	int choose = rand() % 3;
	//�ͷŵл��ļ�ʱ��ˢ�¿����ͷŵл�
	if (enemyReleaseRecorder.update() == false)
		return;
	if (choose == 0)
		//��һ���ͷŵл�
		releaseEnemyI();
	else if(choose==1)
		//�ڶ����ͷŵл�
		releaseEnemyII();
	else
		//�������ͷŵл�
		releaseEnemyIII();
}

void InfiniteGame::releaseEnemyI()
{
	//�ͷ�3��minis
	int minisReleased = 0;
	for (int i = 0; i < MINI_MAX; ++i)
		if (miniEnemys[i]->isFree() == true)
		{
			miniEnemys[i]->setFree(false);
			miniEnemys[i]->reset(rand() % (GAME_WIDTH - MINI_WIDTH) + 2, 4*minisReleased);
			minisReleased++;//��¼�ͷŵ�mini����
			if (minisReleased == 3)
				break;//�ͷ��㹻�˳�
		}
}

void InfiniteGame::releaseEnemyII()
{
	//�ͷ�һ��bos�л�
		for (int i = 0; i < MAX_MAX; ++i)
			if (maxEnemys[i]->isFree() == true)
			{
				maxEnemys[i]->setFree(false);
				maxEnemys[i]->reset(rand() % (GAME_WIDTH - MAX_WIDTH) + 2, 0);
				break;
			}
		//�ͷ�2��minis
		int minisReleased = 0;
		for (int i = 0; i < MINI_MAX; ++i)
			if (miniEnemys[i]->isFree() == true)
			{
				miniEnemys[i]->setFree(false);
				miniEnemys[i]->reset(rand() % (GAME_WIDTH - MINI_WIDTH) + 2, 3*(minisReleased+1));
				if (minisReleased == 2)
					break;//�ͷ��㹻�˳�
			}
}

void InfiniteGame::releaseEnemyIII()
{
	//�ͷ�һ��boss�л�
		if (bossEnemy->isFree() == true)
		{
			bossEnemy->setFree(false);
			bossEnemy->reset(rand() % (GAME_WIDTH - BOSS_WIDTH) + 2, 0);
		}
}

void InfiniteGame::moveAllEnemy()
{
	//����mini�л������ƶ�
	for (int i = 0; i < MINI_MAX; ++i)
		if (miniEnemys[i]->isFree() == false)
		{
			miniEnemys[i]->move();
		}
	//����max�л������ƶ�
	for (int i = 0; i < MAX_MAX; ++i)
		if (maxEnemys[i]->isFree() == false)
		{
			maxEnemys[i]->move();
		}
	//����boss�л��ƶ�
	if (bossEnemy->isFree() == false)
		bossEnemy->move();
}

void InfiniteGame::drawAllEnemy()
{
	//����mini�л����л���
	for (int i = 0; i < MINI_MAX; ++i)
		if (miniEnemys[i]->isFree() == false)
		{
			miniEnemys[i]->draw();
		}
	//����max�л����л���
	for (int i = 0; i < MAX_MAX; ++i)
		if (maxEnemys[i]->isFree() == false)
		{
			maxEnemys[i]->draw();
		}
	//����boss�л�����
	if (bossEnemy->isFree() == false)
		bossEnemy->draw();
}

void InfiniteGame::clearDeadEnemy()
{
	//����mini�л��������
	for (int i = 0; i < MINI_MAX; ++i)
	{
		//�жϵл��Ƿ�����
		if (miniEnemys[i]->isDead())
		{
			//��ʼ���л����ҵ÷�����
			miniEnemys[i]->init();
			score += 10;
		}
	}
	//����max�л����л���
	for (int i = 0; i < MAX_MAX; ++i)
	{
		//�жϵл��Ƿ�����
		if (maxEnemys[i]->isDead())
		{
			//��ʼ���л����ҵ÷�����
			maxEnemys[i]->init();
			score += 30;
		}
	}
	//����boss�л����л���
	if (bossEnemy->isDead())
	{
		//��ʼ���л����ҵ÷�����
		score += 100;

		//����boss�ͷ�buff
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
	//����mini�л���������ӵ�
	for (int i = 0; i < MINI_MAX; ++i)
		if (miniEnemys[i]->isFree() == false)
		{
			miniEnemys[i]->shoot();
		}
	//����max�л���������ӵ�
	for (int i = 0; i < MAX_MAX; ++i)
		if (maxEnemys[i]->isFree() == false)
		{
			maxEnemys[i]->shoot();;
		}
	//����boss�л���������ӵ�
	if (bossEnemy->isFree() == false)
		bossEnemy->shoot();
}

void InfiniteGame::controlEnemyBullet()
{
	//����mini
	for (int i = 0; i < MINI_MAX; ++i)
	{
		//�ƶ��Լ������ӵ�
		miniEnemys[i]->moveAllBullet();
		miniEnemys[i]->drawAllBullet();
	}
	//����max
	for (int i = 0; i < MAX_MAX; ++i)
	{
		//�ƶ��Լ������ӵ�
		maxEnemys[i]->moveAllBullet();
		maxEnemys[i]->drawAllBullet();
	}
	//����max
	{
		//�ƶ��Լ������ӵ�
		bossEnemy->moveAllBullet();
		bossEnemy->drawAllBullet();
	}
}

void InfiniteGame::controlEnemy()
{
	//�����ӵ���Ϊ
	controlEnemyBullet();
	//��������л�
	clearDeadEnemy();
	//�ͷŵл�
	releaseEnemy();
	//�ƶ��л�
	moveAllEnemy();
	//���Ƶл�
	drawAllEnemy();
	//����ӵ�
	shootEnemy();
	//�жϵл��Ƿ�Խ��
	winEnemy();
}

void InfiniteGame::winEnemy()
{
	//�ж��Ƿ��ел�Խ����ͼ
	//����mini��
	for (int i = 0; i < MINI_MAX; ++i)
	{
		if (miniEnemys[i]->isFree()==false&&miniEnemys[i]->getY() == WINDOW_ALL_HEIGHT - 3)
		{
			//�÷ֿ۳�
			score -= 10;
			miniEnemys[i]->destroy();
		}
	}
	//����max��
	for (int i = 0; i < MAX_MAX; ++i)
	{
		if (maxEnemys[i]->isFree() == false && maxEnemys[i]->getY() == WINDOW_ALL_HEIGHT - 3)
		{
			//�÷ֿ۳�
			score -= 20;
			maxEnemys[i]->destroy();
		}
	}
	//���boss��
	if (bossEnemy->isFree() == false && bossEnemy->getY() == WINDOW_ALL_HEIGHT - 3)
	{
		//�÷ֿ۳�
		score -= 50;
		bossEnemy->destroy();
	}
}

void InfiniteGame::releaseBuffs()
{
	//�ͷ�buff�ļ�ʱ��ˢ�¿����ͷ�buff
	if (releaseBuffRecorder.update())
	{
		//���ѡ���ͷ�
		int choose = rand() % 5;
		//��������ͷŵ�����λ��
		int pX = rand() % (GAME_WIDTH - 6);
		BaseBuff* buffPtr=nullptr;
		switch (choose)
		{
		case 0:
			//�ͷŻ�����buff
			buffPtr = new BuffShield(bossEnemy, miniEnemys, maxEnemys, window, mPlane, &score, pX, 4);
			break;
		case 1:
			//�ͷ�������buff
			buffPtr = new BuffInvisible(window, mPlane, &score,  pX, 4);
			break;
		case 2:
			//�ͷŽ�����buff
			buffPtr = new BuffAward(window, mPlane, &score,  pX, 4);
			break;
		case 3:
			//�ͷŲ�����buff
			buffPtr = new BuffAntidote(window, mPlane, &score,  pX, 4);
			break;
		default:
			//�ͷź�ը��buff
			buffPtr = new BuffBoming(bossEnemy, miniEnemys, maxEnemys, window, mPlane, &score, pX, 4);
			break;
		}
		if(buffPtr!=nullptr)
			//���buff
		buffs.push_back(buffPtr);
	}
}

void InfiniteGame::drawBuffs()
{
	//��ÿһ�����ڵ�buff���л���
	for_each(buffs.begin(), buffs.end(), [](BaseBuff* elem) {
		if (elem->Free() == false)
			elem->draw();
		});
}

void InfiniteGame::moveBuffs()
{
	//��ÿһ���ڵ�buff�����ƶ�
	for_each(buffs.begin(), buffs.end(), [](BaseBuff* elem) {
		if (elem->Free() == false)
			elem->move();
		});
}

void InfiniteGame::pickBuffs()
{
	//�ж��Ƿ���buff�ڵ�ͼ�Ͽ��Է���ʰȡ��Ϊ
	for (auto it = buffs.begin(); it != buffs.end(); it++)
	{
		//buff���Ա�ʰȡ
		if ((*it)->Free() == false && (*it)->rec.collision(mPlane->getRec()))
		{
			(*it)->Free() = true;
			//��ʾbuff������Ч��
			(*it)->showInformation();
			//ʹ��buff
			(*it)->use();
		}
	}
}

void InfiniteGame::useBuffs()
{
	//�ж��Ƿ��г�����buff��Ҫʹ��
	for (auto it = buffs.begin(); it != buffs.end(); it++)
	{
		if ((*it)->Free() == true && (*it)->beUsing == true)
			(*it)->use();
	}
}

void InfiniteGame::controlPlane()
{
	//ս������ӵ�
	mPlane->shootBulletA();
	//ս���ƶ��ӵ�
	mPlane->moveBulletA();
	//����ս���ӵ�
	mPlane->drawBulletA();
	//����ս��
	mPlane->paint();
}

void InfiniteGame::deleteBuffs()
{
	//�ж�buff�Ƿ�ʹ����� ����ɾ��
	for (auto it = buffs.begin(); it != buffs.end(); ++it)
	{
		if ((*it)->Free() == true&&(*it)->beUsing==false)
		{
			BaseBuff* tempPtr = (*it);
			buffs.erase(it);
			//������ڶ�������
			delete tempPtr;
			break;
		}
	}
}

void InfiniteGame::controlBuffs()
{
	//�ͷŶ�Ӧ��buff��
	releaseBuffs();
	//�������е�buff��
	drawBuffs();
	//ʰȡ�ִ��buff��
	pickBuffs();
	//�ƶ��ִ��buff��
	moveBuffs();
	//����buff������
	deleteBuffs();
	//ʹ����ʱ��buff
	useBuffs();
}

void InfiniteGame::init()
{
	//�ƶ��ɻ�����ʼλ��
	mPlane->moveTo(PLANE_BEGIN_X, PLANE_BEGIN_Y);
	//��������Ѫ��
	mPlane->setBlood(PLANE_BLOOD);
	//�������÷���
	score = 0;
	//���ñ�ըЧ��
	for (int i = 0; i < BOOM_MAX; ++i)
		booms[i] = new Boom(window);

	for (int i = 0; i < MINI_MAX; ++i)
		miniEnemys[i] = new MiniEnemy(window, config, 0, 0);

	for (int i = 0; i < MAX_MAX; ++i)
		maxEnemys[i] = new MaxEnemy(window, config, 0, 0);

	bossEnemy = new BossEnemy(window, config, 0, 0);
	//������ʱ��
	gameRecorder.start();
	keyboardRecorder.start();
	enemyReleaseRecorder.start();
	enemyMoveRecorder.start();
	releaseBuffRecorder.start();
}

void InfiniteGame::destroy()
{
	//�����ݳ�ʼ��
	init();
	for(int i=0;i<PLANE_BULLETSA_MAX;++i)
		mPlane->destroyBullet(i);
}



