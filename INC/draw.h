#ifndef _DRAW_H_
#define _DRAW_H_
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include"config.h"
#include"gramd.h"
#define MARGIN 4
void draw_quit_coin(int x, int y);
void draw_photo_coin(int x,int y);
void draw_task_coin(int x, int y);
void draw_private_coin(int x, int y);
void draw_public_coin(int x,int y);
void draw_new_coin(int x,int y);
void draw_delete_coin(int x, int y);
void draw_refresh_coin(int x,int y);
void draw_share_coin(int x,int y);
void draw_bk();

#endif 