
/**
 * @file moudle.cpp
 * @author Wen Yanqiu
 * @brief 
 * @version 0.1
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include"moudle.h"
/**
 * @brief 将数字id转换成对应的字符串地址
 *
 * @param num
 * @param mode 0==TASKDATA_path 1==TEXTEDITOR_PATH 2==PHOTO_PATH
 * @return int
 */
int num_id2path(char *usrname, int id, int mode, char *target)
{

	// char retpath[PATH_LENGTH] = ROOTUSRPATH;
	char retpath[PATH_LENGTH];
	memset(retpath, 0, PATH_LENGTH);
	strcat(retpath, ROOTUSRPATH);
	strcat(retpath, usrname);  // eg.  ../hello
	char gap[4] = FILEGAP_SIG; /* ////  */
	strcat(retpath, gap);	   /*./hello/*/
	char id_str[2];
	itoa(id, id_str, 10);
	strcat(retpath, id_str);
	if (mode == 0)
	{
		strcat(retpath, "TD.dat"); /*TASKDAT FILE PATH*/
		strcpy(target, retpath);
		//printf("[num2id]target%s  ", target);
		return 0;
	}
	else if (mode == 1)
	{
		strcat(retpath, ".dat");
		strcpy(target, retpath);
		return 1;
	}
	else if (mode == 2)
	{
		strcat(retpath, "P.DAT"); //????
		strcpy(target, retpath);
		return 2;
	}
	else
	{
		return -1;
	}
}
void draw_taskbox_back()
{
	Task_Box_Rec rec[NUM_TASK_BOXS];
	// init_taskbox_recs(&rec);
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		// recs[i] = {18,30+i*60,18+310,30+i*60+50};
		rec[i].x1 = 18;
		rec[i].y1 = 116 + i * 60;
		rec[i].x2 = 18 + 310;
		rec[i].y2 = 116 + i * 60 + 50;
	}
	for (i = 3; i < NUM_TASK_BOXS; i++)
	{
		rec[i].x1 = 18;
		rec[i].y1 = 26 + 126 + i * 60;
		rec[i].x2 = 18 + 310;
		rec[i].y2 = 26 + 126 + i * 60 + 50;
	}
	setcolor(_BLACK);
	int off = 2;
	// int i = 0;
	for (int j = 0; j < NUM_TASK_BOXS && j < 100; j++)
	{
		setfillstyle(1, _WHITE);
		bar(rec[j].x1, rec[j].y1, rec[j].x2, rec[j].y2);
		rectangle(rec[j].x1 - off, rec[j].y1 - off, rec[j].x2 + off, rec[j].y2 + off);
	}

	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	draw_public_coin(18, 88);
	draw_private_coin(18, 296);
	settextstyle(0, 0, 2);
	outtextxy(34 + 12, 90 + 4, "Public Tasks");
	outtextxy(34 + 12, 298 + 4, "Private Tasks");
	return;
}
/**
 * @brief listen tasklist event
 *
 * @return int 
 */
int taskbox_event()
{
	Task_Box_Rec rec[NUM_TASK_BOXS];
	// init_taskbox_recs(&rec);
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		// recs[i] = {18,30+i*60,18+310,30+i*60+50};
		rec[i].x1 = 18;
		rec[i].y1 = 116 + i * 60;
		rec[i].x2 = 18 + 310;
		rec[i].y2 = 116 + i * 60 + 50;
	}
	for (i = 3; i < NUM_TASK_BOXS; i++)
	{
		rec[i].x1 = 18;
		rec[i].y1 = 26 + 126 + i * 60;
		rec[i].x2 = 18 + 310;
		rec[i].y2 = 26 + 126 + i * 60 + 50;
	}
	Mouse taskbox_mos;
	char t_char = 0;
	int s = -1;
	while (1)
	{
		newmouse(&taskbox_mos);
		t_char = (char)(KeyEvent() & 0xff);

		if (t_char == 0x1B || 0.5 * SCREENWIDTH + 40 < taskbox_mos.posx && taskbox_mos.posx < SCREENWIDTH - 40 && 80 < taskbox_mos.posy && taskbox_mos.posy < SCREENHEIGHT - 40 && taskbox_mos.click == 1)
		{
			clrmous(taskbox_mos.posx, taskbox_mos.posy);
			break;
		}
		for (int taskbox_event_i = 0; taskbox_event_i < NUM_TASK_BOXS && taskbox_event_i < 100; taskbox_event_i++)
		{
			if (taskbox_mos.click == 1 && taskbox_mos.posx > rec[taskbox_event_i].x1 && taskbox_mos.posy > rec[taskbox_event_i].y1 && taskbox_mos.posx < rec[taskbox_event_i].x2 && taskbox_mos.posy < rec[taskbox_event_i].y2)
			{
				s = 1;
			}
			if (s == 1)
			{
				clrmous(taskbox_mos.posx, taskbox_mos.posy);
				return taskbox_event_i;
			}
		}
		// clrmous(taskbox_mos.posx, taskbox_mos.posy);
	}
	return 0;
}
void draw_button(Button bt){
    switch (bt.status)
    {
    case 0:
        setfillstyle(1,WHITE);
        break;
    case 1:
        setfillstyle(1,LIGHTGRAY);

        break;

    case 2:
        setfillstyle(1,DARKGRAY);
        break;
    }
    int x=bt.posx,y=bt.posy,w=bt.width,h=bt.height;
    bar(x,y,x+w,y+h);
}

