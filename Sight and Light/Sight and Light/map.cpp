#include"map.h"
#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;
map::map()
{
	long half_width = WIDTH / 2;
	long half_height = HEIGHT / 2;

	POINT* p1 = new POINT[4]{ {-830,280},{-680,280},{-480,430},{-680,430} };
	MPolygon mp1(p1, 4);
	polygons.push_back(mp1);

	POINT* p2 = new POINT[3]{ {-780,180},{-480,80},{-180,330} };
	MPolygon mp2(p2, 3);
	polygons.push_back(mp2);

	POINT* p3 = new POINT[8]{ {-80,-20},{120,380},{320,380},{120,80},{470,80},{220,-320},{20,-320},{220,-20} };
	MPolygon mp3(p3, 8);
	polygons.push_back(mp3);

	POINT* p4 = new POINT[8]{ {-780,-70},{-680,30},{-580,30},{-530,-70},{-480,30},{-380,30},{-280,-70},{-530,-320} };
	MPolygon mp4(p4, 8);
	polygons.push_back(mp4);

	POINT* p5 = new POINT[3]{ {-205,-170},{-185,80},{-165,-220} };
	MPolygon mp5(p5, 3);
	polygons.push_back(mp5);

	POINT* p6 = new POINT[11]{ {520,-220},{620,-170},{570,-170},{670,-120},{770,-170},{720,-170},{820,-220},{695,-220},{695,-320},{645,-320},{645,-220} };
	MPolygon mp6(p6, 11);
	polygons.push_back(mp6);

	POINT* p7 = new POINT[4]{ {470,355},{870,230},{595,-120},{720,195} };
	MPolygon mp7(p7, 4);
	polygons.push_back(mp7);

	POINT* p8 = new POINT[4]{ {-480,-370},{-405,-295},{-205,-370},{-280,-445} };
	MPolygon mp8(p8, 4);
	polygons.push_back(mp8);

	POINT* p9 = new POINT[3]{ {-155,180},{20,470},{45,330} };
	MPolygon mp9(p9, 3);
	polygons.push_back(mp9);

	POINT* p10 = new POINT[9]{ {270,-470},{345,-345},{370,-395},{405,-335},{420,-385},{465,-300},{495,-370},{565,-295},{545,-405} };
	MPolygon mp10(p10, 9);
	polygons.push_back(mp10);

	POINT* p11 = new POINT[5]{ {220,130},{395,255},{595,215},{520,55},{415,165} };
	MPolygon mp11(p11, 5);
	polygons.push_back(mp11);

	POINT* p12 = new POINT[4]{ {-half_width,half_height} ,{half_width ,half_height}, {half_width, -half_height}, { -half_width,-half_height} };

	MPolygon mp12(p12, 4,true);
	polygons.push_back(mp12);
}

void map::update_mouse_segments()
{	
	//传入起点和角度返回终点
	auto get_point = [](const POINT& point, double angle) -> POINT
	{
		if (angle < 0)
		{
			angle += 360;
		}
		POINT E;
		int factor = angle >= 90 && angle < 270 ? -1 : 1;

		double radian = angle / 180 * 3.1415926;
		E.x = point.x + factor*2000;
		E.y = point.y + tan(radian) *factor* 2000;
		return E;
	};
	
	//传入两个点返回角度
	auto get_angle = [](const POINT& point1, const POINT& point2) -> double
	{
		double dx = point2.x - point1.x;
		double dy = point2.y - point1.y;
		double radian= atan2(dy, dx);
		return radian / 3.1415926 * 180;
		
	};

	auto comp = [&](const POINT& point1, const POINT& point2) -> bool
	{
		double angle_1 = get_angle(mouse_point, point1);
		double angle_2 = get_angle(mouse_point, point2);
		return angle_1 < angle_2;
	};

	polygon_points.clear();
	//遍历每个图形
	for (int i = 0; i < polygons.size(); i++)
	{
		//遍历每个图形的顶点
		for (int j = 0; j < polygons[i].get_point().size(); j++)
		{
			polygon_points.push_back(polygons[i].get_point()[j]);
		}
	}
	sort(polygon_points.begin(), polygon_points.end(), comp);

	mouse_segments.clear();
	std::pair<POINT, POINT> p;

	for (int i = 0; i<polygon_points.size(); i++)
	{
		double angle = get_angle(mouse_point, polygon_points[i]);
		POINT E = get_point(mouse_point, angle-0.001);
		p.first = mouse_point;
		p.second = E;
		mouse_segments.push_back(p);

		p.first = mouse_point;
		p.second = polygon_points[i];
		mouse_segments.push_back(p);

		E = get_point(mouse_point, angle + 0.001);
		p.first = mouse_point;
		p.second = E;
		mouse_segments.push_back(p);
	}
}
//得到交点
POINT map::get_intersection_point(std::pair<POINT, POINT> mouse_segment, std::pair<POINT, POINT> segment)
{
	double mod1 = segment_length(mouse_segment);
	double d1_x = (mouse_segment.second.x - mouse_segment.first.x) / mod1;
	double d1_y = (mouse_segment.second.y - mouse_segment.first.y) / mod1;
	double mod2 = segment_length(segment);
	double d2_x = (segment.second.x - segment.first.x) / mod2;
	double d2_y = (segment.second.y - segment.first.y) / mod2;

	double a = (d2_x * d1_y - d2_y * d1_x);
	if (a == 0)
	{
		return mouse_segment.second;
	}
	double T2 = (d1_x * (segment.first.y - mouse_segment.first.y) + d1_y * (mouse_segment.first.x - segment.first.x)) / a;
	double T1 = (segment.first.x + d2_x * T2 - mouse_segment.first.x) / d1_x;
	if (T1 > 0 && T1 < mod1 && T2>0 && T2 < mod2)
	{
		POINT E;
		E.x = mouse_segment.first.x + d1_x * T1;
		E.y = mouse_segment.first.y + d1_y * T1;
		return E;
	}
	else
	{
		return mouse_segment.second;
	}
}

