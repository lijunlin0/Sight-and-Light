#pragma once
#include <graphics.h>
#include<vector>

//ͼ��
class MPolygon
{
private:
	int m_num = 0;
	POINT* m_p;
	bool m_border;
	//�����
	std::vector<POINT> vertex;
	//��ʼ����
	void init_point();
public:
	MPolygon(POINT* p,int num,bool is_border=false);
	void draw();
	//�õ���
	std::vector<std::pair<POINT,POINT>> get_segments();
	//�õ�����
	std::vector<POINT> get_point() { return vertex; }
};