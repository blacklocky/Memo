#ifndef _MOUDLE_H_
#define _MOUDLE_H_
#include<time.h>
#include"config.h"
#include<graphics.h>
#include<bios.h>
#include<stdlib.h>
#include<dos.h>
#include<string.h>
#include"gramd.h"
#include"mouse.h"
#include"editor.h"
typedef struct _button{
    int posx;
    int posy;
    int width;
    int height;
    int status;

}Button;
void draw_button(Button bt);

typedef struct _textbox{
    int posx;
    int posy;
    int width;
    int height;
    
}Textbox;
typedef struct _rectangel
{   int x;
    int y;
    int w;
    int h;
}Rectangle;

typedef struct task_box_recs
{
    int x1;
    int y1;
    int x2;
    int y2;

}Task_Box_Rec;
int taskbox_event();
int key_action(char *s);
void draw_taskbox_back();
void draw_icon(int x1, int y1, int width, int height);
int KeyEvent();
void draw_textbox(Textbox tb);
void fill_box(Rectangle rec,int color);
int simpleinputbox(Rectangle rec,char *s,const int len,int bkcolor,int ptcolor,int font);

void popmsg(Rectangle rec,const char *msg,int time);
void mov_bar(int x0,int y0,int w,int h,int x,int y);
int num_id2path(char *usrname, int id, int mode,char *targe);


int save_txtfile(char text[MAX_LINES][MAX_LINE_LENGTH], char *path);
void receive_time(char *s);
void traverse(char path_poor[][PATH_LENGTH], int all_num);
#endif