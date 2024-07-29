#include "memo.h"
#include "editor.h"

void draw_tasklist(Tasks usrtask)
{

	// int i = 0;
	FILE *fp_draw;
	FILE *fp;

   //	int draw_j = 0;
	char tmp[PATH_LENGTH];
	if (usrtask.num == 0 && usrtask.other_task_num == 0)
	{
		return;
	}
	// for (draw_j = 0; draw_j < NUM_TASKS; draw_j++)
	//{

	// sprintf(tmp, "drawlist --%d", usrtask.idpoor[draw_j]);
	// printf("%d", usrtask.idpoor[draw_j]);
	// logmessage(tmp);
	//}
	// printf("\n idnum %d", usrtask.num);
	// printf("\n others num %d", usrtask.other_task_num);
	/*draw other task */

	if (usrtask.other_task_num > 0)
	{
		TaskData *draw_data_others = (TaskData *)malloc(usrtask.other_task_num * sizeof(usrtask.other_task_num));

		if (draw_data_others == NULL)
		{
			//printf("NOT mem for drawdata_others\n");

			return;
		}
		for (int i = 0; i < usrtask.other_task_num; i++)
		{
			// draw_data = (TaskData *)malloc(sizeof(TaskData));
			if ((fp_draw = fopen(usrtask.others_path_poor[i], "rb")) == NULL)
			{
				// logmessage("[svef]cnt\n");
			//	printf("[draw_tasklist others]cant open path%s\n", usrtask.others_path_poor[i]);

				fclose(fp_draw);
				free(draw_data_others);
				return;
			}
			else
			{
				fread(&(draw_data_others[i]), sizeof(TaskData), 1, fp_draw);
				fclose(fp_draw);
				draw_taskbox(18, 116 + i * 60, draw_data_others[i]);
				// printf("drwlist....");
				// free(draw_data[i]);
			}
		}
		free(draw_data_others);
	}
	if (usrtask.num > 0)
	{
		TaskData *own_data = (TaskData *)malloc(usrtask.num * sizeof(TaskData));
		if (own_data == NULL)
		{
		//	printf("NOT mem for drawdata_own\n");

			return;
		}
		for (int i = 0; i < usrtask.num && i < 20; i++)
		{

			num_id2path(usrtask.usr, usrtask.idpoor[i], 0, tmp);
			// printf("%s", tmp);
			// draw_data = (TaskData *)malloc(sizeof(TaskData));
			if ((fp = fopen(tmp, "rb")) == NULL)
			{
				// logmessage("[svef]cnt\n");
				//printf("[draw_tasklist own]cant open path%d\n", tmp);

				fclose(fp);
				free(own_data);
				return;
			}
			else
			{

				fread(&(own_data[i]), sizeof(TaskData), 1, fp);
				fclose(fp);
				draw_taskbox(18, 152 + (i + 3) * 60, own_data[i]);
				//printf("-draw i -%d", i);
				// free(draw_data);

				// continue;
			}
		}
		free(own_data);
	}
	// free(draw_data);

	return;
}
/*
void draw_sort_task(TaskNode **list, int num)
{
	sort_list(list);
	//	draw_tasklist(*list, num);
}*/
int MemoEvent(Mouse *mem_eventmos)
{
	newmouse(mem_eventmos);
	int save_but_x1 = 30;
	int save_but_y1 = 727;
	int save_but_x2 = 166;
	int save_but_y2 = 751;
	Memo_rec public_bar = {30, 640, 136, 24};
	if (mem_eventmos->click == 0)
	{
		return 0;
	}
	if (mem_eventmos->posx > 924 && mem_eventmos->posx < 984 && mem_eventmos->posy < 70 && mem_eventmos->posy > 10 && mem_eventmos->click == 1) /*ESC*/
	{
		return -1;
	}
	else if (0.5 * SCREENWIDTH + 40 < mem_eventmos->posx && mem_eventmos->posx < SCREENWIDTH - 40 && 80 < mem_eventmos->posy && mem_eventmos->posy < SCREENHEIGHT - 40)
	{
		return 1;
	}
	else if (205 < mem_eventmos->posx && mem_eventmos->posx < 341 &&
			 mem_eventmos->posy > 727 && mem_eventmos->posy < 751 && mem_eventmos->click == 1)
	{
		return 2;
	}
	else if (30 < mem_eventmos->posx && mem_eventmos->posx < 166 &&
			 mem_eventmos->posy > 684 && mem_eventmos->posy < 708 && mem_eventmos->click == 1)
	{
		return 3;
	}/*10, 80, 348, 630*/
	else if (18 < mem_eventmos->posx && mem_eventmos->posx < 330 && 70 < mem_eventmos->posy && mem_eventmos->posy < 620  && mem_eventmos->click == 1)
	{

		return 4; // select task boxs
	}
	else if (save_but_x1 < mem_eventmos->posx && mem_eventmos->posx < save_but_x2 && save_but_y1 < mem_eventmos->posy && mem_eventmos->posy < save_but_y2 && mem_eventmos->click == 1)
	{
		return 5;
	}
	else if (205 < mem_eventmos->posx && mem_eventmos->posx < 341 && 684 < mem_eventmos->posy && mem_eventmos->posy < 708 && mem_eventmos->click == 1)
	{
		return 6;
	}
	else if (public_bar.x < mem_eventmos->posx && mem_eventmos->posx < public_bar.x + public_bar.w && public_bar.y < mem_eventmos->posy && public_bar.y + public_bar.h > mem_eventmos->posy && mem_eventmos->click == 1)
	{
		return 7;
	}
	return 0;
}

