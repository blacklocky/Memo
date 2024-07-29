/**
 * @file editor.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-03-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "editor.h"
#include "photo.h"
#include "fangs.h"

void *txt_cursor_buffer;

void draw_textcursor(Screen_Pos pos, int *curs_flag)
{
	if (*curs_flag == 0)
	{ /*没画*/
		setfillstyle(1, _Aqua);
		bar(pos.x, pos.y + 10, pos.x + 8, pos.y + 11);
		*curs_flag = 1;
	}
}
void clr_txtcursor(Screen_Pos pos, int *flag)
{
	if (*flag == 1)
	{
		// setfillstyle(1,_Aqua);
		// bar(pos.x,pos.y+10,pos.x+8,pos.y+11);
		putimage(pos.x - 1, pos.y + 10 - 1, txt_cursor_buffer, COPY_PUT);
		free(txt_cursor_buffer);
		*flag = 0;
	}
}

void save_bk_cursor(Screen_Pos pos)
{
	int size;
	size = imagesize(pos.x - 1, pos.y + 10 - 1, pos.x + 9, pos.y + 12);
	txt_cursor_buffer = malloc(size);
	if (txt_cursor_buffer != NULL)
	{
		getimage(pos.x - 1, pos.y + 10 - 1, pos.x + 9, pos.y + 12, txt_cursor_buffer);
	}
	else
	{
		logmessage("[svbkcs] err\n");
	}
}
/**
 * @brief 光标初始化
 *
 * @param pos
 * @param cur_flag
 * @param txtpos
 */
void textcursor_init(Screen_Pos *pos, int *cur_flag, Screen_Pos txtpos)
{
	pos->x = txtpos.x;
	pos->y = txtpos.y;
	setfillstyle(1, _WHITE);
	bar(pos->x, pos->y + 10, pos->x + 9, pos->y + 12);
	save_bk_cursor(*pos);			 // save buffer
	draw_textcursor(*pos, cur_flag); // init draw
	*cur_flag = 1;					 // drawed
}
void new_txtcursor(Screen_Pos *pos, TextEditor edi, int *flag)
{
	Screen_Pos oldpos;
	oldpos.x = pos->x;
	oldpos.y = pos->y;
	pos->x = edi.pos.x; /*new pos*/
	pos->y = edi.pos.y;
	if (oldpos.x == pos->x && oldpos.y == pos->y)
	{
		return;
	}
	clr_txtcursor(oldpos, flag);
	save_bk_cursor(*pos);
	draw_textcursor(*pos, flag);
}

void refresh_curpos(TextEditor *editor)
{
	editor->pos.x = TEXT_PAGE_X + MARGIN_OFF + 10 * editor->cursor_col;
	editor->pos.y = TEXT_PAGE_Y + MARGIN_OFF + 12 * editor->cursor_row;
	return;
}

void init_texteditor(TextEditor *editor)
{
	memset(editor->text, 0, MAX_LINES * MAX_LINE_LENGTH);
	memset(editor->length, 0, MAX_LINES * sizeof(int));
	// editor->text = {'\0'};
	// editor->length = {0};
	editor->cur_num_lines = 0;
	editor->cursor_col = 0;
	editor->cursor_row = 0;
	editor->pos.x = TEXT_PAGE_X + MARGIN_OFF + 10 * editor->cursor_col;
	editor->pos.y = TEXT_PAGE_Y + MARGIN_OFF + 12 * editor->cursor_row;
	// textcursor_init()

	return;
}

void display_char(Screen_Pos pos, char ch)
{
	if (ch == '\0')
	{
		return;
	}
	char tmp[2] = {'\0', '\0'};
	tmp[0] = ch;
	setcolor(_BLACK);
	outtextxy(pos.x, pos.y, tmp);
}

void clear_char(Screen_Pos pos)
{
	setfillstyle(1, _WHITE);
	bar(pos.x, pos.y, pos.x + 8, pos.y + 8);
}

void insert_char(TextEditor *editor, char ch)
{
	int row = editor->cursor_row;
	int col = editor->cursor_col;
	if (editor->cursor_col + 1 < MAX_LINE_LENGTH && editor->length[row] + 1 < MAX_LINE_LENGTH)
	{ /*如果当前行字符数少于*/
		if (editor->cur_num_lines == 0&&editor->cursor_col==0&&editor->cursor_row==0)//@modifed add straight
		{
			display_char(editor->pos, ch);
			editor->text[0][0] = ch;
			editor->length[0] = 1;

			editor->cursor_col++;
			editor->cur_num_lines = 1;
			refresh_curpos(editor);
			return;
		}

		if (col >= editor->length[row])
		{
			display_char(editor->pos, ch);
			editor->text[row][col] = ch;
			//editor->length[row] = col + 1;
			/*modifed handle length */
			if(col+1>editor->length[row]){
				editor->length[row] = col + 1 ;
			}else{
				editor->length[row] = editor->length[row] +1 ;
			}
			editor->cursor_col++;
			if (editor->cur_num_lines < editor->cursor_row + 1)
			{ /*@modifed  解决光标下方内容消失问题*/
				editor->cur_num_lines = editor->cursor_row + 1;
			}
			else
			{
				editor->cur_num_lines = editor->cur_num_lines;
			}
			refresh_curpos(editor);

			return;
		}

		mov_bar(editor->pos.x, editor->pos.y, (editor->length[row] - col + 1) * 10, 8, editor->pos.x + 10, editor->pos.y);

		for (int i = editor->length[row]; i > col; i--)
		{
			editor->text[row][i] = editor->text[row][i - 1];
		}
		clear_char(editor->pos);
		display_char(editor->pos, ch);
		editor->text[row][col] = ch;
		if(col+1>editor->length[row]){
				editor->length[row] = col + 1 ;
			}else{
				editor->length[row] = editor->length[row] +1 ;
			}
		editor->cursor_col++;
		if (editor->cur_num_lines < editor->cursor_row + 1)
		{ /*@modifed  解决光标下方内容消失问题*/
			editor->cur_num_lines = editor->cursor_row + 1;
		}
		else
		{
			editor->cur_num_lines = editor->cur_num_lines;
		}
		refresh_curpos(editor);
		return;
	}
}