void draw_textbox(Textbox tb){
    setfillstyle(1,LIGHTGRAY);
    bar(tb.posx,tb.posy,tb.posx+tb.width,tb.posy+tb.height);
    setcolor(BLACK);
    setlinestyle(SOLID_LINE,0,3);
    line(tb.posx,tb.posy,tb.posx+tb.width,tb.posy);
    line(tb.posx+tb.width,tb.posy,tb.posx+tb.width,tb.posy+tb.height);
    line(tb.posx+tb.width,tb.posy+tb.height,tb.posx,tb.posy+tb.height);
    line(tb.posx,tb.posy+tb.height,tb.posx,tb.posy);
    
}
/*
int draw_task(int posx,int posy,int width,int height,TaskData task){
	setfillstyle(1,_LIGHTGRAY);
	bar(posx,posy,posx+width,posy+height);
	setcolor(_BLACK);
	rectangle(posx,posy,posx+width,posy+height);
	return

} */
void fill_box(Rectangle rec,int color){
    setfillstyle(1,color);
	bar(rec.x,rec.y,rec.x+rec.w,rec.y+rec.h);
	return;
}
/**
 * Function:popmsg
 * ---------------------------------
 * Brief: pop a message in a while 
 * Args: rec Message box 
 *       msg message
 *       time   
 *Return: NULL
 *Note: time--delay(1000*)
 *output in black
 * 
 */
void popmsg(Rectangle rec,const char *msg,int time){
    int size;
    void *buffer;

    size = imagesize(rec.x,rec.y,rec.x+rec.w,rec.y+rec.h);
    buffer = malloc(size);
    getimage(rec.x,rec.y,rec.x+rec.w,rec.y+rec.h,buffer);
    setcolor(BLACK);
    setlinestyle(SOLID_LINE,0,1);
	rectangle(rec.x+1,rec.y+1,rec.x+rec.w-1,rec.y+rec.h-1);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	outtextxy(rec.x+2,rec.y+2,msg);
	delay(time*1000);
	putimage(rec.x,rec.y,buffer,COPY_PUT);
	delay(50);
	free(buffer);

}
void draw_icon(int x1, int y1, int width, int height)
{
	// int iconlinehei,iconlinelen;
	// iconlinehei=3,iconlinelen=60;
	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	rectangle(x1 - 1, y1 - 1, x1 + width + 1, y1 + height + 1);
	setcolor(_Aqua);
	setlinestyle(0, 0, 3);
	for (int i = 0; i < 4; i++)
		line(x1 + 20, y1 + 30 + i * 15, x1 + 75, y1 + 30 + i * 15);
	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	line(x1 + 90, y1, x1 + 70, y1 + 60);
	line(x1 + width, y1 + 20, x1 + 85, y1 + 65);
	line(x1 + 70, y1 + 60, x1 + 85, y1 + 65);
	line(x1 + 72, y1 + 76, x1 + 70, y1 + 60);
	line(x1 + 72, y1 + 76, x1 + 85, y1 + 65);
	setcolor(_BLACK);
	setfillstyle(1, _BLACK);
	//floodfill(x1 + 85, y1 + 30, _BLACK);
}
void mov_bar(int x0,int y0,int w,int h,int x,int y){
	int size;
	void *buffer;

	size = imagesize(x0,y0,x0+w,y0+h);
	buffer = malloc(size);
	getimage(x0,y0,x0+w,y0+h,buffer);
	setfillstyle(1,_WHITE);
	bar(x0,y0,x0+w,y0+h);
	putimage(x,y,buffer,COPY_PUT);
	delay(50);
	free(buffer);
	return ;
}
/**
 *Function: simpleinputbox
 *-------------------------------- 
 * Args:rec the information of box
 *      s receive input
 *      len 
 *      bkcolor
 *      ptcolor 
 *      font  fontsize 8
 * Return: the length of input
 * Note:len of s > 11 
 */