int add_memo_event(Mouse *mos, Memo_rec *tit, Memo_rec *txt, Memo_rec *ddl, Memo_rec *exit_bar, Memo_rec *add_bar, Memo_rec *level_bar, Memo_rec *add_photo)
{
	newmouse(mos);

	if (mos->posx > tit->x && mos->posx < tit->x + tit->w && mos->posy > tit->y && mos->posy < tit->y + tit->h && mos->click == 1)
	{
		return 1;
	}
	else if (mos->posx > txt->x && mos->posx < txt->x + txt->w && mos->posy > txt->y && mos->posy < txt->y + txt->h && mos->click == 1)
	{
		return 2;
	}
	else if (mos->posx > ddl->x && mos->posx < ddl->x + ddl->w && mos->posy > ddl->y && mos->posy < ddl->y + ddl->h && mos->click == 1)
	{
		return 3;
	}
	else if (mos->posx > exit_bar->x && mos->posx < exit_bar->x + exit_bar->w && mos->posy > exit_bar->y && mos->posy < exit_bar->y + exit_bar->h && mos->click == 1)
	{
		return 4;
	}
	else if (mos->posx > add_bar->x && mos->posx < add_bar->x + add_bar->w && mos->posy > add_bar->y && mos->posy < add_bar->y + add_bar->h && mos->click == 1)
	{
		return 5;
	}
	else if (mos->posx > level_bar->x && mos->posx < level_bar->x + level_bar->w && mos->posy > level_bar->y && mos->posy < level_bar->y + level_bar->h && mos->click == 1)
	{
		return 6;
	}
	else if (mos->posx > add_photo->x && mos->posx < add_photo->x + add_photo->w && mos->posy > add_photo->y && mos->posy < add_photo->y + add_photo->h && mos->click == 1)
	{
		return 7;
	}

	return 0;
}