void insert_spacebar(TextEditor *editor)
{
	if (editor->cur_num_lines == 0)
	{
		// display_char(editor->pos, ch);
		setfillstyle(1, _WHITE);
		bar(editor->pos.x, editor->pos.y, editor->pos.x + 8, editor->pos.y + 8);
		editor->text[0][0] = ' ';
		editor->length[0] = 1;

		editor->cursor_col++;
		editor->cur_num_lines = 1;
		refresh_curpos(editor);
		return;
	}

	int row = editor->cursor_row;
	int col = editor->cursor_col;

	if (col >= editor->length[row])
	{
		setfillstyle(1, _WHITE);
		// display_char(editor->pos, ch);
		bar(editor->pos.x, editor->pos.y, editor->pos.x + 8, editor->pos.y + 8);
		editor->text[row][col] = ' ';
		editor->length[row] = col + 1;
		editor->cursor_col++;

		if (editor->cur_num_lines < editor->cursor_row + 1)
		{ /*@modifed  解决光标下方内容消失问题*/
			editor->cur_num_lines = editor->cursor_row + 1;
		}
		else
		{
			editor->cur_num_lines = editor->cur_num_lines;
		}

		refresh_curpos(editor);

		return;
	}

	mov_bar(editor->pos.x, editor->pos.y, (editor->length[row] - col + 1) * 10, 8, editor->pos.x + 10, editor->pos.y);
	for (int i = editor->length[row]; i > col; i--)
	{
		editor->text[row][i] = editor->text[row][i - 1];
	}
	clear_char(editor->pos);
	setfillstyle(1, _WHITE);
	// display_char(editor->pos, ch);
	bar(editor->pos.x, editor->pos.y, editor->pos.x + 8, editor->pos.y + 8);
	editor->text[row][col] = ' ';
	editor->length[row]++;
	editor->cursor_col++;

	if (editor->cur_num_lines < editor->cursor_row + 1)
	{ /*@modifed  解决光标下方内容消失问题*/
		editor->cur_num_lines = editor->cursor_row + 1;
	}
	else
	{
		editor->cur_num_lines = editor->cur_num_lines;
	}
	refresh_curpos(editor);
}
void delect_char(TextEditor *editor)
{
	if (editor->cur_num_lines == 0 || editor->cursor_col == 0)
	{
		return;
	}

	int row = editor->cursor_row;
	int col = editor->cursor_col - 1;
	Screen_Pos tmppos;
	tmppos.x = TEXT_PAGE_X + MARGIN_OFF + 10 * col;
	tmppos.y = TEXT_PAGE_Y + MARGIN_OFF + 12 * row;
	if (col >= editor->length[row])
	{ // editor->cursor_col--;
		return;
	}
	clear_char(tmppos);/*clear show char*/

	for (int i = col; i < editor->length[row] ; i++)/*@modifed */
	{
		editor->text[row][i] = editor->text[row][i + 1];
	}
	mov_bar(editor->pos.x, editor->pos.y, (editor->length[row] - col) * 10, 9, editor->pos.x - 10, editor->pos.y);
	editor->length[row]--;
	editor->cursor_col--;
	refresh_curpos(editor);
}

/*save editor to file */
int save_editor_file(TextEditor *editor, char *sv_path)
{

	FILE *fp;
	// logmessage(path);
	if ((fp = fopen(sv_path, "wb+")) == NULL)
	{
		// logmessage("[svef]cnt\n");
		//printf("[save_editor_file] %s\n", sv_path);
		fclose(fp);
		return 0;
	}
	else
	{
		fwrite(editor, sizeof(TextEditor), 1, fp);
		fclose(fp);
		return 1;
	}
}
/*save editor*/
void ret_save_editor(TextEditor *editor, char *id, char *usr, char *target)
{
	FILE *fp;
	char path[PATH_LENGTH] = ROOTUSRPATH;
	strcat(path, usr);
	char gap[4] = FILEGAP_SIG;
	strcat(path, gap);
	strcat(path, id);
	strcat(path, ".dat");

   //	int s = 0;

	if ((fp = fopen(path, "wb+")) == NULL)
	{
		// logmessage("[svef]cnt\n");
		//printf("[save_editor_file] %s\n", path);
		fclose(fp);
		strcpy(target, "\0");
		return;
	}
	else
	{
		fwrite(editor, sizeof(TextEditor), 1, fp);
		fclose(fp);
		strcpy(target, path);
		return;
	}
}

int read_txtfile(char *path, char text[MAX_LINES][MAX_LINE_LENGTH])
{
	FILE *fp;
	if ((fp = fopen(path, "r")) == NULL)
	{
		logmessage("[rdf]cnt o\n");
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
				fscanf(fp, "%c", &text[i][j]);
			}
		}
		fclose(fp);
		return 1;
	}
}

void show_text(char text[MAX_LINES][MAX_LINE_LENGTH])
{
	int i = 0;
	int j = 0;
	Screen_Pos pos;
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	for (i = 0; i < MAX_LINES; i++)
	{
		for (j = 0; j < MAX_LINE_LENGTH; j++)
		{

			pos.x = TEXT_PAGE_X + MARGIN_OFF + 10 * j;
			pos.y = TEXT_PAGE_Y + MARGIN_OFF + 12 * i;
			display_char(pos, text[i][j]);
		}
	}
	return;
}

void textedit()
{
	setfillstyle(1, _WHITE);
	bar(TEXT_PAGE_X, TEXT_PAGE_Y, TEXT_PAGE_X_END, TEXT_PAGE_Y_END);
	TextEditor editor;
	int flag = 0; // 一开始没有画鼠标
	// void *buffer;
	Screen_Pos cursor_pos;
	init_texteditor(&editor);
	textcursor_init(&cursor_pos, &flag, editor.pos);
	Rectangle poprec = {TEXT_PAGE_X + 200, TEXT_PAGE_Y + 300, 200, 30};
	int ks;
	int ss = 0;
	char ch;
	char readtext[MAX_LINES][MAX_LINE_LENGTH];
	while (1)
	{
		new_txtcursor(&cursor_pos, editor, &flag);
		ks = key_action(&ch);

		switch (ks)
		{
		case ESC:

			break;
		case CTRL_Z: // 退出
			if (ss == 0)
			{

				popmsg(poprec, "not save!", 1);
			}
			else if (ss == 1)
			{
				clr_txtcursor(cursor_pos, &flag);
				return;
			}
			break;
		case CTRL_S:
			ss = save_txtfile(editor.text, "C:\\MEMO\\Test\\a.txt");
			if (ss == 1)
			{
				popmsg(poprec, "Saved!", 1);
			}
			break;
		case ENTER:
			/*just for test*/
			if (editor.cursor_row < MAX_LINES)
			{
				editor.cursor_row++;
				editor.cursor_col = (editor.cursor_col < editor.length[editor.cursor_row]) ? editor.cursor_col : editor.length[editor.cursor_row];

				refresh_curpos(&editor);
			}

			break;
		case BACKSPACE:
			delect_char(&editor);
			break;
		case UP:
			if (editor.cursor_row > 0)
			{
				editor.cursor_row--;
				editor.cursor_col = (editor.cursor_col < editor.length[editor.cursor_row]) ? editor.cursor_col : editor.length[editor.cursor_row];

				refresh_curpos(&editor);
			}
			break;
		case DN:
			if (editor.cursor_row < MAX_LINES)
			{
				editor.cursor_row++;
				editor.cursor_col = (editor.cursor_col < editor.length[editor.cursor_row]) ? editor.cursor_col : editor.length[editor.cursor_row];

				refresh_curpos(&editor);
			}
			break;
		case LEFT:
			if (editor.cursor_col > 0)
			{
				editor.cursor_col--;
				refresh_curpos(&editor);
			}
			else if (editor.cursor_col == 0)
			{
				editor.cursor_row--;
				editor.cursor_col = editor.length[editor.cursor_row];
				refresh_curpos(&editor);
			}
			break;
		case RIGHT:
			if (editor.cursor_col < editor.length[editor.cursor_row])
			{
				editor.cursor_col++;
				refresh_curpos(&editor);
			}
			else if ((editor.cursor_col >= editor.length[editor.cursor_row]) &&
					 editor.cursor_row < editor.cur_num_lines)
			{
				editor.cursor_row++;
				editor.cursor_col = 0;
				refresh_curpos(&editor);
			}
			break;

		case SPACE:
			insert_spacebar(&editor);
			break;
		case OUTCHR:
			insert_char(&editor, ch);

			break;
		default:
			break;
		}
	}
   //	free(txt_cursor_buffer);
}

