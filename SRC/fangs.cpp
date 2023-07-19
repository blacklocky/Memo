#include <stdio.h>
#include "fangs.h"
#include "photo.h"
#include <graphics.h>
#include "gramd.h"
#include "config.h"
#include "memo.h"
int fangsuo(photoinfor *Photoinfo,float xtimes,float ytimes)
{
	FILE *fp;
	int newwidth,newheight; //������ĳ��� 
	int x0 = (Photoinfo->x2 - Photoinfo->x1)/2 + (Photoinfo->x1);  //�������� 
	int y0 = (Photoinfo->y2 - Photoinfo->y1)/2 + (Photoinfo->y1);
	int nx1,nx2;  // ������ͼƬλ�� 
	int ny1,ny2; 
	float time_progress = 0.0;
	int i,j;
	int x,y;
	int tempx1,tempx2,tempy1,tempy2;//��Ӧ��ԭ���ص�����+����λ��Ϊx0 y0 
	int newcolor; 
	
	newwidth = (Photoinfo->x2 - Photoinfo->x1) * xtimes;
	newheight = (Photoinfo->y2 - Photoinfo->y1) * ytimes;
	nx1 = x0 + (-1)*newwidth/2;
	nx2 = x0 + newwidth/2 + newwidth%2;
	ny1 = y0 + (-1)*newheight/2;
	ny2 = y0 + newheight/2 + newheight%2;
	if((fp = fopen("C:\\MEMO\\TEMP\\temp1.txt","wb"))==NULL){
		fclose(fp);
		return -1;
	}
	fwrite(&newwidth,2,1,fp);
	fwrite(&newheight,2,1,fp);	
	for(i = (-1)*newwidth/2 ; i < newwidth/2 + newwidth%2;i++)
	{
		x = (float)i/xtimes;
		tempx1 = (int) x;
		tempx2 = (int) (x+1);
		for(j = (-1)*newheight/2; j < newheight/2 + newheight%2;j++)
		{
			y = (float)j/ytimes;
			tempy1 = (int)y;
			tempy2 = (int)(y+1);
			newcolor = fangcol(tempx1,tempx2,tempy1,tempy2,(float)x,(float)y,x0,y0);
			
			fwrite(&newcolor,2,1,fp);
		}
	}
	fclose(fp);
	
	draw_addmemo_back();
	
	if((fp=fopen("C:\\MEMO\\TEMP\\temp1.txt","rb"))==NULL){
		fclose(fp);
		return -1;
	}
	fseek(fp,4L,0);
	for(i=0;i<newwidth;i++)
	{
		for(j=0;j<newheight;j++)
		{
			fread(&newcolor,2,1,fp);
			putpixel(leftx+i, topy+j, newcolor);
		}
	}
	fclose(fp);
	
	Photoinfo->x1 = leftx;
	Photoinfo->x2 = leftx + newwidth;
	Photoinfo->y1 = topy;
	Photoinfo->y2 = topy + newheight;
	Photoinfo->nwidth = newwidth;
	Photoinfo->nheight = newheight;
}



int fangcol(int tempx1,int tempx2,int tempy1,int tempy2,float x,float y,int x0,int y0)
{
	int color[4];
	COLOR rgb[4];
	int r1,r2,r;
	int i;
	
	color[0]=getpixel(tempx1+x0,tempy1+y0);
	color[1]=getpixel(tempx2+x0,tempy1+y0);
	color[2]=getpixel(tempx1+x0,tempy2+y0);
	color[3]=getpixel(tempx2+x0,tempy2+y0);

	r1 = ((tempx2-x)*color[0] + (x-tempx1)*color[1])/(tempx2-tempx1);
	r2 = ((tempx2-x)*color[2] + (x-tempx1)*color[3])/(tempx2-tempx1);
	r = ((tempy2-y)*r1 + (y-tempy1)*r2)/(tempy2-tempy1);

	return r;
}