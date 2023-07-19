#include "core.h"
/**
 * 1.init graph driver
 * 2.init mouse
 * 3.init color
 */
void init(void)
{	
	
	initgraphmode(1);
	mouseinit();
	useRGB256Colors();
}
/**
 * @brief show local real time
 * 
 * @param posx 
 * @param posy 
 * @return int 
 */
int refresh_time(int posx, int posy);
/**
 * @brief get keyboard infor
 * 
 * @return int 
 */
int keyEvent();
/**
 * @brief listen Register Event
 * 
 * @param mos 
 * @param ub 
 * @param pb 
 * @param ppb 
 * @param rb 
 * @return int 
 */
int RegisterEvent(Mouse *mos, Textbox ub, Textbox pb, Textbox ppb, Textbox rb)
{
	mos->click = 0; // 防止前一次鼠标内容覆盖
	newmouse(mos);
	// mos->click = 0;
	// TODO() finish exit event
	int k = keyEvent();
	if (mos->posx > 1000 && mos->posy < 30 && mos->click == 1 || k == 0x011b) /*ESC*/
	{
		return -1;
	}
	else if (mos->posx > 930 && mos->posx <= 980 && mos->posy < 30 && mos->click == 1)
	{
		return 5;
	}
	else if (ub.posx < mos->posx && mos->posx < ub.posx + ub.width &&
			 ub.posy < mos->posy && mos->posy < ub.posy + ub.height &&
			 mos->click == 1)
	{
		return 1; // in userbox and click
	}
	else if (pb.posx < mos->posx && mos->posx < pb.posx + pb.width &&
			 pb.posy < mos->posy && mos->posy < pb.posy + pb.height &&
			 mos->click == 1)
	{
		return 2; // in passwordbox and click
	}
	else if (ppb.posx < mos->posx && mos->posx < ppb.posx + ppb.width &&
			 ppb.posy < mos->posy && mos->posy < ppb.posy + ppb.height &&
			 mos->click == 1)
	{
		return 3; // in loadbutton and click
	}
	else if (rb.posx < mos->posx && mos->posx < rb.posx + rb.width &&
			 rb.posy < mos->posy && mos->posy < rb.posy + rb.height &&
			 mos->click == 1)
	{
		return 4; // register
	}

	return 0;
}

