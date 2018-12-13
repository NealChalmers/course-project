 /*********************************************************************************
 ****  FileName:  demo.c
 ****  Function:  任务3题目2 印章打印
 ****  Usage:     demo  xxxx.bmp
 ****  Author:    xiangdesheng
 ****  Date:      2010-05-12
 *********************************************************************************/
#include <CONIO.H>
#include <STDLIB.H>
#include <stdio.h>
#include <MATH.H>
#include <MALLOC.H>
#include <string.h>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

/****  The file header of bmp file 位图文件头*****/
#include <pshpack2.h> //This file turns 2 byte packing of structures on, then sizeof(BITMAPFILEHEADER)=14, otherwise sizeof(BITMAPFILEHEADER)=16
typedef struct tagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfoffBits;
} BITMAPFILEHEADER;
#include <poppack.h> //This file turns packing of structures off

/****  The information header of bmp file 位图信息头*****/
typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    DWORD biWidth;
    DWORD biHeight;
    WORD  biPlanes;
    WORD  biBitCount;
    DWORD biCompress;
    DWORD biSizeImage;
    DWORD biXPeIsPerMeter;
    DWORD biYPeIsPerMeter;
    DWORD biCIrUsed;
    DWORD biClrImprotant;
} BITMAPINFOHEADER;

/****  The RGB data of bmp file 图像RGB数据*****/
typedef struct tagRGBDATA{
    BYTE rgbBlue;
    BYTE rgbGreen;
	BYTE rgbRed;
} RGBDATA;

