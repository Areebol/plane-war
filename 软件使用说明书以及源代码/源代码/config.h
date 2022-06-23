//config.h
//log:2022/6/3
//配置文件的配置参数的宏定义

#ifndef CONFIG_H
#define CONFIG_H

#include<string>
#include<Windows.h>

using std::string;

//配置数据-----------------------------------------------------------------------

//对窗口数据配置 ----------------------------------------------------------------
//选择区域的宽度
#define CHOOSE_WIDTH  30 
//区域高度
#define WINDOW_HEIGHT 40 
//游戏宽度
#define GAME_WIDTH 60
//窗口几何大小信息
#define WINDOW_ALL_HEIGHT WINDOW_HEIGHT+6 
#define WINDOW_ALL_WIDTH GAME_WIDTH + CHOOSE_WIDTH + 6 

//对游戏数据配置
#define GAME_RATE 10 //游戏速度
#define LEVEL_MAX 3 //游戏难度的最大选择数量


//对提示信息的数据配置-----------------------------------------------------------
//分数绘制坐标
#define SCORE_X  GAME_WIDTH+4+8 
#define SCORE_Y  3+12

#define BLOOD_X GAME_WIDTH+4+4
#define BLOOD_Y 3+8
//提示1坐标
#define GUIDE1_X GAME_WIDTH+4+4
#define GUIDE1_Y 3+20
//提示2坐标
#define GUIDE2_X GAME_WIDTH+4+4
#define GUIDE2_Y 3+25
//设置子弹提示1坐标
#define GUIDE1_SET_BULLET_X GAME_WIDTH+4+6
#define GUIDE1_SET_BULLET_Y 3+15
//设置子弹提示2坐标
#define GUIDE2_SET_BULLET_X GAME_WIDTH+4+6
#define GUIDE2_SET_BULLET_Y 3+20
//设置难度提示1坐标
#define GUIDE1_SET_LEVEL_X 2+25
#define GUIDE1_SET_LEVEL_Y 3+15
//设置难度提示2坐标
#define GUIDE2_SET_LEVEL_X 2+25 
#define GUIDE2_SET_LEVEL_Y 3+20
//标题坐标1
#define TITLE1_X 2+26
#define TITLE1_Y 3+5
//标题坐标2
#define TITLE2_X 2+17
#define TITLE2_Y 3+15
//标题坐标3
#define TITLE3_X 2+17
#define TITLE3_Y 3+20
//暂停标题坐标
#define PAUSE_X 2+26
#define PAUSE_Y 3+13
//暂停1坐标
#define PAUSE1_X  2+26
#define PAUSE1_Y  3+18
//暂停2坐标
#define PAUSE2_X GAME_WIDTH+4+6
#define PAUSE2_Y 3+15
//暂停3坐标
#define PAUSE3_X GAME_WIDTH+4+6
#define PAUSE3_Y 3+20







//爆炸效果数据配置-------------------------------------------------------------
//爆炸间隔
#define BOOM_INTERVAL 1
//爆炸最大数量
#define BOOM_MAX 15

//文本颜色属性配置
#define COLOR_REGULAR 0x0F
#define COLOR_WHOLE_GREEN 0x22
#define COLOR_WHOLE_BLACK 0x00
#define COLOR_WHITE_BLACK 0xF0

//主窗口按钮信息配置-----------------------------------------------------------
#define MAIN_BUTTON_MAX 4
#define MAIN_BUTTON1 " 无尽模式 "
#define MAIN_BUTTON2 " 游戏设置 "
#define MAIN_BUTTON3 " 退出游戏 "
#define MAIN_BUTTON4 " 历史高分 "
#define MAIN_BUTTON1_X GAME_WIDTH+4+8
#define MAIN_BUTTON2_X GAME_WIDTH+4+8
#define MAIN_BUTTON3_X GAME_WIDTH+4+8
#define MAIN_BUTTON4_X GAME_WIDTH+4+8
#define MAIN_BUTTON1_Y 3+12
#define MAIN_BUTTON2_Y 3+15
#define MAIN_BUTTON3_Y 3+21
#define MAIN_BUTTON4_Y 3+18
#define MAIN_BUTTON_FLASH_RATE 100

//设置窗口按钮信息配置------------------------------------------------------------
#define SET_BUTTON_MAX 3
#define SET_BUTTON1 " 选择子弹 "
#define SET_BUTTON2 " 选择难度 "
#define SET_BUTTON3 " 返回菜单 "
#define SET_BUTTON1_X GAME_WIDTH+4+8
#define SET_BUTTON2_X GAME_WIDTH+4+8
#define SET_BUTTON3_X GAME_WIDTH+4+8
#define SET_BUTTON1_Y 3+12
#define SET_BUTTON2_Y 3+15
#define SET_BUTTON3_Y 3+18
#define SET_BUTTON_FLASH_RATE 100


//对键盘读取信息配置
#define KEYBOARD_RATE 50
#endif
