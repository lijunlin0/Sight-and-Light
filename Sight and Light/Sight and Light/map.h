#pragma once
#include <graphics.h>
#include <conio.h>
#include"MPolygon.h"
#include<vector>

class map
{
private:
	//ͼ��
	std::vector<MPolygon> polygons;
	//��Դ������ı�
	std::vector<std::pair<POINT, POINT>> mouse_segments;
	//���λ��
	POINT mouse_point;
	std::vector<POINT> polygon_points;
public:
	map();
	//�����ߵĳ���
	double segment_length(std::pair<POINT, POINT> segment);
	//�õ�����
	POINT get_intersection_point(std::pair<POINT, POINT> mouse_segment, std::pair<POINT, POINT> segment);
	//��ͼ��
	void draw(ExMessage msg);
	//�������λ��
	void set_mouse_point(ExMessage msg) { mouse_point.x = msg.x; mouse_point.y = msg.y; };
	//��ʼ����Դ������ı�
	void update_mouse_segments();
};
