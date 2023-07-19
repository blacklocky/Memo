#ifndef _PHOTO_H_
#define _PHOTO_H_
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#pragma pack(2)

typedef unsigned short WORD;  
typedef unsigned long DWORD;  
typedef unsigned char BYTE; 
typedef long LONG;

typedef struct COLOR
{
	BYTE B;
	BYTE G;
	BYTE R;
	//BYTE A;
}NCOLORS;


typedef struct tagRGBQUAD  //鑹插僵琛?
{
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
}RGBQUAD;

typedef struct tagBITMAPFILEHEADER //浣嶅浘鏂囦欢澶?
{
	WORD bfType;   //鍥剧墖绉嶇被锛孊MP鍥剧墖鍥哄畾涓築M锛岃〃绀轰负鍗佸叚杩涘埗灏辨槸0x4d42
    DWORD bfSize;  //璇ュ浘鐗囨枃浠剁殑澶у皬* 
    WORD bfReserved1;  //淇濈暀瀛?
    WORD bfReserved2;  //淇濈暀瀛?
    DWORD bfOffBits;  //瀹為檯鍥剧墖鏁版嵁鐨勫亸绉婚噺* 
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER  //浣嶅浘淇℃伅澶?
{
	DWORD biSize;  //鎸囧畾姝ょ粨鏋勪綋鐨勯暱搴? sizeof(BITMAPINFOHEADER)
    LONG biWidth;  //bmp鍥剧墖鐨勫搴? 
    LONG biHeight;  //bmp鍥剧墖鐨勯珮搴?* 
    WORD biPlanes;  //骞抽潰鏁帮紝鏄剧ず鍣ㄥ彧鏈変竴涓钩闈紝鎵€浠ヤ竴鑸负1  1
    WORD biBitCount;  //棰滆壊浣嶆暟锛岀洰鍓嶄竴鑸敤24浣嶆垨32浣? 24
    DWORD biCompression;   //鍘嬬缉鏂瑰紡锛屽彲浠ユ槸0锛?锛?锛?琛ㄧず涓嶅帇缂╋紝BMP涓轰笉鍘嬬缉锛屾墍浠ヤ负0
    DWORD biSizeImage;   //瀹為檯浣嶅浘鏁版嵁鍗犵敤鐨勫瓧鑺傛暟.鐢变簬涓婇潰涓嶅帇缂╋紝鎵€浠ヨ繖閲屽～0鍗冲彲
    LONG biXPelsPerMeter;  //X鏂瑰悜鍒嗚鲸鐜囷紝鍗虫瘡绫虫湁澶氬皯涓儚绱狅紝鍙互鐪佺暐
    LONG biYPelsPerMeter;  //Y鏂瑰悜鍒嗚鲸鐜囷紝鍗虫瘡绫虫湁澶氬皯涓儚绱狅紝鍙互鐪佺暐
    DWORD biClrUsed;   //浣跨敤鐨勯鑹叉暟锛屽鏋滀负0锛屽垯琛ㄧず榛樿鍊?2^棰滆壊浣嶆暟)
    DWORD biClrImportant;  //閲嶈棰滆壊鏁帮紝濡傛灉涓?锛屽垯琛ㄧず鎵€鏈夐鑹查兘鏄噸瑕佺殑
}BITMAPINFOHEADER;
//鍏朵綑鐩存帴娓? 

typedef struct BMP
{
	BITMAPFILEHEADER fileHead;
	BITMAPINFOHEADER infoHead;
	RGBQUAD colortable[256];
}BMPheader;

#define leftx 760
#define topy 128
#define fixwidth 200
#define fixheight 200

#define fmidx 650
#define fmidy 400

#define PHOTOPATH "C:\\MEMO\\BMP\\"

typedef struct photoinfor
{
	char name[30];  //鍥惧儚鍚嶇О
	char photopath[30]; //鍥惧儚璺緞
	int flag; //鍥惧儚鐘舵€?
	int newflag; //鏄惁涓烘柊寤哄浘鐗?
	int save;  //淇濆瓨鐘舵€?
	int backflag;  //鎾ら攢鐘舵€?
	int deleteflag;   //鍒犻櫎鐘舵€?
	int x1,y1,x2,y2;  //鍥惧儚鍧愭爣
	unsigned int nheight,nwidth;  //褰撳墠闀垮
	unsigned int pheight,pwidth;  //鍘熷闀垮
}bmpinfor;

int BMPOpen(int x,int y,char *path);
int BMPinsert(int x,int y,char *path,long int *oldwidth,long int *oldheight,photoinfor *Photoinfo);//插入新照片

int BMPsave(char* path);
void drawdot(int x,int y ,int color);


float ratio(long int *width,long int *height);

#endif