//Rec.h
//log:2022/6/3
//Rec类的定义

#ifndef REC_H
#define REC_H

//矩形类
class Rec
{
public:
	//构造函数
	Rec(int x=0,int y=0,int width=0,int height=0);

	//判断矩形之间是否碰撞函数
	bool collision(Rec& rhs);

	//重新设置矩形的坐标位置
	void reset(int x, int y);
private:
	//坐标位置
	int x;
	int y;
	//矩形几何信息
	int width;
	int height;
};

#endif

