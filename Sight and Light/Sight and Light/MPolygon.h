#pragma once
#include <graphics.h>
#include<vector>

//图形
class MPolygon
{
private:
	int m_num = 0;
	POINT* m_p;
	//顶点表
	std::vector<POINT> vertex;
public:
	MPolygon(POINT* p,int num);
	void draw();
	//初始化点
	void init_point();
	//得到边
	std::vector<std::pair<POINT,POINT>> get_segments();
	//得到交点
	POINT get_intersection_point(std::pair<POINT,POINT> segment);
	//得到顶点
	std::vector<POINT> get_vertex() { return vertex; }
};