int simpleinputbox(Rectangle rec,char *s,const int len,int bkcolor,int ptcolor,int font){
    char poor[11]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
	char outchar[2] = {'\0','\0'};
    int now = 0;
    int k = 0;
    char tmp;
    const int margioff = 4 ; 
    Rectangle msg= {50,50,100,10};///50,50,100,10
    while (now>=0)
    {   k = bioskey(0);
        tmp = (char)(k&0xff);
		if(tmp == '\r'){//Enter
			break;
		}
		else if(tmp == '\b'){//BACKSPACE
			poor[now] = '\0';
			setfillstyle(1,bkcolor);
			now--;
			if(now>=0){
				bar(rec.x+margioff+now*font,rec.y+margioff,rec.x+margioff+now*font+font,rec.y+margioff+font);
			}
		}
		else if('a'<=tmp&&tmp<='z'||'A'<=tmp<='Z'||'0'<=tmp&&tmp<='9'){
			outchar[0] = tmp;
			poor[now] = tmp;
			setcolor(ptcolor);
			settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
			outtextxy(rec.x+margioff+now*font,rec.y+margioff,outchar);
			now ++;
		}
	}
	if(now>len){
		popmsg(msg,"overflow!!",5);
		return -1;
	}
	if(now<len){
		strcpy(s,poor);
		return now;
	}
	return 0;


}

/**
 * @brief
 *
 * @return int
 *
 /*
void RegisterWindow(int posx,int posy,int width,int height){
   //s newmouse(mos);
	long size;
	void *buffer;
	size = imagesize(posx,posy,posx+width,posy+height);
   //	buffer = malloc(size);
   //	getimage(posx,posy,posx+width,posy+height,buffer);
	setfillstyle(1,_Grey78);
	bar(posx,posy,posx+width,posy+height);
	delay(1000);
   //	putimage(posx,posy,buffer,COPY_PUT);
   //	free(buffer);

}  */
int KeyEvent(){
	int k = 0;
	if(bioskey(1)){
		k = bioskey(0);
	}
	return k;
}
int save_txtfile(char text[MAX_LINES][MAX_LINE_LENGTH], char *path)
{
	FILE *fp;
	if ((fp = fopen(path, "w+")) == NULL)
	{
		logmessage("[svf]cnt o\n");
		fclose(fp);
		return 0;
	}
	else
	{
		int i = 0;
		int j = 0;
		for (i = 0; i < MAX_LINES; i++)
		{
			for (j = 0; j < MAX_LINE_LENGTH; j++)
			{
				fprintf(fp, "%c", text[i][j]);
			}
		}
		fclose(fp);
		return 1;
	}
	// todo
}
int key_action(char *s)
{

	int key_act = KeyEvent();
	*s = (char)(key_act & 0xff);
	char tmp = *s;
	if (tmp == 0x1B)
	{ // esc
		return ESC;
	}
	else if (tmp == '\r')
	{
		return ENTER;
	}
	else if (tmp == '\b')
	{
		return BACKSPACE;
	}
	else if (key_act == 0x4800)
	{
		return UP;
	}
	else if (key_act == 0x5000)
	{
		return DN;
	}
	else if (key_act == 0x4B00)
	{
		return LEFT;
	}
	else if (key_act == 0x4D00)
	{
		return RIGHT;
	}
	else if (key_act == 0x3920)
	{
		return SPACE;
	}
	else if (tmp >= 0x21 && tmp <= 0x7E)
	{
		return OUTCHR;
	}
	else if (key_act == 0x2C1A)
	{
		return CTRL_Z;
	}
	else if (key_act == 0x1F13)
	{
		return CTRL_S;
	}
	else if (key_act == 0x2004)
	{
		return CTRL_D;
	}
	return 0;
}
/**
 * @brief
 *
 * @param posx
 * @param posy
 * @param data
 */

void receive_time(char *s)
{
	time_t t = time(NULL);
	struct tm *local_time = localtime(&t);
	int time[6] = {local_time->tm_year + 1900, local_time->tm_mon + 1,
				   local_time->tm_mday, local_time->tm_hour, local_time->tm_min,
				   local_time->tm_sec};
	sprintf(s, "%2d/%2d-%2d", time[1], time[2], time[3]);
}


void traverse(char path_poor[][PATH_LENGTH], int all_num)
{
	for (int i = 0; i < all_num; i++)
	{
		printf("%s\n", path_poor[i]);
	}
	return;
}