void draw_addmemo_back()
{
	Memo_rec tit_bar = {400, 80, 584, 30};
	Memo_rec text_bar = {400, 120, 584, 700 - 120};
	Memo_rec ddl_bar = {700, 705, 280, 24};
	Memo_rec level_bar = {400, 705, 285, 50};
	Memo_rec exit_bar = {700, 734, 112, 26};
	Memo_rec add_bar = {842, 734, 112, 26};
	Memo_rec greenhigh = {415, 729, 74, 24};
	Memo_rec yellowmid = {504, 729, 74, 24};
	Memo_rec redlow = {593, 729, 74, 24};
	Memo_rec add_photo = {490, 28, 200, 24};
	// Memo_rec public_bar = {618, 5, 104, 24};
	Memo_rec gphoto_name = {710, 22, 154, 36}; // 4.5 添加相应photo case事件 (已完成)
	Memo_rec wphoto_name = {716, 28, 142, 24}; // photo public share inputbox
	setfillstyle(1, _WHITE);
	bar(400, 80, SCREENWIDTH - 40, 760);
	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	line(text_bar.x, text_bar.y - 4, text_bar.x + text_bar.w, text_bar.y - 4);
	line(ddl_bar.x + 136, ddl_bar.y, ddl_bar.x + 136, ddl_bar.y + ddl_bar.h);

	rectangle(tit_bar.x, tit_bar.y, tit_bar.x + tit_bar.w, tit_bar.y + tit_bar.h);
	rectangle(text_bar.x, text_bar.y, text_bar.x + text_bar.w, text_bar.y + text_bar.h);
	rectangle(ddl_bar.x, ddl_bar.y, ddl_bar.x + ddl_bar.w, ddl_bar.y + ddl_bar.h);
	rectangle(level_bar.x, level_bar.y, level_bar.x + level_bar.w, level_bar.y + level_bar.h);
	rectangle(exit_bar.x, exit_bar.y, exit_bar.x + exit_bar.w, exit_bar.y + exit_bar.h);
	rectangle(add_bar.x, add_bar.y, add_bar.x + add_bar.w, add_bar.y + add_bar.h);

	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	rectangle(exit_bar.x, exit_bar.y, exit_bar.x + exit_bar.w, exit_bar.y + exit_bar.h);
	rectangle(add_bar.x, add_bar.y, add_bar.x + add_bar.w, add_bar.y + add_bar.h);
	setcolor(_BLACK);
	settextstyle(0, 0, 2);
	outtextxy(ddl_bar.x + 4, ddl_bar.y + 4, "Deadline");
	outtextxy(exit_bar.x + 4, exit_bar.y + 5, "exit");
	outtextxy(add_bar.x + 4, add_bar.y + 5, "add");

	setcolor(_BLACK);
	settextstyle(0, 0, 1);
	outtextxy(level_bar.x + 86, level_bar.y + 3, "Priority Level");
	outtextxy(greenhigh.x + 25, greenhigh.y - 3 - 8, "Low");
	outtextxy(yellowmid.x + 25, yellowmid.y - 3 - 8, "Mid");
	outtextxy(redlow.x + 21, redlow.y - 3 - 8, "High");
	setfillstyle(1, _Green);
	bar(greenhigh.x, greenhigh.y, greenhigh.x + greenhigh.w, greenhigh.y + greenhigh.h);
	setfillstyle(1, _YELLOW);
	bar(yellowmid.x, yellowmid.y, yellowmid.x + yellowmid.w, yellowmid.y + yellowmid.h);
	setfillstyle(1, _RED);
	bar(redlow.x, redlow.y, redlow.x + redlow.w, redlow.y + redlow.h);

	draw_photo_coin(400, 10);
	setcolor(_BLACK);
	setlinestyle(0, 0, 3);
	rectangle(add_photo.x, add_photo.y, add_photo.x + add_photo.w, add_photo.y + add_photo.h);
	settextstyle(0, 0, 2);
	outtextxy(add_photo.x + 4, add_photo.y + 4, "Insert Photo");
}