char inputfile[112][136];     /*点阵图文件*/
char tempchar[4][56][68];
char tofile[126],trash[126];
unsigned char hanzi[40];
char sava[15][5];
int main(int argc, char *argv[])
{
	RGBDATA *bmpData=NULL;	//图像数据指针
	FILE *fp;				//BMP文件指针
	long i,j,k;
	long width=128;			//图像宽度
	long height=128;		//图像高度
	long dataSize=width*height;
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;

	if(argc<3)
	{
		printf("\n    请指定您要生成的BMP文件名！\n");
		printf("\n    方法1：在cmd窗口输入： getit  xxx.txt xxxx.bmp  后回车执行！\n");
		printf("\n    方法2：在VC的工程设置中添加参数：  xxx.txt xxxx.bmp　后编译运行！\n");
		printf("\n    功能： 根据输入汉字，输出bmp格式印章！\n\n");
		exit(0);
	}

	printf("\n    **************************************************************************\n");
	printf("\n             作者：蔡沐                 \n");
	printf("\n             目的：根据输入汉字，输出bmp格式印章！（任务3题目2）       \n");
	printf("\n             功能：根据所给xxx.txt点阵图，输出bmp格式印章！\n\n");
	printf("\n    **************************************************************************\n\n");

    //第一步：用命令行中给出的文件名新建一BMP文件，此时还是一个空文件
	if((fp=fopen(argv[2], "wb+"))==NULL)
	{
		printf("无法打开bmp文件!");
		exit(0);
	}


	//第二步：置文件头数据并写入BMP文件
	bmfHeader.bfType=0x4d42;
	bmfHeader.bfSize=14+40+width*height*3;
	bmfHeader.bfReserved1=0;
	bmfHeader.bfReserved2=0;
	bmfHeader.bfoffBits=0x36;
    fwrite(&bmfHeader, sizeof(BITMAPFILEHEADER), 1, fp);

	//第三步：置信息头数据并写入BMP文件
	bmiHeader.biSize=40;
	bmiHeader.biWidth=width;
	bmiHeader.biHeight=height;
	bmiHeader.biPlanes=1;
	bmiHeader.biBitCount=24;
	bmiHeader.biCompress=0;
	bmiHeader.biSizeImage=width*height*3;
	bmiHeader.biXPeIsPerMeter=0;
	bmiHeader.biYPeIsPerMeter=0;
	bmiHeader.biCIrUsed=0;
	bmiHeader.biClrImprotant=0;
    fwrite(&bmiHeader, sizeof(BITMAPINFOHEADER), 1, fp);

	//第四步：置图像RGB数据并写入BMP文件
	//分配足够内存，让bmpData指向这块内存，用于存放图像各象素点的RGB分量值
	if((bmpData=(RGBDATA*)malloc(width*height*3))==NULL)
	{
		printf("bmpData memory malloc error!");
	}

	//汉字的处理
    int  n,len,hanzin,ki;
    printf("    请输入一个或多个汉字：");
    scanf("%s",hanzi);
    for(len=0;hanzi[len]!='\0';len++);
    hanzin=len/2;
    for(n=0;n<len;n++)
    {
        sprintf(sava[n/2]+n%2*2,"%x",hanzi[n]);//编码－＞字符，并存入sava数组
    }
    for(ki=3;ki>=hanzin;ki--)
        strcpy(sava[ki],"a1a1");

    //初始化tempchar

    //处理文字库与文件，找到点阵图
    FILE *fpp;
    for(n=0;n<4;n++)
    {
        if((fpp=fopen(argv[1],"r"))==NULL)
        {
            printf("\n无法打开%s文件\n",argv[1]);
            exit(0);
        }
        for(i=0;i<4;i++)
            fgets(trash,100,fpp);
        for(i=0;i<8178;i++)
        {
            fscanf(fpp,"CurCode: %s",tofile);
            fscanf(fpp,"%s = 7",trash);
            if(strcmp(sava[n],tofile)==0)
            {
                for(j=0;j<56;j++)
                    fscanf(fpp,"%s",tempchar[n][j]);
                break;
            }
            else
                for(j=0;j<59;j++)
                    fgets(tofile,100,fpp);
        }
        fclose(fpp);
    }
    //处理点阵图
	for(i=0;i<height;i++)
    {
        if(i<56)
        {
            strcpy(inputfile[i],tempchar[2][i]);
            strcat(inputfile[i],tempchar[0][i]);
        }
        else
        {
            strcpy(inputfile[i],tempchar[3][i%56]);
            strcat(inputfile[i],tempchar[1][i%56]);
        }
    }

	//先在bmpData所指内存中置图像RGB数据，然后将所有数据写入BMP文件
    /*for(i=0;i<112;i++)
        printf(q,"%s\n",inputfile[i]);*/
    long ti,tj;
	for(i=0;i<height;i++)
	{
	    ti=i-8;
        tj=0;
		for(j=0;j<width;j++)
		{
		    k=(height-i-1)*width + j;//计算bmp图片中第i行第j列图像数据在bmpData[]数组中的位置
		    if(i<7||j<7||i>=121||j>=121)
            {
				bmpData[k].rgbBlue=0;
				bmpData[k].rgbGreen=0;
				bmpData[k].rgbRed=255;//红色分量值为：255
                continue;
			}
			if(inputfile[ti][tj]==',')
            {

                if(tj!=135)
                {
                    j--;
                    tj++;
                    continue;
                }
                else
                    break;
            }
			else if(inputfile[ti][tj]=='X')//上100行只置红色分量值，显示为红色
			{
				bmpData[k].rgbBlue=0;
				bmpData[k].rgbGreen=0;
				bmpData[k].rgbRed=255;//红色分量值为：255
				tj++;
			}
			else
            {
                bmpData[k].rgbBlue=255;
                bmpData[k].rgbGreen=255;//白色
                bmpData[k].rgbRed=255;
                tj++;
            }
		}
	}
	fwrite(bmpData,sizeof(RGBDATA),dataSize,fp);//将bmpData所指内存中的RGB数据一次性写入BMP文件
	printf("\n    恭喜您！BMP文件已经成功生成！\n");
	printf("\n    请在当前目录下查看生成的BMP文件%s\n\n",argv[2]);

	free(bmpData);	//释放bmpData所指的内存空间
	bmpData=NULL;	//置bmpData为空指针
	fclose(fpp);
	fclose(fp);		//关闭fp所指文件
    return 0;
}