void ddl_input(char *s, Memo_rec ddl_bar)
{
	char ddl[DDL_LENGTH] = "\0";
	memset(ddl, 0, DDL_LENGTH);
	char tmp;
	char outchar[2];
	outchar[1] = '\0';
	int now = 0;
	int k = 0;
	const int margioff = 2;
	const int font = 8;
	Memo_rec rec = ddl_bar;
	setcolor(_WHITE);
	setlinestyle(0, 0, 1);
	line(ddl_bar.x + 136, rec.y, rec.x + rec.w, rec.y);
	line(rec.x + rec.w, rec.y + rec.h, rec.x + rec.w, rec.y);
	line(ddl_bar.x + 136, rec.y + rec.h, rec.x + rec.w, rec.y + rec.h);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	while (now >= 0)
	{
		k = bioskey(0);
		tmp = (char)(k & 0xff);
		if (tmp == '\r')
		{ // Enter
			break;
		}
		else if (tmp == '\b')
		{ // BACKSPACE
			ddl[now] = '\0';
			setfillstyle(1, _WHITE);
			now--;
			if (now >= 0)
			{
				bar(ddl_bar.x + 136 + margioff + now * font, rec.y + margioff, ddl_bar.x + 136 + margioff + now * font + font, rec.y + margioff + font);
			}
		}
		else if (tmp >= 0x21 && tmp <= 0x7E)
		{
			outchar[0] = tmp;
			ddl[now] = tmp;
			setcolor(_BLACK);
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
			outtextxy(ddl_bar.x + 136 + margioff + now * font, rec.y + margioff, outchar);
			now++;
		}
		if (now >= DDL_LENGTH - 2)
		{
			break;
		}
	}
	strcpy(s, ddl);
}
void editrcpy(TextEditor *target, TextEditor source)
{
	target->cur_num_lines = source.cur_num_lines;
	target->cursor_row = source.cursor_row;
	target->cursor_col = source.cursor_col;
	target->pos.x = source.pos.x;
	target->pos.y = source.pos.y;
	for (int ls = 0; ls < MAX_LINES; ls++)
	{
		target->length[ls] = source.length[ls];
	}
	for (int si = 0; si < MAX_LINES; si++)
	{
		for (int sj = 0; sj < MAX_LINE_LENGTH; sj++)
		{
			target->text[si][sj] = source.text[si][sj];
		}
	}
	return;
}
/**
 * @brief
 * @note mode 0-addnew    1-edit
 * @param editor
 * @param text_bar
 * @param mode
 */
