//Rec.h
//log:2022/6/3
//Rec��Ķ���

#ifndef REC_H
#define REC_H

//������
class Rec
{
public:
	//���캯��
	Rec(int x=0,int y=0,int width=0,int height=0);

	//�жϾ���֮���Ƿ���ײ����
	bool collision(Rec& rhs);

	//�������þ��ε�����λ��
	void reset(int x, int y);
private:
	//����λ��
	int x;
	int y;
	//���μ�����Ϣ
	int width;
	int height;
};

#endif

