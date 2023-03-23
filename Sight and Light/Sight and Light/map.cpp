#include"map.h"
#include<iostream>

using namespace std;
map::map()
{
	//四边形
	POINT* p1 =new POINT[4] { {50, 200}, {200, 200},{400,50},{200, 50} };
	MPolygon mp1(p1, 4);
	polygons.push_back(mp1);


	//三角形
	POINT* p2 = new POINT[3]{ {100, 300}, {400, 400},{700,150} };
	MPolygon mp2(p2, 3);
	polygons.push_back(mp2);

	//闪电形
	POINT* p3 = new POINT[8]{ {800, 500}, {1000, 100},{1200,100},{1000,400},{1350,400},{1100,800},{900,800},{1100,500} };
	MPolygon mp3(p3, 8);
	polygons.push_back(mp3);

	//爱心形
	POINT* p4 = new POINT[8]{ {100, 550}, {200, 450},{300,450},{350,550},{400,450},{500,450},{600,550},{350,800} };
	MPolygon mp4(p4, 8);
	polygons.push_back(mp4);

	//三角形
	POINT* p5 = new POINT[3]{ {675, 650}, {695, 400},{715,700} };
	MPolygon mp5(p5, 3);
	polygons.push_back(mp5);

	//树形
	POINT* p6 = new POINT[11]{ {1400, 700}, {1500, 650},{1450,650},{1550, 600}, {1650, 650},{1600,650},{1700, 700}, {1575, 700},{1575,800},{1525, 800}, {1525, 700} };
	MPolygon mp6(p6, 11);
	polygons.push_back(mp6);

	//飞镖形
	POINT* p7 = new POINT[4]{ {1350, 125}, {1750, 250},{1475,600},{1600,285} };
	MPolygon mp7(p7, 4);
	polygons.push_back(mp7);

	//平行四边形
	POINT* p8 = new POINT[4]{ {400, 850}, {475, 775},{675,850},{600,925} };
	MPolygon mp8(p8, 4);
	polygons.push_back(mp8);

	//三角形
	POINT* p9 = new POINT[3]{ {725, 300}, {900, 10},{925,150} };
	MPolygon mp9(p9, 3);
	polygons.push_back(mp9);

	//尖刺形
	POINT* p10 = new POINT[9]{ {1150, 950}, {1225, 825},{1250,875},{1285,815},{1300, 865}, {1345, 780},{1375,850},{1445,775},{1425,885} };
	MPolygon mp10(p10, 9);
	polygons.push_back(mp10);

	//手柄形
	POINT* p11 = new POINT[5]{ {1100, 350}, {1275, 225},{1475,265},{1400,425},{1295,315} };
	MPolygon mp11(p11, 5);
	polygons.push_back(mp11);
		init_mouse_segments();
}


void map::init_mouse_segments()
{	
	std::pair<POINT, POINT> p;
	for (int i = 0; i < polygons.size(); i++)
	{
		cout << "加入成功" << endl;
		for (int j = 0; j<polygons[i].get_point().size(); j++)
		{

			p.first = mouse_point;
			p.second = polygons[i].get_point()[j];
			mouse_segments.push_back(p);
		}
	}
}
//得到交点
POINT map::get_intersection_point(std::pair<POINT, POINT> mouse_segment, std::pair<POINT, POINT> segment)
{
	//创建方向向量
	POINT d1, d2;
	double mod1 = sqrt((mouse_segment.first.x - mouse_segment.second.x)*(mouse_segment.first.x - mouse_segment.second.x) + (mouse_segment.first.y - mouse_segment.second.y)* (mouse_segment.first.y - mouse_segment.second.y));
	d1.x = (mouse_segment.second.x - mouse_segment.first.x) / mod1;
	d1.y = mouse_segment.second.y - mouse_segment.first.y / mod1;
	double mod2 = sqrt((segment.first.x - segment.second.x) * (segment.first.x - segment.second.x) + (segment.first.y - segment.second.y) * (segment.first.y - segment.second.y));
	d2.x = (segment.second.x - segment.first.x) / mod2;
	d2.y = (segment.second.y - segment.first.y) / mod2;

	double a = (d2.x * d1.y - d2.y * d1.x);

	double T2 = (d1.x * (segment.first.y - mouse_segment.first.y) + d1.y * (mouse_segment.first.x - segment.first.x)) / a ;
	double T1 = (segment.first.x + d2.x * T2 - mouse_segment.first.x) / d1.x;
	if (T1 > 0 && T1 < mod1 && T2>0 && T2 < mod2)
	{
		POINT E;
		E.x = segment.first.x + d2.x * T2;
		E.y = segment.first.y + d2.y * T2;
		return E;
	}
	else
	{
		return mouse_segment.second;
	}
}

void map::draw(ExMessage msg)
{
	//填充颜色
	setfillcolor(CYAN);
	//线段颜色
	setlinecolor(BLACK);
	//遍历图形
	for (int i = 0; i < polygons.size(); i++)
	{
		//画图形
		polygons[i].draw();
		//遍历图形对应的边
		vector<pair<POINT, POINT>> segments = polygons[i].get_segments();
		for (int j = 0; j < segments.size(); j++)
		{
			//遍历光源到顶点的边
			for (int k = 0; k < mouse_segments.size(); k++)
			{
				POINT e = get_intersection_point(mouse_segments[k], segments[j]);
				line(mouse_point.x, mouse_point.y, e.x, e.y);
			}
		}
	}

	/*line(msg.x, msg.y, 50, 200);	line(msg.x, msg.y, 200, 200);	line(msg.x, msg.y, 400, 50); line(msg.x, msg.y, 200, 50); 
	line(msg.x, msg.y, 100, 300);	line(msg.x, msg.y, 400, 400);	line(msg.x, msg.y, 700, 150);
	line(msg.x, msg.y, 800, 500);	line(msg.x, msg.y, 1000, 100);	line(msg.x, msg.y, 1200, 100);	line(msg.x, msg.y, 1000, 400);	line(msg.x, msg.y, 1350, 400);	line(msg.x, msg.y, 1100, 800); line(msg.x, msg.y, 900, 800); line(msg.x, msg.y, 1100, 500);
	line(msg.x, msg.y, 100, 550);	line(msg.x, msg.y, 200, 450);	line(msg.x, msg.y, 300, 450);	line(msg.x, msg.y, 350, 550);	line(msg.x, msg.y, 400, 450);	line(msg.x, msg.y, 500, 450);	line(msg.x, msg.y, 600, 550);	line(msg.x, msg.y, 350, 800);
	*/
}