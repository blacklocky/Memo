/**
 * @file photo.cpp
 * @author Wen Yanqiu
 * @brief 
 * @version 0.1
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include "photo.h"
#include"gramd.h"
#include "config.h"
#include <graphics.h>
#include <math.h>
int BMPinsert(int x,int y,char *path,long int *oldwidth,long int *oldheight,photoinfor *Photoinfo)//鎻掑叆鏂扮収鐗?
{
    FILE *fpbmp;//閿熶茎纭锋嫹鎸囬敓鏂ゆ嫹
	unsigned int bit;//閿熶茎纭锋嫹浣嶉敓鏂ゆ嫹
	long int width,height; 
	unsigned long int compression;
	char dotColor;
	int i,j;
	
	if((fpbmp=fopen(path,"rb"))==NULL)//閿熻鍑ゆ嫹閿熸澃杈炬嫹閿熶茎纭锋嫹
    {
    	fclose(fpbmp);
		return -1;
	}
	

	fseek(fpbmp,28L,0); 
	fread(&bit,2,1,fpbmp);
	
	if(bit!=8U)
	{
		return -1;
	}

	fseek(fpbmp, 30L, 0);
	fread(&compression, 4, 1, fpbmp);
	
	if (compression != 0UL)
	{
		return -1;
	}
	
	fseek(fpbmp,18L,0);
	fread(&width,4,1,fpbmp);
	fread(&height,4,1,fpbmp);
	*oldwidth = width;
	*oldheight = height;
	
	if(width>SCREENWIDTH)
		return -1;


	Photoinfo->pwidth = width;
	Photoinfo->pheight = height;
	Photoinfo->x1 = fmidx - width/2;
	Photoinfo->x2 = fmidx + width/2;
	Photoinfo->y1 = fmidy - height/2;
	Photoinfo->y2 = fmidy + height/2;
	
	Photoinfo->flag = 1;
	Photoinfo->newflag = 0;
	Photoinfo->save = 1;
	Photoinfo->backflag = 0;
	Photoinfo->deleteflag = 0;
	
	Photoinfo->nwidth = Photoinfo->pwidth;
	Photoinfo->nheight = Photoinfo->pheight;	

	fseek(fpbmp,0x436,0);
	
	for(i=height-1;i>-1;i--)
	{
		for(j=0;j<width;j++)
		{
			
			fread(&dotColor, 1,1,fpbmp);
			drawdot(j+x-width/2, i+y-height/2,(int)dotColor);
		}
	}
	
	fclose(fpbmp);
    return 1;
}



int BMPOpen(int x,int y,char *path)//鎵撳紑鏀剧缉鍚庣殑鐓х墖
{
	FILE *fp;
	int color24; 
	int i,j;
	int width,height;

	if((fp=fopen(path,"rb"))==NULL)
	{fclose(fp);return -1;}
		

	fread(&width,2,1,fp);
	fread(&height,2,1,fp);
	
	for(i=0;i<width;i++)
	{
		for(j=0;j<height;j++)
		{
			fread(&color24 , 2, 1 , fp);
			putpixel(x+i, y+j, color24);
		}
	}
	fclose(fp);
	return 1;
}

void drawdot(int x,int y ,int color)
{
	if(x < 0 || x > (SCREENWIDTH - 1) || y < 0 || y > (SCREENHEIGHT - 1))
	{
		return;
	}
	putpixel(x,y,color);
}


float ratio(long int *width,long int *height)
{
	float xtimes,ytimes;
	float rate;
	xtimes = (float)fixwidth/(float)(*width);
	ytimes = (float)fixheight/(float)(*height);
	if(xtimes > ytimes)
		rate = ytimes;
	else if(fabs(xtimes - ytimes)<1e-6)
		rate = xtimes;
	else
		rate = xtimes;
	return rate;
}

int BMPsave(char* path)
{
	FILE *temp;
	FILE *save;
	char ch;
	int width,height;


	if((temp=fopen("C:\\MEMO\\TEMP\\temp1.txt","rb"))==NULL){
		fclose(temp);
		return -1;
	}
		

	if((save=fopen(path,"wb"))==NULL){
		fclose(save);
		return -1;
	}
		
	
	while((ch = fgetc(temp))!=EOF)
		fputc(ch,save);

	
	fclose(temp);
	fclose(save);
	return 1;

}
