/**
 * @file draw.cpp
 * @author Wen Yanqiu
 * @brief 
 * @version 0.1
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include"draw.h"


void draw_quit_coin(int x, int y)
{
	setcolor(_BLACK);
	setlinestyle(0, 0, 3);
	rectangle(x, y, x + 60, y + 60);	  // 外框
	line(x + 10, y + 10, x + 40, y + 10); // 半包围框
	line(x + 10, y + 50, x + 40, y + 50);
	line(x + 10, y + 10, x + 10, y + 50);
	line(x + 40, y + 15, x + 40, y + 45); // 三角
	line(x + 40, y + 15, x + 50, y + 30);
	line(x + 40, y + 45, x + 50, y + 30);

	setfillstyle(1, _BLACK);
	bar(x + 20, y + 20, x + 40, y + 40);
	//floodfill(x + 45, y + 30, _BLACK);
}

void draw_photo_coin(int x, int y)
{
	setfillstyle(1, _DARKRED);
	fillellipse(x + 39, y + 19, 7, 7);

	setcolor(_DARKGREEN);
	setlinestyle(0, 0, 3);
	line(x + 7, y + 55, x + 25, y + 33);
	line(x + 25, y + 33, x + 35, y + 45);
	line(x + 28, y + 48, x + 39, y + 30);
	line(x + 39, y + 30, x + 55, y + 55);
	line(x + 7, y + 55, x + 55, y + 55);

	setcolor(_DARKGREEN);
	setfillstyle(1, _DARKGREEN);
	//floodfill(x + 40, y + 53, _DARKGREEN);
}

void draw_task_coin(int x, int y)
{
	setcolor(_BLACK);
	setlinestyle(0, 0, 3);
	rectangle(x, y, x + 60, y + 60);
	rectangle(x + 5, y + 7, x + 25, y + 27);
	rectangle(x + 5, y + 33, x + 25, y + 53);
	line(x + 28, y + 27, x + 55, y + 27);
	line(x + 28, y + 53, x + 55, y + 53);
}

void draw_private_coin(int x, int y)
{
	setcolor(_BLACK);
	setlinestyle(0, 0, 3);
	rectangle(x + 3, y + 6, x + 23, y + 19);
	line(x + 3, y + 6, x + 10, y + 13);
	line(x + 3, y + 19, x + 10, y + 13);
	line(x + 23, y + 6, x + 16, y + 13);
	line(x + 23, y + 19, x + 16, y + 13);
	line(x + 10, y + 13, x + 16, y + 13);
}

void draw_public_coin(int x, int y)
{
	setcolor(_BLACK);
	setlinestyle(0, 0, 3);
	line(x + 3, y + 9, x + 3, y + 21);
	line(x + 23, y + 9, x + 23, y + 21);
	line(x + 3, y + 21, x + 23, y + 21);
	line(x + 3, y + 9, x + 10, y + 15);
	line(x + 3, y + 21, x + 10, y + 15);
	line(x + 23, y + 9, x + 16, y + 15);
	line(x + 23, y + 21, x + 16, y + 15);
	line(x + 10, y + 15, x + 16, y + 15);
	line(x + 3, y + 9, x + 13, y + 4);
	line(x + 23, y + 9, x + 13, y + 4);
}

void draw_new_coin(int x, int y)
{
	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	line(x + 2, y + 3, x + 2, y + 15);
	line(x + 2, y + 3, x + 14, y + 3);
	line(x + 14, y + 3, x + 9, y + 6);
	line(x + 9, y + 6, x + 14, y + 9);
	line(x + 2, y + 9, x + 14, y + 9);
}

void draw_save_coin(int x, int y)
{
	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	rectangle(x + 1, y + 1, x + 15, y + 15);
	rectangle(x + 4, y + 1, x + 12, y + 5);
	rectangle(x + 4, y + 9, x + 12, y + 15);
}

void draw_delete_coin(int x, int y)
{
	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	rectangle(x + 1, y + 1, x + 15, y + 15);
	line(x + 1, y + 1, x + 15, y + 15);
}

void draw_refresh_coin(int x, int y)
{
	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	line(x + 2, y + 4, x + 2, y + 9);
	line(x + 2, y + 4, x + 14, y + 4);
	line(x + 14, y + 4, x + 12, y + 2);
	line(x + 14, y + 4, x + 12, y + 6);

	line(x + 14, y + 7, x + 14, y + 12);
	line(x + 14, y + 12, x + 2, y + 12);
	line(x + 2, y + 12, x + 4, y + 10);
	line(x + 2, y + 12, x + 4, y + 14);
}

void draw_share_coin(int x, int y)
{
	setcolor(_BLACK);
	setfillstyle(1, _BLACK);
	fillellipse(x + 3, y + 8, 2, 2);
	fillellipse(x + 10, y + 4, 2, 2);
	fillellipse(x + 10, y + 12, 2, 2);

	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	line(x + 3, y + 7, x + 10, y + 3);
	line(x + 3, y + 8, x + 10, y + 4);
	line(x + 3, y + 9, x + 10, y + 5);
	line(x + 3, y + 7, x + 10, y + 11);
	line(x + 3, y + 8, x + 10, y + 12);
	line(x + 3, y + 9, x + 10, y + 13);
}

void draw_bk()
{
	setfillstyle(1, _LIGHTGRAY);
	bar(0, 0, SCREENWIDTH, SCREENHEIGHT);
	// devide line
	setcolor(_BLACK);
	setlinestyle(0, 0, 3);
	line(0.35 * SCREENWIDTH, 0, 0.35 * SCREENWIDTH, SCREENHEIGHT);
	// task box
	setlinestyle(0, 0, 3);
	rectangle(10, 80, 348, 630);//TASK LIST BORDEN EDGE
	// task coin & words
	draw_task_coin(10, 10);
	setcolor(_BLACK);
	settextstyle(0, 0, 2);
	outtextxy(100, 20, "Let's create a");
	outtextxy(100, 45, "new task");
	// task choose bottons
	draw_share_coin(10, 640);
	draw_new_coin(10, 686);
	draw_save_coin(10, 731);
	draw_delete_coin(185, 686);
	draw_refresh_coin(185, 731);

	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	rectangle(30, 640, 30 + 136, 640 + 24);
	rectangle(30, 684, 30 + 136, 684 + 24);
	rectangle(30, 727, 30 + 136, 727 + 24);
	rectangle(205, 684, 205 + 136, 684 + 24);
	rectangle(205, 727, 205 + 136, 727 + 24);

	settextstyle(0, 0, 2);
	outtextxy(30 + MARGIN, 640 + MARGIN, "Public");
	outtextxy(30 + MARGIN, 684 + MARGIN, "New");
	outtextxy(30 + MARGIN, 727 + MARGIN, "Save All");
	outtextxy(205 + MARGIN, 684 + MARGIN, "Delete");
	outtextxy(205 + MARGIN, 727 + MARGIN, "Refresh");
	// quit
	setfillstyle(1, _Grey93);
	bar(0.35 * SCREENWIDTH + 40, 80, SCREENWIDTH - 40, 760);
	draw_quit_coin(924, 10);
}