int text_input(TextEditor **text_editor, Memo_rec text_bar, int mode, int *isdeal)
{

	// TextEditor editor;
	int flag = 0;
	int ks = 0;
	char ch;
	int exit_s = 0;
	// void *buffer;
	Screen_Pos cursor_pos;
	if (mode == 0)
	{
		init_texteditor(*text_editor);
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		setfillstyle(1, _WHITE);
		bar(text_bar.x, text_bar.y, text_bar.x + text_bar.w, text_bar.y + text_bar.h);
	}
	else if (mode == 1)
	{
	}

	textcursor_init(&cursor_pos, &flag, (*text_editor)->pos);
	Rectangle poprec = {TEXT_PAGE_X + 200, TEXT_PAGE_Y + 300, 200, 30};
	while (1)
	{
		ks = key_action(&ch);
		new_txtcursor(&cursor_pos, **text_editor, &flag);
		switch (ks)
		{
		case ESC:

			break;
		case CTRL_Z: // 退出
			/*if(exit_s==1){
			free(txt_cursor_buffer);
			clr_txtcursor(cursor_pos,&flag);
			return ;
			}
			else {
				popmsg(poprec,"not save!",1);
			}*/
			if (mode == 0) // add-mode
			{
				if (exit_s == 1)
				{
					*isdeal = 1;
					// free(txt_cursor_buffer);
					clr_txtcursor(cursor_pos, &flag);
					return 1;
				}

				else
				{
					popmsg(poprec, "not save!", 1);
					break;
				}
			}
			else if (mode == 1)
			{				 // edit-mode
				*isdeal = 1; // 维护数据
				// free(txt_cursor_buffer);
				clr_txtcursor(cursor_pos, &flag);
				draw_addmemo_back();
				return 1;
			}

		case CTRL_S:
			/*for (int si = 0; si < 60; si++)
			{
				for(int sj = 0;sj < 60; sj ++){
					text[si][sj] = editor->text[si][sj];
				}
			}*/
			exit_s = 1;
			break;
		case ENTER:
			/*just for test*/
			if ((*text_editor)->cursor_row + 1 < MAX_LINES)
			{
				if ((*text_editor)->cursor_row < MAX_LINES)
				{
					(*text_editor)->cursor_row++;
					(*text_editor)->cursor_col = ((*text_editor)->cursor_col < (*text_editor)->length[(*text_editor)->cursor_row]) ? (*text_editor)->cursor_col : (*text_editor)->length[(*text_editor)->cursor_row];

					refresh_curpos(*text_editor);
				}
			}

			break;
		case BACKSPACE:
			/*modifed   add if judge*/
			if((*text_editor)->cursor_col -1 >=0){
				delect_char(*text_editor);
			}
			
			break;
		case UP:
			if ((*text_editor)->cursor_row > 0)
			{
				(*text_editor)->cursor_row--;
				(*text_editor)->cursor_col = ((*text_editor)->cursor_col < (*text_editor)->length[(*text_editor)->cursor_row]) ? (*text_editor)->cursor_col : (*text_editor)->length[(*text_editor)->cursor_row];

				refresh_curpos(*text_editor);
			}
			break;
		case DN:
			if ((*text_editor)->cursor_row < MAX_LINES)
			{
				(*text_editor)->cursor_row++;
				(*text_editor)->cursor_col = ((*text_editor)->cursor_col < (*text_editor)->length[(*text_editor)->cursor_row]) ? (*text_editor)->cursor_col : (*text_editor)->length[(*text_editor)->cursor_row];

				refresh_curpos(*text_editor);
			}
			break;
		case LEFT:
			
			if ((*text_editor)->cursor_col > 0)
			{
				(*text_editor)->cursor_col--;
				refresh_curpos(*text_editor);
			}
			else if ((*text_editor)->cursor_col == 0)
			{	if((*text_editor)->cursor_row-1>=0){/*@modifed add if juedge*/
				(*text_editor)->cursor_row--;
				(*text_editor)->cursor_col = (*text_editor)->length[(*text_editor)->cursor_row];
				refresh_curpos(*text_editor);
			}
				
			}
			break;
		case RIGHT:
			if ((*text_editor)->cursor_col < (*text_editor)->length[(*text_editor)->cursor_row])
			{
				(*text_editor)->cursor_col++;
				refresh_curpos(*text_editor);
			}
			else if (((*text_editor)->cursor_col >= (*text_editor)->length[(*text_editor)->cursor_row]) &&
					 (*text_editor)->cursor_row < (*text_editor)->cur_num_lines)
			{
				(*text_editor)->cursor_row++;
				(*text_editor)->cursor_col = 0;
				refresh_curpos(*text_editor);
			}
			break;
		case CTRL_D:
			if (mode == 0)
			{
				break;
			}
			else if (mode == 1)
			{
				*isdeal = 0; /*0 mean dealed*/
				// free(txt_cursor_buffer);
				clr_txtcursor(cursor_pos, &flag);
				draw_addmemo_back();
				return 1;
			}

		case SPACE:
			// insert_spacebar(*editor);
			insert_char(*text_editor, ' ');
			break;
		case OUTCHR:
			insert_char(*text_editor, ch);
			break;

		default:
			break;
		}
	}
}
void show_title(char title[51])
{
	const int margioff = 4;
	Memo_rec tit_bar = {400, 80, 968 - 400, 30};
	setfillstyle(1, _WHITE);
	bar(tit_bar.x, tit_bar.y, tit_bar.x + tit_bar.w, tit_bar.y + tit_bar.h);
	setcolor(_BLACK);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	outtextxy(tit_bar.x + margioff, tit_bar.y + margioff, title);
}
void show_task_body(TaskData *databody) /*@modifed args: Taskdata --> Taskdata* */
{

	draw_addmemo_back();
	show_title(databody->task);
	TextEditor *new_editor = (TextEditor *)malloc(sizeof(TextEditor));
	if (new_editor == NULL)
	{
		printf("[show task_body]not mem\n");
	}
	FILE *fp;
	FILE *fpbmp;
	if ((fp = fopen(databody->editorpath, "rb")) == NULL)
	{
		fclose(fp);
		free(new_editor);
		//printf("editor file open error[show body]");
		delay(1000);
		return;
	}
	else
	{
		fread(new_editor, sizeof(TextEditor), 1, fp);
		fclose(fp);
	}
	protect_text_func(new_editor); /**/
	// strcpy(sometext, new_editor->text[0]);
	if ((fpbmp = fopen(databody->imgpath, "rb")) == NULL)
	{
		fclose(fpbmp);
		show_text(new_editor->text);
		free(new_editor);
		return;
	}
	else
	{
		show_text(new_editor->text);
		BMPOpen(leftx, topy, databody->imgpath);
		free(new_editor);
		return;
	}
}
TextEditor *ret_editor(char *path)
{
	TextEditor *edior = (TextEditor *)malloc(sizeof(TextEditor));
	if (edior == NULL)
	{
		printf("[ret _editor ] not mem\n");
	}
	FILE *fp;
	fp = fopen(path, "rb");
	fread(edior, sizeof(TextEditor), 1, fp);
	fclose(fp);
	return edior;
}

void sort_list(TaskNode **list)
{
	TaskNode *current = *list;
	TaskNode *index = NULL;
	TaskData tmp;
	if (list == NULL)
	{
		return;
	}
	else
	{
		while (current != NULL)
		{
			index = current->next_tasknode;

			while (index != NULL)
			{
				if (index->cur_task.level >= current->cur_task.level)
				{
					tmp = current->cur_task;
					current->cur_task = index->cur_task;
					index->cur_task = tmp;
				}
				index = index->next_tasknode;
			}

			current = current->next_tasknode;
		}
	}
}

/**
 * @brief init a TaskData all zero
 * for init_usrtask()
 *
 * @param data
 */
void init_taskdata(TaskData *data)
{
	data->level = 101;
	data->isdeal = 1;
	// init_texteditor(&(data->editor));
	memset(data->editorpath, 0, PATH_LENGTH);
	memset(data->id, 0, ID_LENGTH);
	//	data->id = ;
	memset(data->imgpath, 0, PATH_LENGTH);
	memset(data->task, 0, TASK_LENGTH);
	memset(data->deadline, 0, DDL_LENGTH);
	//	data->imgpath = ;
	//	data->task = "\0";
	//	data->deadline = "\0";
	char s[INIT_DATA_LENGTH];
	memset(s, 0, INIT_DATA_LENGTH);
	receive_time(s);
	strcpy(data->initdata, s);
	return;
}

/**
 * @brief
 * @note pos :1.2.3....
 */
TaskNode find_taskndoe_bypos(TaskNode *head, int pos)
{
	TaskNode *list = head;
	for (int i = 0; i < pos - 1; i++)
	{
		if (list == NULL)
		{
			//	return NULL;
		}
		else
		{
			list = list->next_tasknode;
		}
	}
	return *list;
}

/**
 * Function:
 * @brief
 *
 */

TaskNode *delete_deal_task(TaskNode *head)
{
	TaskNode dummy;
	dummy.next_tasknode = head;
	TaskNode *prev = &dummy;
	TaskNode *curr = head;
	while (curr != NULL)
	{
		if (curr->cur_task.isdeal == 0)
		{
			prev->next_tasknode = curr->next_tasknode;
			free(curr);
			curr = prev->next_tasknode;
		}
		else
		{
			prev = curr;
			curr = curr->next_tasknode;
		}
	}
	return dummy.next_tasknode;
}

