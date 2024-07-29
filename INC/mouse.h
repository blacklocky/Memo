#ifndef _mouse_h_
#define _mouse_h_

#include<conio.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include"gramd.h"

#define MOUS_X_MAX 1009 //(1024-15)
#define MOUS_Y_MAX 758

typedef struct {
	int posx,posy;
	int click;//��� nothing = 0 left =1 right = 2
	
    
    union REGS regs;
   
	
}Mouse;

//extern Mouse mos;   
int mouse_press(int x1, int y1, int x2, int y2);//����ڿ��е�����򷵻�1���ڿ���δ������򷵻�2�����ڿ����򷵻�0
void mouse(int,int);//������
void mouseinit(void);//��ʼ��
//void mou_pos(int*,int*,int*);//�������λ��
void mread(int *,int *,int*);//�����겻��
void save_bk_mou(int x,int y);//����걳��
void clrmous(int x,int y);//������
void drawmous(int x,int y);//�����
void newmouse(Mouse *m);   //�������
int ismouse_clickbt(Mouse mos,int x1,int y1,int x2,int y2);

extern int MouseX;
extern int MouseY;
extern int MouseS;
extern int press;
extern union REGS regs;
#endif