int add_memo(Tasks usrtask) // 传入名字写文件 num 命名
{
	// close();
	// init();
	// cleardevice();
	// draw_bk();
	// draw_taskbox_back();
	// draw_tasklist(usrtask);

	char usrname[USRNAME_LENGTH];
	strcpy(usrname, usrtask.usr);
	int num = usrtask.idpoor[usrtask.num];
	char gap[4] = FILEGAP_SIG;
	Mouse nmos;
	FILE *fp;

	TaskData *add_new_data = (TaskData *)malloc(sizeof(TaskData));
	if (add_new_data == NULL)
	{
		//printf("[add memo ] not mem\n");
		return 0;
	}
	TextEditor *add_meme_editor = (TextEditor *)malloc(sizeof(TextEditor));
	if (add_meme_editor == NULL)
	{
	//	printf("[add memo ] not mem\n");
		return 0;
	}
	init_taskdata(add_new_data);
	char idnum[ID_LENGTH];
	itoa(num, idnum, 10);
	strcpy(add_new_data->id, idnum);
	char path[PATH_LENGTH] = ROOTUSRPATH;
	strcat(path, usrname);
   //	char gap[4] = FILEGAP_SIG;
	strcat(path, gap);
	strcat(path, idnum);
	strcat(path, "td.dat");

	Memo_rec tit_bar = {400, 80, 584, 30};
	Memo_rec text_bar = {400, 120, 584, 700 - 120};
	Memo_rec ddl_bar = {700, 705, 280, 24};
	Memo_rec level_bar = {400, 705, 285, 50};
	Memo_rec exit_bar = {700, 734, 112, 26};
	Memo_rec add_bar = {842, 734, 112, 26};
	Memo_rec greenhigh = {415, 729, 74, 24};
	Memo_rec yellowmid = {504, 729, 74, 24};
	Memo_rec redlow = {593, 729, 74, 24};
	Memo_rec add_photo = {490, 28, 200, 24};
	// Memo_rec public_bar = {618, 5, 104, 24};
	Memo_rec gphoto_name = {710, 22, 154, 36}; // 4.5 添加相应photo case事件 (已完成)
	Memo_rec wphoto_name = {716, 28, 142, 24}; // photo public share inputbox
	draw_addmemo_back();

	FILE *fpeditor; /*save save editor */
	char save_editor_path[PATH_LENGTH] = ROOTUSRPATH;
	//memset(save_editor_path, 0, PATH_LENGTH);
	//save_editor_path = ROOTDBPATH;
	strcat(save_editor_path, usrtask.usr);
	strcat(save_editor_path, gap);
	strcat(save_editor_path, idnum);
	strcat(save_editor_path, ".dat");

	char share_usrname[15] = {'\0'};
	int photo_state = 0;
	/*new*/
	// TextEditor editor;
	int add_memo_S = 1;
	// TaskData newdata;
	// new_node_add->next_tasknode = NULL;

	// traverse(*head);
	while (1)
	{

		switch (add_memo_S)
		{
		case 1:
			clrmous(nmos.posx, nmos.posy);
			tite_input(add_new_data->task, tit_bar);
			setcolor(_BLACK);
			setlinestyle(0, 0, 1);
			rectangle(tit_bar.x, tit_bar.y, tit_bar.x + tit_bar.w, tit_bar.y + tit_bar.h);
			break;

		case 2:
			clrmous(nmos.posx, nmos.posy);
			text_input(&add_meme_editor, text_bar, 0, &(add_new_data->isdeal));
			setcolor(_BLACK);
			setlinestyle(0, 0, 1);
			rectangle(text_bar.x, text_bar.y, text_bar.x + text_bar.w, text_bar.y + text_bar.h);
			break;

		case 3:
			clrmous(nmos.posx, nmos.posy);
			ddl_input(add_new_data->deadline, ddl_bar);
			setcolor(_BLACK);
			setlinestyle(0, 0, 1);
			line(ddl_bar.x, ddl_bar.y, ddl_bar.x + ddl_bar.w, ddl_bar.y);
			line(ddl_bar.x + ddl_bar.w, ddl_bar.y + ddl_bar.h, ddl_bar.x + ddl_bar.w, ddl_bar.y);
			line(ddl_bar.x, ddl_bar.y + ddl_bar.h, ddl_bar.x + ddl_bar.w, ddl_bar.y + ddl_bar.h);
			break;

		case 4:
			clrmous(nmos.posx, nmos.posy);
			free(add_meme_editor);
			free(add_new_data);
			return 0;

		case 5: // ADD
			protect_text_func(add_meme_editor);
			/*************************************************************/
			// ret_save_editor(add_meme_editor, idnum, usrname, add_new_data->editorpath);

			if ((fpeditor = fopen(save_editor_path, "wb+")) == NULL)
			{
				// logmessage("[svef]cnt\n");
				//printf("[save_editor_file] %s\n", save_editor_path);
				fclose(fpeditor);
				strcpy(add_new_data->editorpath, "\0");
				//return 0;
			}
			else
			{
				fwrite(add_meme_editor, sizeof(TextEditor), 1, fpeditor);
				fclose(fpeditor);
				strcpy(add_new_data->editorpath, save_editor_path);/*保存编辑器地址*/
				//return 0;
			}
			
			/************************************************/
			if (strlen(add_new_data->editorpath) == 0)
			{
				free(add_meme_editor);
				free(add_new_data);
				clrmous(nmos.posx, nmos.posy);
				draw_addmemo_back();
				return 0;
			}
			
			else
			{
				if ((fp = fopen(path, "wb+")) == NULL)
				{
					// logmessage("[svef]cnt\n");
					//printf("cant open %s\n", path);
					free(add_meme_editor);
					free(add_new_data);
					fclose(fp);
					clrmous(nmos.posx, nmos.posy);
					draw_addmemo_back();
					return 0;
				}
				else
				{
					fwrite(add_new_data, sizeof(TaskData), 1, fp);
					fclose(fp);
					// printf("[add_memo]save %s\n", path);
					free(add_meme_editor);
					free(add_new_data);
					clrmous(nmos.posx, nmos.posy);

					return 1;
				}
			}
			//clrmous(nmos.posx, nmos.posy);
			return 0;

		case 6:
			clrmous(nmos.posx, nmos.posy);
			level_choose(&(add_new_data->level), level_bar, greenhigh, yellowmid, redlow);
			setcolor(_BLACK);
			setlinestyle(0, 0, 1);
			rectangle(level_bar.x, level_bar.y, level_bar.x + level_bar.w, level_bar.y + level_bar.h);
			break;
		case 7:
			clrmous(nmos.posx, nmos.posy);
			insert_photo(add_new_data->imgpath, add_photo, gphoto_name, wphoto_name, add_new_data->task, tit_bar, add_meme_editor, text_bar, add_new_data->id, usrname);
			photo_state = 3;
			break;
		/*case 8:
			clrmous(nmos.posx, nmos.posy);
			public_share(usrname, share_usrname, gphoto_name, wphoto_name);
			break;*/
		default:
			break;
		}
		// delay(10);
		add_memo_S = add_memo_event(&nmos, &tit_bar, &text_bar, &ddl_bar, &exit_bar, &add_bar, &level_bar, &add_photo);
	}
	//return 0;
}