int protect_text_func(TextEditor *texteditor)
{
	int cur_col = 0;
	/*错误数据退出*/
	if (texteditor->cur_num_lines < 0 || texteditor->cursor_col < 0 || texteditor->cursor_row < 0)
	{
		return -1;
	}
	/*根据当前行数将之后行的数据置'\0'*/
	if (texteditor->cur_num_lines > 0)
	{
		for (int i = texteditor->cur_num_lines; i < MAX_LINES; i++)
		{
			memset(texteditor->text[i], 0, MAX_LINE_LENGTH);
		}
	}
	/*将每行置后的数据赋值一个 0 */
	for (int j = 0; j < MAX_LINES; j++)
	{
		cur_col = texteditor->length[j];
		texteditor->text[j][cur_col + 1] = '\0';
	}
	return 1;
}

void draw_taskbox(int posx, int posy, TaskData data)
{

	char task[TASK_LENGTH];
	int k;
	char sometext[MAX_LINE_LENGTH];
	memset(sometext, 0, MAX_LINE_LENGTH);
	memset(task, 0, TASK_LENGTH);
	/*for save memory we use file to read information*/

	TextEditor *new_editor = (TextEditor *)malloc(sizeof(TextEditor));
	if (new_editor == NULL)
	{
		printf("[draw_tasknox ] not mem\n");
		return;
	}
	FILE *fp_tasknbox;
	// printf("[draw_taskbox]editor:%s\n", data.editorpath);

	if ((fp_tasknbox = fopen(data.editorpath, "rb")) == NULL)
	{
		// logmessage("[svef]cnt\n");
		printf("[draw_tasklist]cant open %s\n", data.editorpath);

		fclose(fp_tasknbox);
		free(new_editor);
		return;
	}

	fread(new_editor, sizeof(TextEditor), 1, fp_tasknbox);
	fclose(fp_tasknbox);
	// strcpy(sometext, (new_editor->text)[0]);
	for (int j = 0; j < 17; j++)
	{
		sometext[j] = (new_editor->text)[0][j];
	}
	// logmessage(sometext);
	free(new_editor);

	sometext[20] = '\0';
	sometext[19] = '.';
	sometext[18] = '.';
	sometext[17] = '.';
	// strcpy(task, data.task);
	for (k = 0; k < 17; k++)
	{
		task[k] = data.task[k];
	}
	task[20] = '\0';
	task[19] = '.';
	task[18] = '.';
	task[17] = '.';

	setcolor(_WHITE);
	rectangle(posx, posy, posx + 310, posy + 50);
	setfillstyle(1, _Grey93);
	bar(posx, posy, posx + 310, posy + 50);
	switch (data.level)
	{
	case 1:
		setfillstyle(1, _Green);
		break;
	case 2:
		setfillstyle(1, _YELLOW);
		break;
	case 3:
		setfillstyle(1, _RED);
		break;
	default:
		setfillstyle(1, _GRAY);
		break;
	}
	fillellipse(posx + 20 + 5, posy + 20 + 5, 20, 20);
	setcolor(BLACK);
	settextstyle(0, 0, 1);
	outtextxy(posx + 50, posy + 10, task);
	outtextxy(posx + 50, posy + 30, sometext);
	outtextxy(posx + 220, posy + 10, data.deadline);
	outtextxy(posx + 220, posy + 30, data.initdata);
	if (data.isdeal != 1)
	{
		setcolor(_BLACK);
		setlinestyle(0, 0, 1);
		line(posx - 5, posy + 25, posx + 310 + 5, posy + 25);
	}
	// printf("finished draw");
	return;
}

// 4.18 0:11 原UB.dat文件写入 两个num无误、others_path_poor[i]无误
// 4.18 0:24 读取UB.dat文件 两个num无误、others_path_poor[i]无误
int save_usrmemo(Tasks *usrtask)
{
	char usr_path[PATH_LENGTH] = ROOTUSRPATH;
	strcat(usr_path, usrtask->usr);
	char gap[4] = FILEGAP_SIG;
	strcat(usr_path, gap);
	strcat(usr_path, "ub.dat");

	FILE *usr_fp;
	if ((usr_fp = fopen(usr_path, "wb+")) == NULL)
	{
		// logmessage("[svef]cnt\n");
		// printf("[save]cant open %s\n", usr_path);
		fclose(usr_fp);
		return 0;
	}
	else
	{
		fwrite(usrtask, sizeof(Tasks), 1, usr_fp);
		fclose(usr_fp);
		return 1;
	}

	/*Tasks *test;
	if ((usr_fp = fopen(usr_path, "rb+")) == NULL)
	{
		// logmessage("[svef]cnt\n");
		printf("[save]cant open %s\n", usr_path);
		fclose(usr_fp);
		return 0;
	}else{
		fread(test,sizeof(Tasks),1,usr_fp);
		fclose(usr_fp);
		return 1 ;

	}*/
}
int edit_task(char *edit_file_path)
{
	FILE *edit_fp;
	FILE *text_fp;
	TaskData *edit_data = (TaskData *)malloc(sizeof(TaskData));
	int es = 0;
	char edit_text_path[PATH_LENGTH];
	if (edit_data == NULL)
	{
		printf("[edit_data] malloc err");
		return 0;
	}
	if ((edit_fp = fopen(edit_file_path, "rb")) == NULL)
	{
		// logmessage("[svef]cnt\n");
		//printf("[edit]cant open %s\n", edit_file_path);

		fclose(edit_fp);
		free(edit_data);
		return 0;
	}
	else
	{
		fread(edit_data, sizeof(TaskData), 1, edit_fp);
		fclose(edit_fp);
		strcpy(edit_text_path, edit_data->editorpath);
		show_task_body(edit_data);
		// free(edit_data);
		TextEditor *edit_text = (TextEditor *)malloc(sizeof(TextEditor));

		if ((text_fp = fopen(edit_text_path, "rb")) == NULL)
		{
			//printf("[edit]cant open %s\n", edit_file_path);
			free(edit_text);
			fclose(text_fp);
			return 0;
		}
		else
		{
			fread(edit_text, sizeof(TextEditor), 1, text_fp);
			fclose(text_fp);
			protect_text_func(edit_text);
			Memo_rec text_bar = {400, 120, 968 - 400, 700 - 120};
			es = text_input(&edit_text, text_bar, 1, &(edit_data->isdeal));
			if (es == 1)
			{
				if ((edit_fp = fopen(edit_file_path, "wb")) == NULL)
				{
					//printf("[edit-end]cant open %s\n", edit_file_path);
					free(edit_data);
					free(edit_text);
					fclose(edit_fp);
					return 0;
				}
				else
				{
					fwrite(edit_data, sizeof(TaskData), 1, edit_fp);
					free(edit_data);
					fclose(edit_fp);
					if ((text_fp = fopen(edit_text_path, "wb")) == NULL)
					{
						//printf("[edit-end]cant open %s\n", edit_text_path);
						// free(edit_data);
						free(edit_text);
						fclose(text_fp);
						return 0;
					}
					else
					{
						fwrite(edit_text, sizeof(TextEditor), 1, text_fp);
						free(edit_text);

						fclose(text_fp);
						return 1;
					}
				}
			}
			else
			{
				//printf("edit-text err\n");
				free(edit_data);
				free(edit_text);
				return 0;
			}
		}
	}
}

