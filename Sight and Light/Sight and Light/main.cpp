#include <graphics.h>
#include <conio.h>
#include<iostream>
#include<windows.h>
#include"map.h"
#include"time.h"
using namespace std;

long long time::update_ms = 0;
//窗口宽高
static const int WIDTH = 1760;
static const int HEIGHT = 960;

int main()
{
	initgraph(WIDTH, HEIGHT);
	map m;
	ExMessage msg;//创建消息变量
	while (true)
	{
		getmessage(&msg, EX_MOUSE);
		long long current = time::current_time();
		if (current - time::update_ms < time::frame_ms)
		{
			continue;
		}
		time::update_ms = current;

		BeginBatchDraw();

		//清屏
		setfillcolor(WHITE);
		solidrectangle(0, 0, WIDTH, HEIGHT);
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