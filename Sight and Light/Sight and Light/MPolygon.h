#pragma once
#include <graphics.h>
#include<vector>

//ͼ��
class MPolygon
{
private:
	int m_num = 0;
	POINT* m_p;
	//�����
	std::vector<POINT> vertex;
public:
	MPolygon(POINT* p,int num);
	void draw();
	//��ʼ����
	void init_point();
	//�õ���
	std::vector<std::pair<POINT,POINT>> get_segments();
	//�õ�����
	POINT get_intersection_point(std::pair<POINT,POINT> segment);
	//�õ�����
	std::vector<POINT> get_vertex() { return vertex; }
};