int delete_task_byid(Tasks *usrtask)
{
	int rets = find_deal_taskid(*usrtask); /*查找isdeal id 索引*/
	int key_delet = usrtask->idpoor[rets];
	int i = 0;
	if (rets == -1)
	{
		return 0; // delet task err
	}
	else
	{
		for (i = rets; i < 10 - 1; i++)
		{
			usrtask->idpoor[i] = usrtask->idpoor[i + 1];
		}									 /*前移*/
		usrtask->idpoor[10 - 1] = key_delet; /*置尾*/
		usrtask->num--;
		return 1;
	}
}
int find_deal_taskid(Tasks utask)
{
	FILE *fp;
	char tmp_path[PATH_LENGTH];
	int i;
	for (i = 0; i < utask.num; i++)
	{
		// strcpy(tmp_path,num_id2path(utask.usr,utask.idpoor[i],0));
		num_id2path(utask.usr, utask.idpoor[i], 0, tmp_path);

		if ((fp = fopen(tmp_path, "rb")) == NULL)
		{
			// logmessage("[svef]cnt\n");
			printf("[find_dealtaskid]cant open %s\n", tmp_path);

			fclose(fp);
			return -1;
		}
		else
		{
			TaskData *tmpdata = (TaskData *)malloc(sizeof(TaskData));
			fread(tmpdata, sizeof(TaskData), 1, fp);
			if (tmpdata->isdeal != 1)
			{
				free(tmpdata);
				fclose(fp);
				return i;
			}
			else
			{
				free(tmpdata);
				fclose(fp);
				continue;
			}
		}
	}
	return -1;
}
/*************************************************************************************************************************/
/*************************************************************************************************************************/
/**************************************************************************************************************************/
void level_choose(int *level, Memo_rec level_bar, Memo_rec greenhigh, Memo_rec yellowmid, Memo_rec redlow)
{
	setcolor(_WHITE);
	setlinestyle(0, 0, 1);
	rectangle(level_bar.x, level_bar.y, level_bar.x + level_bar.w, level_bar.y + level_bar.h);

	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	rectangle(greenhigh.x, greenhigh.y, greenhigh.x + greenhigh.w, greenhigh.y + greenhigh.h);
	int ks;
	char ch;
	int move = 0;
	int direction = 0;
	*level = 1;
	while (1)
	{
		ks = key_action(&ch);

		switch (ks)
		{
		case SPACE:
			return;
		case LEFT:
			direction = 0;
			if (move == 1 || move == 2)
			{
				movebox(greenhigh, yellowmid, redlow, move, direction);
				move--;
				(*level)--;
			}
			break;
		case RIGHT:
			direction = 1;
			if (move == 1 || move == 0)
			{
				movebox(greenhigh, yellowmid, redlow, move, direction);
				move++;
				(*level)++;
			}
			break;
		}
	}
}

void movebox(Memo_rec greenhigh, Memo_rec yellowmid, Memo_rec redlow, int move, int direction)
{
	if (move == 0)
	{
		setfillstyle(1, _Green);
		bar(greenhigh.x, greenhigh.y, greenhigh.x + greenhigh.w, greenhigh.y + greenhigh.h);
		setcolor(_BLACK);
		setlinestyle(0, 0, 1);
		rectangle(yellowmid.x, yellowmid.y, yellowmid.x + yellowmid.w, yellowmid.y + yellowmid.h);
	}
	else if (move == 2)
	{
		setfillstyle(1, _RED);
		bar(redlow.x, redlow.y, redlow.x + redlow.w, redlow.y + redlow.h);
		setcolor(_BLACK);
		setlinestyle(0, 0, 1);
		rectangle(yellowmid.x, yellowmid.y, yellowmid.x + yellowmid.w, yellowmid.y + yellowmid.h);
	}
	else if (move == 1)
	{
		if (direction == 0) // left
		{
			setfillstyle(1, _YELLOW);
			bar(yellowmid.x, yellowmid.y, yellowmid.x + yellowmid.w, yellowmid.y + yellowmid.h);
			setcolor(_BLACK);
			setlinestyle(0, 0, 1);
			rectangle(greenhigh.x, greenhigh.y, greenhigh.x + greenhigh.w, greenhigh.y + greenhigh.h);
		}
		else if (direction == 1) // right
		{
			setfillstyle(1, _YELLOW);
			bar(yellowmid.x, yellowmid.y, yellowmid.x + yellowmid.w, yellowmid.y + yellowmid.h);
			setcolor(_BLACK);
			setlinestyle(0, 0, 1);
			rectangle(redlow.x, redlow.y, redlow.x + redlow.w, redlow.y + redlow.h);
		}
	}
}

void insert_photo(char *s, Memo_rec add_photo, Memo_rec gphoto_name, Memo_rec wphoto_name, char *tit, Memo_rec tit_bar, TextEditor *editor, Memo_rec text_bar, char *id, char *usrname)
{
	char photoname[15] = {'\0'};
	// memset(photoname);
	char photopath[PATH_LENGTH] = PHOTOPATH;
	char savephpath[PATH_LENGTH] = ROOTDBPATH;
	photoinfor *Photoinfo;
	long int *oldwidth, *oldheight;
	long int Oldwidth = 0, Oldheight = 0;
	float proportion;
	Memo_rec move_bar = {710, 8, 112, 24};
	Memo_rec cancel_bar = {710, 48, 112, 24};
	int ifmove = 0;
	oldwidth = &Oldwidth;
	oldheight = &Oldheight;
	photoname_inputbox(gphoto_name, wphoto_name);
	photoname_input(photoname, wphoto_name);
	setfillstyle(1, _LIGHTGRAY);
	bar(gphoto_name.x, gphoto_name.y, gphoto_name.x + gphoto_name.w, gphoto_name.y + gphoto_name.h);
	newphotoname(photopath, photoname);									
	BMPinsert(fmidx, fmidy, photopath, oldwidth, oldheight, Photoinfo); 
	ifmove = photo_move(move_bar, cancel_bar);
	setfillstyle(1, _LIGHTGRAY);
	bar(move_bar.x, move_bar.y, move_bar.x + move_bar.w, move_bar.y + move_bar.h);
	bar(cancel_bar.x, cancel_bar.y, cancel_bar.x + cancel_bar.w, cancel_bar.y + cancel_bar.h);
	if (ifmove == 0)
	{
		draw_addmemo_back();
		show_newtitle(tit, tit_bar);
		show_text(editor->text);
		return;
	}
	else if(ifmove == 1)
	{
		proportion = ratio(oldwidth, oldheight);
		fangsuo(Photoinfo, proportion, proportion);
	}

	show_newtitle(tit, tit_bar);
	show_text(editor->text);
	strcat(savephpath, usrname);
	strcat(savephpath, "\\p");
	strcat(savephpath, id);
	strcat(savephpath, ".dat");

	BMPsave(savephpath);
	strcpy(s, savephpath); // problem newpath  need change  done
}


