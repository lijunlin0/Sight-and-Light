#include"MPolygon.h"

MPolygon::MPolygon(POINT* p, int num)
{
	m_p = p;
	m_num = num;
	init_point();
}
void MPolygon::draw()
{
	setfillcolor(BLUE);
	fillpolygon(m_p, m_num);
}

//初始化点
void MPolygon::init_point()
{
	for (int i = 0; i < m_num; i++)
	{
		vertex.push_back(m_p[i]);
	}
}

//得到边
std::vector<std::pair<POINT, POINT>> MPolygon::get_segments()
{
	std::vector<std::pair<POINT, POINT>> v;
	for (int i = 0; i < m_num; i++)
	{
		if ((i + 1 != m_num))
		{
			v[i].first = m_p[i];
			v[i].second = m_p[i + 1];
		}
		else
		{
			v[i].first = m_p[i];
			v[i].second = m_p[0];
		}
	}
	return v;
}

//得到交点
POINT MPolygon::get_intersection_point(std::pair<POINT, POINT> segment)
{
	POINT i;
	return i;
}

/*
1--我们需要找到视线（也可以是光线，我们用视线来统一代替）和这些线段之间最近的交点。任何一条线都可以这样来表示：Point + Direction * T

   这样，我们就可以得到关于视线和线段的四个等式。

    Ray X = r_px + r_dx * T1
    Ray Y = r_py + r_dy * T1
    Segment X = s_px + s_dx * T2
    Segment Y = s_py + s_dy * T2
   注意：在我们开始之前，要注意检查视线和相对应的线段是否平行，也就是方向是否相同。如果平行，就没有交点，不用处理。

2--如果它们（视线和相对应的线段）相交，那么交点的 X 和 Y 应该相等，也就是：

    r_px + r_dx * T1 = s_px + s_dx * T2
    r_py + r_dy * T1 = s_py + s_dy * T2

3--我们将用下面的方法取得 T1 和 T2

   从等式中取得 T1，然后忽略掉 T1
   T1 = (s_px+s_dx*T2-r_px)/r_dx = (s_py+s_dy*T2-r_py)/r_dy

   两边都乘以 r_dx * r_dy
    s_px*r_dy + s_dx*T2*r_dy - r_px*r_dy = s_py*r_dx + s_dy*T2*r_dx - r_py*r_dx

   解出 T2
    T2 = (r_dx*(s_py-r_py) + r_dy*(r_px-s_px))/(s_dx*r_dy - s_dy*r_dx)

   带入 T2 得到 T1
   T1 = (s_px+s_dx*T2-r_px)/r_dx
   要确保 T1>0 和 0
*/