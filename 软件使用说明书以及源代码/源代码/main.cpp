//main.cpp
//log:2022/6/3
//源文件

#include"WindowSetter.h"
#include"MainControl.h"

int main()
{
	//声明窗口设置对象 对窗口进行写入
	WindowSetter* windowSetter=new WindowSetter;
	//声明主控制对象 飞机大战游戏 并进行初始化
	MainControl planeWar(windowSetter);
}

//#include"ScoreFileRecord.h"
//#include"WindowSetter.h"
//#include"HistoryScoreRecord.h"
//using namespace std;
//int main()
//{
//	WindowSetter window;
//	ScoreFileRecord fielHelper;
//	HistoryScoreRecord record(&window, &fielHelper);
//	record.showHighestScore();
//}