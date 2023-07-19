#ifndef _EDITOR_H_
#define _EDITOR_H_

#include<stdlib.h>
#include<string.h>
#include<graphics.h>
#include<bios.h>
#include"file.h"
#include"memo.h"
#include<stdlib.h>
#include<dos.h>
#include<string.h>
#include"gramd.h"
#include"mouse.h"
#include"moudle.h"
#include"config.h"


/*i.dat   TextEditor*/
/*iTD.dat   TASKDATA*/
/*UB.dat    TASKS*/
typedef struct scr_pos
{
    int x;
    int y;
}Screen_Pos;

/*文本编辑器结构*/
typedef struct text_edit
{
    char text[MAX_LINES][MAX_LINE_LENGTH];/*文本数据区*/
    int length[MAX_LINES];/*单行当前长度*/
    int cur_num_lines;/*当前行数*/
    int cursor_row;/*当前光标行索引*/
    int cursor_col;/*当前光标列索引*/
    Screen_Pos pos;/*当前屏幕位置*/
    
} TextEditor;

enum {
    ESC,
    ENTER,
    BACKSPACE,
    UP,
    DN,
    LEFT,
    RIGHT,
	SPACE,
	OUTCHR,
	CTRL_Z,
	CTRL_S,
	CTRL_D
};
typedef struct memorec
{   int x;
	int y;
	int w;
	int h;
}Memo_rec;


typedef struct taskda
{
	int level;
	char initdata[INIT_DATA_LENGTH];
	char task[TASK_LENGTH];
	char id[ID_LENGTH];
	char deadline[DDL_LENGTH];
	int isdeal;
	//TextEditor editor;
	char editorpath[PATH_LENGTH];
	char imgpath[PATH_LENGTH];
	//char txtpath[31];


}TaskData;
/**/

typedef struct taskno
{
	TaskData cur_task;
	taskno *next_tasknode;
}TaskNode;

//typedef TaskNode *TaskList;

typedef struct stasks
{   
	char usr[USRNAME_LENGTH];
	int idpoor[10];/*modifed @date 4.20  10*/
	char others_path_poor[OTHER_TASK_NUM][PATH_LENGTH];
	int other_task_num;/*from 0,1,2*/
	int num;
}Tasks;




void textedit();
void tite_input(char *s,Memo_rec tit_bar);
void ddl_input(char *s,Memo_rec ddl_bar);
int text_input(TextEditor **editor,Memo_rec text_bar,int mode,int *isdeal);

void show_text(char text[MAX_LINES][MAX_LINE_LENGTH]);
void movebox(Memo_rec greenhigh, Memo_rec yellowmid, Memo_rec redlow,int move,int direction);
void level_choose(int *level, Memo_rec level_bar, Memo_rec greenhigh, Memo_rec yellowmid, Memo_rec redlow);
void init_texteditor(TextEditor *editor);
void editrcpy(TextEditor *target,TextEditor source);
void insert_photo(char *s, Memo_rec add_photo, Memo_rec gphoto_name, Memo_rec wphoto_name,char *tit,Memo_rec tit_bar,TextEditor *editor,Memo_rec text_bar,char *id,char *usrname);
void photoname_inputbox(Memo_rec gphoto_name , Memo_rec wphoto_name);
void photoname_input(char *s, Memo_rec wphoto_name);
void newphotoname(char *photopath, char *photoname);
int photo_move(Memo_rec move_bar, Memo_rec cancel_bar);
int public_share(char *edit_file_path, char *usrshare);
void show_newtext(char text[MAX_LINES][MAX_LINE_LENGTH]);
void show_newtitle(char *s, Memo_rec tit_bar);
void sharename(char *s);
int click_share();


void sort_list(TaskNode **list);
//int init_tasklist(char *taskdbpath,TaskNode* start);
void draw_taskbox(int posx, int posy, TaskData data);


void init_taskdata(TaskData* data);
/* 1 ok -1 error*/
void show_task_body(TaskData *data);
void show_title(char title[51]);
TaskNode find_taskndoe_bypos(TaskNode *head,int pos);   
/*光标的屏幕坐标*/
int edit_task(char *edit_file_path);
TaskNode* delete_deal_task(TaskNode *head);
//void new_delete_deal_task(Tasks *task);

void ret_save_editor(TextEditor *editor,char *id,char *usr,char *target);
int save_usrmemo(Tasks *usrtask);
int find_deal_taskid(Tasks utask);
int delete_task_byid(Tasks *usrtask);
int protect_text_func(TextEditor *texteditor);
#endif