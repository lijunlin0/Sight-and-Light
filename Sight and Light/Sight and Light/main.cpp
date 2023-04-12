#include <graphics.h>
#include <conio.h>
#include<iostream>
#include<windows.h>
#include"map.h"
#include"time.h"
using namespace std;

//鼠标坐标转换
void set_msg(ExMessage* msg)
{
	if (msg->x < map::WIDTH / 2)
	{
		msg->x = -(map::WIDTH / 2 - msg->x);
	}
	else
	{
		msg->x = msg->x - map::WIDTH / 2;
	}
	if (msg->y > map::HEIGHT / 2)
	{
		msg->y = -(msg->y - map::HEIGHT / 2);
	}
	else
	{
		msg->y = map::HEIGHT / 2 - msg->y;
	}
}
long long time::update_ms = 0;

int main()
{
	initgraph(map::WIDTH, map::HEIGHT,SHOWCONSOLE);

	map m;
	ExMessage msg;//创建消息变量
	setorigin(map::WIDTH/2,map::HEIGHT/2);
	setaspectratio(1, -1);
	while (true)
	{
		getmessage(&msg, EX_MOUSE);
		set_msg(&msg);
		m.set_mouse_point(msg);
		long long current = time::current_time();
		if (current - time::update_ms < time::frame_ms)
		{
			continue;
		}
		time::update_ms = current;

		BeginBatchDraw();

		//清屏
		setfillcolor(WHITE);
		solidrectangle(-map::WIDTH/2,-map::HEIGHT/2, map::WIDTH/2, map::HEIGHT/2);
		//画障碍
		m.draw(msg);
		//画光源
		setfillcolor(BLACK);
		solidcircle(msg.x, msg.y, 8);

		EndBatchDraw();
	}
	system("pause");
	return 0;
}