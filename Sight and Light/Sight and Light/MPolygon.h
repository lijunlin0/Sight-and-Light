#pragma once
#include <graphics.h>
#include<vector>

//图形
class MPolygon
{
private:
	int m_num = 0;
	POINT* m_p;
	bool m_border;
	//顶点表
	std::vector<POINT> vertex;
	//初始化点
	void init_point();
public:
	MPolygon(POINT* p,int num,bool is_border=false);
	void draw();
	//得到边
	std::vector<std::pair<POINT,POINT>> get_segments();
	//得到顶点
	std::vector<POINT> get_point() { return vertex; }
};