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
	//��
	std::vector<std::pair<POINT, POINT>> mouse_segments;
public:
	map();
	//��һ��ͼ�ε���
	void draw_line(std::vector<POINT> v,ExMessage msg);
	//��ͼ��
	void draw(ExMessage msg);
};
