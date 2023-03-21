#pragma once
#include <graphics.h>
#include <conio.h>
#include"MPolygon.h"
#include<vector>

class map
{
private:
	//图形
	std::vector<MPolygon> polygons;
	//边
	std::vector<std::pair<POINT, POINT>> mouse_segments;
public:
	map();
	//画一个图形的线
	void draw_line(std::vector<POINT> v,ExMessage msg);
	//画图形
	void draw(ExMessage msg);
};
