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

//��ʼ����
void MPolygon::init_point()
{
	for (int i = 0; i < m_num; i++)
	{
		vertex.push_back(m_p[i]);
	}
}

//�õ���
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

//�õ�����
POINT MPolygon::get_intersection_point(std::pair<POINT, POINT> segment)
{
	POINT i;
	return i;
}

/*
1--������Ҫ�ҵ����ߣ�Ҳ�����ǹ��ߣ�������������ͳһ���棩����Щ�߶�֮������Ľ��㡣�κ�һ���߶�������������ʾ��Point + Direction * T

   ���������ǾͿ��Եõ��������ߺ��߶ε��ĸ���ʽ��

    Ray X = r_px + r_dx * T1
    Ray Y = r_py + r_dy * T1
    Segment X = s_px + s_dx * T2
    Segment Y = s_py + s_dy * T2
   ע�⣺�����ǿ�ʼ֮ǰ��Ҫע�������ߺ����Ӧ���߶��Ƿ�ƽ�У�Ҳ���Ƿ����Ƿ���ͬ�����ƽ�У���û�н��㣬���ô���

2--������ǣ����ߺ����Ӧ���߶Σ��ཻ����ô����� X �� Y Ӧ����ȣ�Ҳ���ǣ�

    r_px + r_dx * T1 = s_px + s_dx * T2
    r_py + r_dy * T1 = s_py + s_dy * T2

3--���ǽ�������ķ���ȡ�� T1 �� T2

   �ӵ�ʽ��ȡ�� T1��Ȼ����Ե� T1
   T1 = (s_px+s_dx*T2-r_px)/r_dx = (s_py+s_dy*T2-r_py)/r_dy

   ���߶����� r_dx * r_dy
    s_px*r_dy + s_dx*T2*r_dy - r_px*r_dy = s_py*r_dx + s_dy*T2*r_dx - r_py*r_dx

   ��� T2
    T2 = (r_dx*(s_py-r_py) + r_dy*(r_px-s_px))/(s_dx*r_dy - s_dy*r_dx)

   ���� T2 �õ� T1
   T1 = (s_px+s_dx*T2-r_px)/r_dx
   Ҫȷ�� T1>0 �� 0
*/