void photoname_inputbox(Memo_rec gphoto_name, Memo_rec wphoto_name)
{
	setfillstyle(1, _GRAY);
	bar(gphoto_name.x, gphoto_name.y, gphoto_name.x + gphoto_name.w, gphoto_name.y + gphoto_name.h);
	setfillstyle(1, _WHITE);
	bar(wphoto_name.x, wphoto_name.y, wphoto_name.x + wphoto_name.w, wphoto_name.y + wphoto_name.h);
	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	rectangle(gphoto_name.x, gphoto_name.y, gphoto_name.x + gphoto_name.w, gphoto_name.y + gphoto_name.h);
	rectangle(wphoto_name.x, wphoto_name.y, wphoto_name.x + wphoto_name.w, wphoto_name.y + wphoto_name.h);
}

void photoname_input(char *s, Memo_rec wphoto_name)
{
	char photoname[15] = {'\0'};
	char tmp;
	char outchar[2];
	outchar[1] = '\0';
	int now = 0;
	int k = 0;
	const int margin = 4;
	const int size = 16;
	if (now >= 0 && now <= 7)
	{
		while (1)
		{
			k = bioskey(0);
			tmp = (char)(k & 0xff);
			if (tmp == '\r')
			{
				photoname[now] = '\0'; //!!important 类似文本输入优化 4.8 （未完成）
				break;
			}
			else if (tmp == '\b')
			{
				if (now > 0 && now <= 8)
				{
					now--;
					photoname[now] = '\0';
					setfillstyle(1, _WHITE);
					bar(wphoto_name.x + margin + now * size, wphoto_name.y + margin, wphoto_name.x + margin + (now + 1) * size, wphoto_name.y + margin + size);
				}
			}
			else if ((tmp >= 0x21 && tmp <= 0x7E) || (tmp == ' '))
			{
				if (now >= 0 && now <= 7)
				{
					outchar[0] = tmp;
					photoname[now] = tmp;
					setcolor(_BLACK);
					settextstyle(0, 0, 2);
					outtextxy(wphoto_name.x + margin + now * size, wphoto_name.y + margin, outchar);
					now++;
				}
			}
		}
	}
	strcpy(s, photoname);
}

void newphotoname(char *photopath, char *photoname)
{
	char type[5] = ".bmp";
	strcat(photopath, photoname);
	strcat(photopath, type);
}

int photo_move(Memo_rec move_bar, Memo_rec cancel_bar)
{
	int ks;
	char ch;
	int now = 0;
	// draw move box
	setfillstyle(1, _GRAY);
	bar(move_bar.x, move_bar.y, move_bar.x + move_bar.w, move_bar.y + move_bar.h);
	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	rectangle(move_bar.x, move_bar.y, move_bar.x + move_bar.w, move_bar.y + move_bar.h);
	settextstyle(0, 0, 2);
	outtextxy(move_bar.x + 8, move_bar.y + 4, "MOVE");
	//draw cancel box
	setfillstyle(1, _GRAY);
	bar(cancel_bar.x, cancel_bar.y, cancel_bar.x + cancel_bar.w, cancel_bar.y + cancel_bar.h);
	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	rectangle(cancel_bar.x, cancel_bar.y, cancel_bar.x + cancel_bar.w, cancel_bar.y + cancel_bar.h);
	settextstyle(0, 0, 2);
	outtextxy(cancel_bar.x + 8, cancel_bar.y + 4, "CANCEL");

	setcolor(_RED);
	setlinestyle(0,0,1);
	rectangle(move_bar.x, move_bar.y, move_bar.x + move_bar.w, move_bar.y + move_bar.h);

	// choose move or cancel
	while (1)
	{
		ks = key_action(&ch);
		switch (ks)
		{
		case SPACE:
			if(now == 0)
			{
				return 1;
			}
			else if(now == 1)
			{
				return 0;
			}
		case UP:
			if(now == 1)
			{
				setcolor(_BLACK);
				setlinestyle(0,0,1);
				rectangle(cancel_bar.x, cancel_bar.y, cancel_bar.x + cancel_bar.w, cancel_bar.y + cancel_bar.h);
				setcolor(_RED);
				rectangle(move_bar.x, move_bar.y, move_bar.x + move_bar.w, move_bar.y + move_bar.h);
				now--;
			}
			break;
		case DN:
			if(now == 0)
			{
				setcolor(_BLACK);
				setlinestyle(0,0,1);
				rectangle(move_bar.x, move_bar.y, move_bar.x + move_bar.w, move_bar.y + move_bar.h);
				setcolor(_RED);
				rectangle(cancel_bar.x, cancel_bar.y, cancel_bar.x + cancel_bar.w, cancel_bar.y + cancel_bar.h);
				now++;
			}
			break;
		}
	}
}


void show_newtitle(char *s, Memo_rec tit_bar)
{
	const int margioff = 4;
	setcolor(_BLACK);
	settextstyle(0, 0, 2);
	outtextxy(tit_bar.x + margioff, tit_bar.y + margioff, s);
}

void show_newtext(char text[MAX_LINES][MAX_LINE_LENGTH]) // 4.9 problem鐩稿簲绉讳綅鎵╁睍闂锛堟湭瑙ｅ喅锛?
{
	int i = 0;
	int j = 0;
	int k = 0;
	char newtext[MAX_LINES * MAX_LINE_LENGTH];
	memset(newtext, 0, MAX_LINES * MAX_LINE_LENGTH);
	Screen_Pos pos;
	setcolor(_BLACK);
	settextstyle(0, 0, 1);
	for (i = 0; i < MAX_LINES; i++)
	{
		for (j = 0; j < MAX_LINE_LENGTH; j++)
		{
			newtext[k] = text[i][j];
			k++;
		}
	}

	k = 0;

	for (i = 0; i < MAX_NLINES; i++)
	{
		for (j = 0; j < MAX_LINE_NLENGTH; j++)
		{
			pos.x = TEXT_PAGE_X + MARGIN_OFF + 10 * j;
			pos.y = TEXT_PAGE_Y + MARGIN_OFF + 12 * i;
			display_char(pos, newtext[k]);
			k++;
		}
	}
	for (i = MAX_NLINES; i < MAX_LFTLINES; i++)
	{
		for (j = 0; j < MAX_LINE_LENGTH; j++)
		{
			pos.x = TEXT_PAGE_X + MARGIN_OFF + 10 * j;
			pos.y = TEXT_PAGE_Y + MARGIN_OFF + 12 * i;
			display_char(pos, newtext[k]);
		}
	}
}

