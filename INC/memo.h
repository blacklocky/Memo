#ifndef _memo_h_
#define _memo_h_
#include<graphics.h>
#include"mouse.h"
#include<bios.h>
#include"config.h"
#include"moudle.h"
#include"editor.h"
#include"core.h"
#include"draw.h"
#define MEMO_BODY_PAGE_X = 400
#define MEMO_BODY_PAGE_Y = 80
#define MEMO_BODY_END_X = 968
#define MEMO_BODY_END_Y = 760
#define NUM_TASK_BOXS 8



void memoinit(const char *usr);
//int add_memo(TaskList *list,int num);
//int add_memo(TASKS *usrtask);
void draw_addmemo_back();
//void show_task_body(TASKDATA data);
//void draw_taskbox_back();


#endif