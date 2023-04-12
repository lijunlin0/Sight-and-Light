#include"MPolygon.h"
#include<math.h>

MPolygon::MPolygon(POINT* p, int num,bool is_border)
{
	m_border = is_border;
	m_p = p;
	m_num = num;
	init_point();
}
void MPolygon::draw()
{
	if (m_border)
	{
		return;
	}
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
	std::pair<POINT, POINT> p;
	for (int i = 0; i < m_num; i++)
	{
		if ((i + 1 != m_num))
		{
			p.first= m_p[i];
			p.second=m_p[i + 1];
			v.push_back(p);
		}
		else
		{
			p.first = m_p[i];
			p.second = m_p[0];
			v.push_back(p);
		}
	}
	return v;
}