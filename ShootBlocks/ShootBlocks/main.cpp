#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include<Windows.h>
#include<math.h>
typedef struct rect
{
	int x;
	int y;
}DataType;
#include "List.h"
#define WIDTH 640
#define HEIGHT 480
char ch;
SLNode *head;
int radius = 25;
int vx_ball = 1, vy_ball = 1;
int rect_x = 240;
int rect_direction = 1;
int x_pos = rand()%640 + 1;
int y_pos = rand()%480 + 1;
int x, y;
int c = 100, con = 1;
void AppendRect()
{
	for (int i = ListLength(head); i < 4; i++)
	{
		DataType newRect;
		newRect.x = rand()%360 + 1;
		newRect.y = rand()%260 + 1;
		while (true)
		{
			int judge = 1;
			if (ListLength(head) == 0 )
			{
				break;
			}
			for (int j = 0; j < ListLength(head); j++)
			{
				DataType value;
				ListGet(head, j, &value);
				if (sqrt(abs(double(pow(value.x - newRect.x/1.0,2) - pow(value.y - newRect.y/1.0,2)))) < 120)
				{
					judge = 0;
					break;
				}
			}
			if (judge)
			{
				break;
			}
			newRect.x = rand()%360 + 1;
			newRect.y = rand()%260 + 1;
		}
		ListInsert(head, i, newRect);
	}
}
void displayRect()
{
	for (int i = 0; i < ListLength(head); i++)
	{
		DataType Rect;
		ListGet(head, i, &Rect);
		setfillcolor(BLUE);
		solidrectangle(Rect.x, Rect.y, Rect.x + 120, Rect.y + 36);
	}
}
void MoveSphere()
{
	setfillcolor(BLACK);
	solidcircle(x_pos, y_pos, radius);
	setfillcolor(WHITE);
	solidcircle(x_pos += vx_ball, y_pos += vy_ball, radius);
	FlushBatchDraw();
	Sleep(5);
	if (x_pos >= WIDTH - radius)
	{
		vx_ball = -1;
	}
	if (x_pos <= radius)
	{
		vx_ball = 1;
	}
	if (y_pos >= HEIGHT - radius || (y_pos == 460 - radius && x_pos >= rect_x && x_pos <= rect_x + 160))
	{
		vy_ball = -1;
	}
	if (y_pos <= radius)
	{
		vy_ball = 1;
	}
}
void DisplayRedRect()
{
	BeginBatchDraw();
	setfillcolor(BLACK);
	solidrectangle(rect_x-rect_direction, 460, rect_x + 160 - rect_direction, 480);
	setfillcolor(RGB(c, 0, 0));
	if (c == 255)
	{
		con = -1;
	}
	if (c == 100)
	{
		con = 1;
	}
	c += con;
	solidrectangle(rect_x, 460, rect_x+160,480);
	FlushBatchDraw();
	Sleep(5);
}
void RemoveInvalidRect()
{
	for (int i = 0; i < ListLength(head); i++)
	{
		int flag = 1;
		DataType value;
		ListGet(head, i, &value);
		if (x_pos >= value.x - radius && x_pos <= value.x + 120 + radius && y_pos >= value.y && y_pos <= value.y + 36)
		{
			flag = 0;
		}
		if (y_pos >= value.y - radius && y_pos <= value.y + 36 + radius && x_pos >= value.x && x_pos <= value.x + 120)
		{
			flag = 0;
		}
		if (!flag)
		{
			setfillcolor(BLACK);
			solidrectangle(value.x, value.y, value.x + 120, value.y + 36);
			ListDelete(head, i);
			AppendRect();
		}
	}
}
void ControlRedRect()
{
	if (kbhit())
	{
		ch = getch();
		switch(ch)
		{
			case 'a':
				rect_direction = -20;
				if (rect_x + rect_direction >= 0)
				{
					rect_x += rect_direction ;
				}
				break;
			case 'd': 
				rect_direction = 20;
				if (rect_x + rect_direction <= 480)
				{
					rect_x += rect_direction ;
				}
				break;
		}
	}
}
int main()
{
	initgraph(WIDTH, HEIGHT);
	srand((unsigned int)time(0));
	ListInitiate(&head);
	//产生敌人，复用性高
	AppendRect();
	while (true)
	{
		//画出敌人，复用性高
		displayRect();
		BeginBatchDraw();
		//移动球，复用性高
		MoveSphere();
		//画出红板，复用性高
		DisplayRedRect();
		//清除无效蓝块，复用性高
		RemoveInvalidRect();
		//控制红块，复用性高
		ControlRedRect();
	}
	_getch();
	closegraph();
	return 0;
}