void sharename(char *s)
{
	char share_name[15] = {'\0'};
	Memo_rec gshare_bar = {185, 638, 154, 28};
	Memo_rec wshare_bar = {191, 640, 142, 24};

	setfillstyle(1, _GRAY);
	bar(gshare_bar.x, gshare_bar.y, gshare_bar.x + gshare_bar.w, gshare_bar.y + gshare_bar.h);
	setfillstyle(1, _WHITE);
	bar(wshare_bar.x, wshare_bar.y, wshare_bar.x + wshare_bar.w, wshare_bar.y + wshare_bar.h);
	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	rectangle(gshare_bar.x, gshare_bar.y, gshare_bar.x + gshare_bar.w, gshare_bar.y + gshare_bar.h);
	rectangle(wshare_bar.x, wshare_bar.y, wshare_bar.x + wshare_bar.w, wshare_bar.y + wshare_bar.h);

	photoname_input(share_name, wshare_bar);
	strcpy(s, share_name);

	setfillstyle(1, _LIGHTGRAY);
	bar(gshare_bar.x, gshare_bar.y, gshare_bar.x + gshare_bar.w, gshare_bar.y + gshare_bar.h);
}

int click_share()
{
	int ks;
	char ch;
	Memo_rec share_bar = {205, 640, 88, 24};
	// draw move box
	setfillstyle(1, _GRAY);
	bar(share_bar.x, share_bar.y, share_bar.x + share_bar.w, share_bar.y + share_bar.h);
	setcolor(_BLACK);
	setlinestyle(0, 0, 1);
	rectangle(share_bar.x, share_bar.y, share_bar.x + share_bar.w, share_bar.y + share_bar.h);
	settextstyle(0, 0, 2);
	outtextxy(share_bar.x + 4, share_bar.y + 4, "Share");
	// choose share
	while (1)
	{
		ks = key_action(&ch);
		switch (ks)
		{
		case SPACE:
			setfillstyle(1, _LIGHTGRAY);
			bar(share_bar.x, share_bar.y, share_bar.x + share_bar.w, share_bar.y + share_bar.h);
			return 1;
		}
	}
}

// 可以从自己的被分享列表里面删除，但是不能删除分享用户的源文件 4.16 need change

void tite_input(char *s, Memo_rec tit_bar)
{
	char title[TASK_LENGTH];
	memset(title, 0, TASK_LENGTH);
	char tmp;
	char outchar[2];
	outchar[1] = '\0';
	int now = 0;
	int k = 0;
	const int margioff = 4;
	const int font = 16;
	Memo_rec rec = tit_bar;
	setfillstyle(1, _WHITE);
	bar(tit_bar.x, tit_bar.y, tit_bar.x + tit_bar.w, tit_bar.y + tit_bar.h);
	while (now >= 0)
	{
		k = bioskey(0);
		tmp = (char)(k & 0xff);
		if (tmp == '\r')
		{ // Enter
			break;
		}
		else if (tmp == '\b')
		{ // BACKSPACE

			title[now] = '\0';
			setfillstyle(1, _WHITE);
			now--;
			if (now >= 0)
			{
				bar(rec.x + margioff + now * font, rec.y + margioff, rec.x + margioff + now * font + font, rec.y + margioff + font);
			}
		}

		else if ((tmp >= 0x21 && tmp <= 0x7E) || (tmp == ' '))
		{
			outchar[0] = tmp;
			title[now] = tmp;
			setcolor(_BLACK);
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
			outtextxy(rec.x + margioff + now * font, rec.y + margioff, outchar);
			now++;
		}
		if (now >= TASK_LENGTH - 2)
		{ // yuejie
			break;
		}
	}
	strcpy(s, title);
}

int public_share(char *edit_file_path, char *usrshare)
{
	FILE *edit_fp;
	FILE *share_fp;
	TaskData *edit_data = (TaskData *)malloc(sizeof(TaskData)); // 用于展示任务内容
	Tasks *share_data = (Tasks *)malloc(sizeof(Tasks));			// 被修改的UB.dat 结构体
	char file_path[PATH_LENGTH];								// 任务地址
	char share_path[PATH_LENGTH] = "C:\\MEMO\\USERS\\";			// 共享用户地址
	int i = 0;

	strcat(share_path, usrshare);
	strcat(share_path, "\\");
	strcat(share_path, "UB.dat");
	strcpy(file_path, edit_file_path);

	// 是否成功分配内存
	if (edit_data == NULL)
	{
		//printf("[edit_data] malloc err");
		return 0;
	}
	if (share_data == NULL)
	{
		printf("[edit_data] malloc err");
		return 0;
	}

	// 能否正常打开该任务文件
	if ((edit_fp = fopen(file_path, "rb")) == NULL)
	{
		// logmessage("[svef]cnt\n");
		//printf("[edit]cant open %s\n", edit_file_path);

		fclose(edit_fp);
		free(edit_data);
		free(share_data);
		return 0;
	}
	else
	{
		fread(edit_data, sizeof(TaskData), 1, edit_fp);
		fclose(edit_fp);
		// 显示任务内容
		show_task_body(edit_data);

		// share text or path(now path)
		// 将打开路径写入共享用户的结构体
		if ((share_fp = fopen(share_path, "rb")) == NULL)
		{
			//printf("[newedit]cant open %s\n", share_path);

			fclose(share_fp);
			free(edit_data);
			free(share_data);
			return 0;
		}
		else
		{
			fread(share_data, sizeof(Tasks), 1, share_fp);
			fclose(share_fp);
			if (share_data->other_task_num >= 3)
			{
				free(edit_data);
				free(share_data);
				return 0;
			}

			for (i = 0; i < OTHER_TASK_NUM; i++)
			{
				if (strlen(share_data->others_path_poor[i]) == 0)
				{
					break;
				}
				if (strcmp(share_data->others_path_poor[i], edit_file_path) == 0)
				{
					free(edit_data);
					free(share_data);
					return 0;
				}
			}

			strcpy(share_data->others_path_poor[i], file_path);
			// share_data->other_task_num = 1;
			share_data->other_task_num = i + 1;
			if ((share_fp = fopen(share_path, "wb")) == NULL)
			{
			//	printf("[saveedit]cant open %s\n", share_path);

				fclose(share_fp);
				free(edit_data);
				free(share_data);
				return 0;
			}
			else
			{
				fwrite(share_data, sizeof(Tasks), 1, share_fp);
				fclose(share_fp);
				free(edit_data);
				free(share_data);
				return 1;
			}
		}
	}
}
