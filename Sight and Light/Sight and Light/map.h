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
	//光源到顶点的边
	std::vector<std::pair<POINT, POINT>> mouse_segments;
	//鼠标位置
	POINT mouse_point;
	std::vector<POINT> polygon_points;
public:
	map();
	//计算线的长度
	double segment_length(std::pair<POINT, POINT> segment);
	//得到交点
	POINT get_intersection_point(std::pair<POINT, POINT> mouse_segment, std::pair<POINT, POINT> segment);
	//画图形
	void draw(ExMessage msg);
	//设置鼠标位置
	void set_mouse_point(ExMessage msg) { mouse_point.x = msg.x; mouse_point.y = msg.y; };
	//初始化光源到顶点的边
	void update_mouse_segments();
};