void draw_home_button()
{
	Textbox log, reg;
	log.posx = 250;
	reg.posx = 650;
	log.posy = 550;
	reg.posy = 550;
	log.width = reg.width = 150;
	log.height = reg.height = 50;
	draw_textbox(log);
	draw_textbox(reg);
	settextstyle(0, 0, 2);
	outtextxy(log.posx + 10, log.posy + 10, "Login..");
	outtextxy(reg.posx + 10, reg.posy + 10, "Register");
}
void drawhomepagebk()
{

	setfillstyle(1, _WHITE);
	bar(0, 0, 1024, 768);
	setfillstyle(1, _RED);
	fillellipse(1000, 24, 18, 18);
	setfillstyle(1, _YELLOW);
	fillellipse(1000 - 40, 24, 18, 18);
	setcolor(_BLACK);
	settextstyle(0, 0, 4);
	outtextxy(350, 120, "MEMO NOTE");
	draw_icon(225, 80, 100, 100);

	refresh_time(920, 740);
}
int Register_judge(char *usr, char *p1, char *p2)
{
	if (strcmp(p1, p2) == 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
	return 0;
}
int loginEvent(Mouse *logeve_mos, Textbox ub, Textbox pb, Button bt)
{
	logeve_mos->click = 0; // 防止前一次鼠标内容覆盖
	newmouse(logeve_mos);
	// mos->click = 0;
	// TODO() finish exit event
	int k = keyEvent();
	if (logeve_mos->posx > 1000 && logeve_mos->posy < 30 && logeve_mos->click == 1 || k == 0x011b) /*ESC*/
	{
		return -1;
	}
	else if (logeve_mos->posx > 930 && logeve_mos->posx <= 980 && logeve_mos->posy < 30 && logeve_mos->click == 1)
	{
		return 4;
	}
	else if (ub.posx < logeve_mos->posx && logeve_mos->posx < ub.posx + ub.width &&
			 ub.posy < logeve_mos->posy && logeve_mos->posy < ub.posy + ub.height &&
			 logeve_mos->click == 1)
	{
		return 1; // in userbox and click
	}
	else if (pb.posx < logeve_mos->posx && logeve_mos->posx < pb.posx + pb.width &&
			 pb.posy < logeve_mos->posy && logeve_mos->posy < pb.posy + pb.height &&
			 logeve_mos->click == 1)
	{
		return 2; // in passwordbox and click
	}
	else if (bt.posx < logeve_mos->posx && logeve_mos->posx < bt.posx + bt.width &&
			 bt.posy < logeve_mos->posy && logeve_mos->posy < bt.posy + bt.height &&
			 logeve_mos->click == 1)
	{
		return 3; // in loadbutton and click
	}

	return 0;
}
/*
 *Function: userjudge
 *----------------------------------------
 *Args: Textbox & char *
 *Return: Judge state
 *-1 or 0 is error &  1 is achieve
 *Note: open usrs.txt; create
 *char **poor; use keyboard and
 *visual


*/
int Registe_usr(char *usr, char *pass)
{

	chdir("C:\\MEMO\\USERS");
	char name[11];
	sprintf(name, "%s\n", usr);
	int rs;
	FILE *fp, *p;
	rs = mkdir(usr);
	if (rs == 0)
	{
		char Path[101] = "C:\\MEMO\\USERS\\";
		const char passPath[12] = "\\\\pass.txt";
		strcat(Path, usr);
		strcat(Path, passPath);
		if ((fp = fopen(Path, "w+")) == NULL)
		{
			logmessage("[register] cant mkfile\n");
			fclose(fp);
			return -1;
		}
		else
		{
			fputs(pass, fp);
			fclose(fp);
			if ((p = fopen("C:\\MEMO\\USERS\\usrs.txt", "a+")) == NULL)
			{
				logmessage("[register] cant open\n");
				fclose(fp);
				return -1;
			}
			else
			{
				fputs(name, p);
				fclose(p);
			}
		}

		return 1;
	}
	else
	{
		logmessage("[register] cant mkdir\n");
		return -1;
	}
	return 0;
}
int userjudge(Textbox ub, char *u)
{
	draw_textbox(ub);
	char usr[8] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	char usrpoor[10][8] = {
		{'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
		{'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
		{'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
		{'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
		{'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'}};
	char tmp;
	int num = 0;
	int k = 0;
	char outchar[2] = {'\0', '\0'};
	FILE *fp;
	setcolor(BLACK);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
	while (num >= 0)
	{

		k = bioskey(0);
		tmp = (char)(k & 0xff);
		if (tmp == '\r')
		{
			break;
		}
		else if (tmp == '\b')
		{
			if (num > 0)
			{
				usr[num] = '\0';
				setfillstyle(1, LIGHTGRAY);
				num--;
				if (num >= 0)
					bar(ub.posx + 2 + num * 17, ub.posy + 2, ub.posx + 2 + num * 17 + 17, ub.posy + 2 + 17); /// 删除块大小
			}
		}
		else if ('a' <= tmp && tmp <= 'z' || 'A' <= tmp <= 'Z')
		{
			usr[num] = tmp;
			outchar[0] = tmp;
			setcolor(BLACK);
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); /// 文字大小对应关系
			outtextxy(ub.posx + 2 + num * 17, ub.posy + 2, outchar);
			num++;
		}
		else
		{
		}
	}
	if (num >= 8)
	{
		// hz_writexy(80,100,"用户id过长",BLACK,16);///
		Rectangle msg = {200, 310, 400, 40};
		popmsg(msg, "userid too long", 2);
		return -1;
	}
	if (num < 8 && usr[0] != '\0')
	{
		int n_lines = 0;
		n_lines = readfilelines(USRSLISTPATH, usrpoor);
		int j = 0;
		for (; (strcmp(usr, usrpoor[j]) != 0) && j < n_lines;)
		{
			j++;
		}
		if (j == n_lines)
		{
			Rectangle msg = {200, 310, 400, 40};
			popmsg(msg, "no user id", 1);
			return -1;
		}
		else
		{
			strcpy(u, usrpoor[j]);
			Rectangle msg = {200, 310, 400, 40}; /// 更改大小和位置
			popmsg(msg, "userid ok", 1);		 ///
			return 1;
		}
	}
	return 0;
}
/**
 * @brief 
 * 
 */
void memoregiste()
{

	cleardevice();
	drawhomepagebk();
	refresh_time(920, 740);
	Mouse mos;
	Textbox ub, pb, ppb, rb;
	ub.posx = pb.posx = ppb.posx = 200;
	rb.posx = 350;
	ub.posy = 250;
	pb.posy = 330;
	ppb.posy = 410;
	rb.posy = 500;
	ub.width = pb.width = ppb.width = 500;
	rb.width = 160;
	ub.height = pb.height = rb.height = ppb.height = 50;
	draw_textbox(ub);
	draw_textbox(pb);
	draw_textbox(rb);
	draw_textbox(ppb);
	settextstyle(0, 0, 2);
	outtextxy(ub.posx, ub.posy - 20, "Input user's name");
	outtextxy(pb.posx, pb.posy - 20, "Input user's password");
	outtextxy(ppb.posx, ppb.posy - 20, "Input password again");
	outtextxy(rb.posx + 10, rb.posy + 10, "Confirm!");

	Rectangle msg = {50, 50, 400, 40};
	int s, us, ps1, ps2;
	char usr[11], pass1[11], pass2[11];
	while (1)
	{
		s = RegisterEvent(&mos, ub, pb, ppb, rb);
		switch (s)
		{
		case -1:
			exit(0);
			break;
		case 1:
			draw_textbox(ub);
			Rectangle ubbox = {ub.posx, ub.posy, ub.posx + ub.width, ub.posy + ub.height};
			simpleinputbox(ubbox, usr, 16, LIGHTGRAY, BLACK, 17);
			break;
		case 2:
			draw_textbox(pb);
			Rectangle pbbox = {pb.posx, pb.posy, pb.posx + pb.width, pb.posy + pb.height};
			simpleinputbox(pbbox, pass1, 16, LIGHTGRAY, BLACK, 17);
			break;
		case 3:
			draw_textbox(ppb);
			Rectangle ppbbox = {ppb.posx, ppb.posy, ppb.posx + ppb.width, ppb.posy + ppb.height};
			simpleinputbox(ppbbox, pass2, 16, LIGHTGRAY, BLACK, 17);

			break;
		case 4:
			if (Register_judge(usr, pass1, pass2) == 1)
			{
				if (Registe_usr(usr, pass1) == 1)
				{
					popmsg(msg, "Finish!", 1);
					return;
				}
			}
			else
			{
				popmsg(msg, "Again !!", 1);
			}

			break;
		case 5:
			clrmous(mos.posx, mos.posy);
			return;
		default:
			break;
		}
	}
}
/**
 * @brief 密码判断
 * 
 * @param pb 
 * @param usr 
 * @return int 
 */
int pwjudje(Textbox pb, char *usr)
{
	draw_textbox(pb);
	char password[8] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	char Path[101] = ROOTUSRPATH;
	const char passPath[12] = "\\\\pass.txt";
	strcat(Path, usr);
	strcat(Path, passPath);
	char passpoor[2][8] = {
		{'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
		{'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'}};
	char input[20] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
					  '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	Rectangle inputbox = {pb.posx, pb.posy, pb.posx + pb.width, pb.posy + pb.height};
	int is = simpleinputbox(inputbox, input, 16, LIGHTGRAY, BLACK, 17);
	Rectangle msg = {200, 460, 400, 40}; /// 100,100,200
	if (is == -1 || is == 0)
	{								  // bad input
		popmsg(msg, "bad input ", 2); ///
		return -1;
	}
	else if (is > 0)
	{
		int fs = readfilelines(Path, passpoor);
		if (fs >= 0)
		{
			if (strcmp(passpoor[0], input) == 0)
			{

				popmsg(msg, "password ok", 2); ///
				return 1;
			}
			else
			{
				popmsg(msg, "passwork error", 2); ///
				return -3;
			}
		}
		else
		{
			popmsg(msg, "bad fileread", 2); ///
			return -2;						// bad file read
		}
	}
}
void login()
{
	cleardevice();
	drawhomepagebk();
	refresh_time(920, 740);
	Mouse logmos;
	Button bt;
	Textbox ub, pb, rb;
	ub.posx = pb.posx = 200;
	rb.posx = 350;
	ub.posy = 250;
	pb.posy = 400;
	rb.posy = 500;
	ub.width = pb.width = 500;
	rb.width = 160;
	ub.height = pb.height = rb.height = 50;

	bt.posx = 750;
	bt.posy = 320;
	bt.width = 88;
	bt.height = 60;

	draw_textbox(ub);
	draw_textbox(pb);
	draw_button(bt);
	settextstyle(0, 0, 2);
	outtextxy(200, 220, "please enter user's name");
	outtextxy(200, 370, "please enter the password");
	outtextxy(750 + 4, 320 + 22, "Enter");

	setcolor(_BLACK);
	setlinestyle(0,0,3);
	rectangle(bt.posx, bt.posy, bt.posx + bt.width, bt.posy + bt.height);
	
	// outtextxy(rb.posx+10,rb.posy+10,"Register");
	int s, us, ps;
	char usr[16] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
					'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	Rectangle msg = {200, 310, 400, 40};
	/// mos.click = 0;
	while (1)
	{ /*draw_textbox(ub);
	  draw_textbox(pb);
	  draw_button(bt);*/
		s = loginEvent(&logmos, ub, pb, bt);
		switch (s)
		{
		case -1:
			exit(0);
		case 1: // user  box
			draw_textbox(ub);
			clrmous(logmos.posx, logmos.posy);
			us = userjudge(ub, usr);
			if (us == -1 || us == 0)
			{					  // usrname judge error
				draw_textbox(ub); // clear ub
			}
			break;
		case 2: // password box
			draw_textbox(pb);
			clrmous(logmos.posx, logmos.posy);
			if (us == 1)
			{

				ps = pwjudje(pb, usr); // listen password event
			}
			if (ps != 1)
			{
				draw_textbox(pb); // redraw
			}
			break;
		case 3:
			// draw_button(bt);
			clrmous(logmos.posx, logmos.posy);
			delay(100);
			if ((us == 1 && ps == 1))
			{
				popmsg(msg, usr, 1);
				delay(100);
				cleardevice();
				memoinit(usr);
				//printf("exit!!");
				delay(1000);
				//exit(-1);
				return;
				
			}
			else
			{
				popmsg(msg, "relog!!", 1);
			}
			break;
		case 4:
			clrmous(logmos.posx, logmos.posy);
			return;
		default:
			break;
		}
		
		delay(50);
	}
};
/**
 * @brief 更新并显示系统时间
 * size : 100x30
 *
 */
int refresh_time(int posx, int posy)
{

	time_t t = time(NULL);
	struct tm *local_time = localtime(&t);
	int time[6] = {local_time->tm_year + 1900, local_time->tm_mon + 1,
				   local_time->tm_mday, local_time->tm_hour, local_time->tm_min,
				   local_time->tm_sec};
	// if(time[4]!=old_min){
	setfillstyle(1, _WHITE);
	bar(posx, posy, posx + 100, posy + 30);
	setcolor(_BLACK);
	rectangle(posx, posy, posx + 100, posy + 30);
	char s1[26]  ;memset(s1,0,26);
	sprintf(s1, "%2d:%2d", time[3], time[4]);
	char s2[26]; memset(s2,0,26);
	sprintf(s2, "%4d/%2d/%2d", time[0], time[1], time[2]);
	settextstyle(0, 0, 1);
	outtextxy(posx + 20, posy + 4, s1);
	outtextxy(posx + 4, posy + 15, s2);
	//}
	return time[4];
}
int keyEvent()
{
	int k = 0;
	if (bioskey(1))
	{
		k = bioskey(0);
	}
	return k;
}
int homeEvent(Mouse *home_evemos)
{
	newmouse(home_evemos);
	int k = keyEvent();
	if (home_evemos->posx > 1000 && home_evemos->posy < 30 && home_evemos->click == 1 || k == 0x011b) /*ESC*/
	{
		return -1;
	}
	else if (home_evemos->click == 1 && home_evemos->posx > 250 && home_evemos->posx < 400 && home_evemos->posy > 550 && home_evemos->posy < 600)
	{
		return 1;
	}
	else if (home_evemos->click == 1 && home_evemos->posx > 650 && home_evemos->posx < 800 && home_evemos->posy > 550 && home_evemos->posy < 600)
	{
		return 2;
	}
	return 0;
}
void close(void)
{
	cleardevice();
	closegraph();
}
/**
 * @brief 主界面
 * 
 * @return int 
 */
int home()
{
	cleardevice();
	drawhomepagebk();
	draw_home_button();
	Mouse homemos;
	int s;
	int old_min;
	while (1)
	{ // old_min = refresh_time(900,730,old_min);
		s = homeEvent(&homemos);
		switch (s)
		{
		case 1:
			clrmous(homemos.posx, homemos.posy);
			login();
			cleardevice();
			drawhomepagebk();
			draw_home_button();
			//	memoinit();
			break;

		case -1:

			return 0;
		case 2:
			clrmous(homemos.posx, homemos.posy);
			memoregiste();
			cleardevice();
			drawhomepagebk();
			draw_home_button();
			break;
		case 0:
			break;
		}
		delay(50);
		/* code */
	}
}