double map::segment_length(std::pair<POINT, POINT> segment)
{
	return sqrt((segment.first.x - segment.second.x)*(segment.first.x - segment.second.x) + (segment.first.y - segment.second.y)* (segment.first.y - segment.second.y));
}

void map::draw(ExMessage msg)
{
	update_mouse_segments();
	//填充颜色
	setfillcolor(CYAN);
	//线段颜色
	setlinecolor(BLACK);
	setfillcolor(BLUE);
	//遍历图形
	for (int i = 0; i < polygons.size(); i++)
	{
		//画图形
		polygons[i].draw();
	}
	POINT min_p;
	//遍历光源到顶点的边
	for (int k = 0; k < mouse_segments.size(); k++)
	{
		double min_length = segment_length(mouse_segments[k]);
		min_p.x = mouse_segments[k].second.x;
		min_p.y = mouse_segments[k].second.y;
		//遍历图形
		for (int i = 0; i < polygons.size(); i++)
		{
			//遍历图形对应的边
			vector<pair<POINT, POINT>> segments = polygons[i].get_segments();
			for (int j = 0; j < segments.size(); j++)
			{
				POINT e = get_intersection_point(mouse_segments[k], segments[j]);
				std::pair<POINT, POINT> L;
				L.first = mouse_segments[k].first;
				L.second = e;
				double length = segment_length(L);
				if (min_length >length)
				{
					min_length = length;
					min_p = e;
				}
			}
		}
		mouse_segments[k].second = min_p;
		setlinecolor(GREEN);
		line(mouse_segments[k].first.x, mouse_segments[k].first.y, mouse_segments[k].second.x , mouse_segments[k].second.y);
	}
	
	int size = mouse_segments.size();
	POINT* p = new POINT[size];
	for (int i = 0; i <size;i++)
	{
		p[i] = mouse_segments[i].second; 
	}
	MPolygon polygon(p, size);

	setfillcolor(GREEN);
	polygon.draw();
	/*line(msg.x, msg.y, 50, 200);	line(msg.x, msg.y, 200, 200);	line(msg.x, msg.y, 400, 50); line(msg.x, msg.y, 200, 50); 
	line(msg.x, msg.y, 100, 300);	line(msg.x, msg.y, 400, 400);	line(msg.x, msg.y, 700, 150);
	line(msg.x, msg.y, 800, 500);	line(msg.x, msg.y, 1000, 100);	line(msg.x, msg.y, 1200, 100);	line(msg.x, msg.y, 1000, 400);	line(msg.x, msg.y, 1350, 400);	line(msg.x, msg.y, 1100, 800); line(msg.x, msg.y, 900, 800); line(msg.x, msg.y, 1100, 500);
	line(msg.x, msg.y, 100, 550);	line(msg.x, msg.y, 200, 450);	line(msg.x, msg.y, 300, 450);	line(msg.x, msg.y, 350, 550);	line(msg.x, msg.y, 400, 450);	line(msg.x, msg.y, 500, 450);	line(msg.x, msg.y, 600, 550);	line(msg.x, msg.y, 350, 800);
	*/
}