int init_usrTASk(Tasks *usrtask)
{
	char usr_path[PATH_LENGTH] = ROOTUSRPATH;
	strcat(usr_path, usrtask->usr);
	char gap[4] = FILEGAP_SIG;
	strcat(usr_path, gap);
	strcat(usr_path, "ub.dat");

	FILE *usr_fp;
	if ((usr_fp = fopen(usr_path, "rb")) == NULL)
	{
		// logmessage("[svef]cnt\n");
		//printf("[memoinit]cant open %s\n", usr_path);
		// usrtask->path_poor[0] =
		fclose(usr_fp);
		return 0;
	}
	else
	{
		// fwrite(usrtask,sizeof(Tasks),1,usr_fp);
		fread(usrtask, sizeof(Tasks), 1, usr_fp);
		fclose(usr_fp);
		return 1;
	}
}
/**
 * @brief 备忘录的主体
 * 
 * @param usr 
 */
void memoinit(const char *usr)
{
	// close();
	// init();
	Rectangle msg = {600, 310, 400, 40};
	char usrname[USRNAME_LENGTH];
	char share_name[USRNAME_LENGTH];
	int ifshare = 0;
	strcpy(usrname, usr);
	char temp_add_path[PATH_LENGTH];
	char temp_edit_path[PATH_LENGTH];
	char temp_file_path[PATH_LENGTH];
	int i;
	int j;
	int memos = -1;
	Tasks UsrTask;
	strcpy(UsrTask.usr, usrname);
	memos = init_usrTASk(&UsrTask);
	if (memos == 0)
	{
		// popmsg(msg, "NEW USR !!! WELCOME",2);

		UsrTask.num = 0;
		memset(UsrTask.others_path_poor, 0, OTHER_TASK_NUM * PATH_LENGTH);
		/*init id poor*/
		for (i = 0; i < 10; i++)
		{
			UsrTask.idpoor[i] = i;
		}
		UsrTask.other_task_num = 0;
		/*for (j = 0; j < NUM_TASKS; j++)
		{
			char tmp[3];
			sprintf(tmp, "init --%d", UsrTask.idpoor[j]);
			logmessage(tmp);
		}*/
	}
	Mouse memomos;
	int memo_init_s = 0;
	int task_list_state = -101; // listen task select
	int tasknum = -101;
	int as = 0;
	int es = -1;
	int ss = -1;
	// cleardevice();

	draw_bk();
	draw_taskbox_back();

	if (memos == 1)
	{
		// popmsg(msg, "WELCOME BACK!",2);
		draw_tasklist(UsrTask);
	}
	// draw_tasklist(UsrTask.head, UsrTask.num);

	while (1)
	{
		memo_init_s = MemoEvent(&memomos);
		switch (memo_init_s)
		{

		case -1: // 退出
			//exit(0);
			return;
			
		case 2: // 刷新
			clrmous(memomos.posx, memomos.posy);
			delay(10);
			cleardevice();
			draw_bk();
			draw_taskbox_back();
			// Tasks tmptask = {"hello",{0,2,3,4,5,1},{"","",""},0,2};
			draw_tasklist(UsrTask);

			break;
		case 3: // 添加memo
			clrmous(memomos.posx, memomos.posy);
			if (UsrTask.num>=5)
			{
				popmsg(msg,"num overflow",1);
				break;
			}

			if (add_memo(UsrTask) == 0)
			{
				// free(new_node);
				draw_addmemo_back();
				//  delete new_node;
				// traverse(UsrTask.path_poor, UsrTask.num);
				//printf("failed add memo\n");
				break;
			}
			else
			{
				// strcpy(UsrTask.path_poor[UsrTask.num], temp_add_path);
				draw_addmemo_back();
				UsrTask.num++;
				delay(10);
				// save_bk_mou(memomos.posx, memomos.posy);
				// drawmous(memomos.posx, memomos.posy);
				break;
			}

			//break;

		case 4: // 点击
			clrmous(memomos.posx, memomos.posy);
			task_list_state = taskbox_event();
			if (task_list_state == -1)
			{
				break;
			}
			else if (0 <= task_list_state && task_list_state < NUM_TASK_BOXS)
			{
				// clrmous(memomos.posx, memomos.posy);
				if (0 <= task_list_state && task_list_state <= 2)
				{
					if (strlen(UsrTask.others_path_poor[task_list_state]) == 0)
					{
						break; /*未检测others地址*/
					}
					es = edit_task(UsrTask.others_path_poor[task_list_state]);
					if (es == 1)
					{
						//printf("[edit others]ok");
						delay(10);
						// newmouse(&memomos);

						// clrmous(memomos.posx, memomos.posy);

						break;
					}
					else
					{
						//printf("[edit others] failed");
						break;
					}
				}
				else
				{
					num_id2path(UsrTask.usr, UsrTask.idpoor[task_list_state - 3], 0, temp_edit_path);
					es = edit_task(temp_edit_path);
					if (es == 1)
					{
						//printf("[edit]ok");

						break;
					}
					else
					{
						//printf("[edit] failed");
						break;
					}
				}

				break;
			}
			break;
		case 5:

			ss = save_usrmemo(&UsrTask);
			if (ss == 1)
			{
				//printf("[save]ok");
			}
			else
			{
				//printf("[save]failed");
			}
			break;
		case 6:
			/*delet a deal node and num--*/

			// delete_deal_task(&UsrTask);

			if (UsrTask.num > 0)
			{
				delete_task_byid(&UsrTask); /*num--在函数内*/
			}
			break;
		// case 7: 文件共享
		// 获取用户名 选择任务 确认分享
		case 7:
			clrmous(memomos.posx, memomos.posy);
			sharename(share_name); // 共享用户的用户名
			tasknum = taskbox_event();
			if (tasknum == -1)
			{
				break;
			}
			else if (0 <= tasknum && tasknum < NUM_TASK_BOXS)
			{
				ifshare = click_share();
				if (ifshare == 1)
				{
					num_id2path(UsrTask.usr, UsrTask.idpoor[tasknum - 3], 0, temp_file_path);
					public_share(temp_file_path, share_name); // need change 4.17
					ifshare--;
					break;
				}
				else
					break;
			}
			break;
		default:
			//	mos.style = 0;
			/// MouseS = 0;
			break;
		}

		if (UsrTask.num > NUM_TASKS - 1 || UsrTask.num < 0)
		{
			printf("usr_task_num_error[memo_init]\n");
			delay(1000);
			exit(-1);
		}
	}
}
