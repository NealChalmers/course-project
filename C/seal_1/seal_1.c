 /*********************************************************************************
 ****  FileName:  demo.c
 ****  Function:  ����3��Ŀ1 ӡ�´�ӡ
 ****  Usage:     demo  xxxx.bmp
 ****  Author:    xiangdesheng
 ****  Date:      2010-05-12
 *********************************************************************************/
#include <CONIO.H>
#include <stdlib.H>
#include <stdio.H>
#include <math.H>
#include <malloc.H>
#include <string.h>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

/****  The file header of bmp file λͼ�ļ�ͷ*****/
#include <pshpack2.h> //This file turns 2 byte packing of structures on, then sizeof(BITMAPFILEHEADER)=14, otherwise sizeof(BITMAPFILEHEADER)=16
typedef struct tagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfoffBits;
} BITMAPFILEHEADER;
#include <poppack.h> //This file turns packing of structures off

/****  The information header of bmp file λͼ��Ϣͷ*****/
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

/****  The RGB data of bmp file ͼ��RGB����*****/
typedef struct tagRGBDATA{
    BYTE rgbBlue;
    BYTE rgbGreen;
	BYTE rgbRed;
} RGBDATA;

char inputfile[112][126];     /*����ͼ�ļ�*/

int main(int argc, char *argv[])
{
	RGBDATA *bmpData=NULL;	//ͼ������ָ��
	FILE *fp;				//BMP�ļ�ָ��
	long i,j,k;
	long width=128;			//ͼ����
	long height=128;		//ͼ��߶�
	long dataSize=width*height;
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;

	if(argc<3)
	{
		printf("\n    ��ָ����Ҫ���ɵ�BMP�ļ�����\n");
		printf("\n    ����1����cmd�������룺 getit  xxxx.bmp xxx.txt  ��س�ִ�У�\n");
		printf("\n    ����2����VC�Ĺ�����������Ӳ����� xxxx.bmp xxx.txt����������У�\n");
		printf("\n    ���ܣ� ����xxx.txt�ļ��е���ͼ�����bmp��ʽӡ�£�\n\n");
		exit(0);
	}

	printf("\n    **************************************************************************\n");
	printf("\n             ���ߣ�����                 \n");
	printf("\n             Ŀ�ģ����ݵ���ͼ����ӡ�£�������3��Ŀ1��       \n");
	printf("\n             ���ܣ���������xxx.txt����ͼ�����bmp��ʽӡ�£�\n\n");
	printf("\n    **************************************************************************\n\n");

    //��һ�������������и������ļ����½�һBMP�ļ�����ʱ����һ�����ļ�
	if((fp=fopen(argv[2], "wb+"))==NULL)
	{
		printf("�޷���bmp�ļ�!");
		exit(0);
	}


	//�ڶ��������ļ�ͷ���ݲ�д��BMP�ļ�
	bmfHeader.bfType=0x4d42;
	bmfHeader.bfSize=14+40+width*height*3;
	bmfHeader.bfReserved1=0;
	bmfHeader.bfReserved2=0;
	bmfHeader.bfoffBits=0x36;
    fwrite(&bmfHeader, sizeof(BITMAPFILEHEADER), 1, fp);

	//������������Ϣͷ���ݲ�д��BMP�ļ�
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

	//���Ĳ�����ͼ��RGB���ݲ�д��BMP�ļ�
	//�����㹻�ڴ棬��bmpDataָ������ڴ棬���ڴ��ͼ������ص��RGB����ֵ
	if((bmpData=(RGBDATA*)malloc(width*height*3))==NULL)
	{
		printf("bmpData memory malloc error!");
	}

	//�������ͼ

	FILE *fpp;
	if((fpp=fopen(argv[1],"r"))==NULL)
    {
        printf("\n�޷���%s�ļ�\n",argv[1]);
        exit(0);
    }
	for(i=0;i<height;i++)
    {
        fscanf(fpp,"%s",inputfile[i]);
    }
	//����bmpData��ָ�ڴ�����ͼ��RGB���ݣ�Ȼ����������д��BMP�ļ�
    long ti,tj;
	for(i=0;i<height;i++)
	{
	    ti=i-8;
        tj=0;
		for(j=0;j<width;j++)
		{
		    k=(height-i-1)*width + j;//����bmpͼƬ�е�i�е�j��ͼ��������bmpData[]�����е�λ��
		    if(i<7||j<7||i>=121||j>=121)
            {
				bmpData[k].rgbBlue=0;
				bmpData[k].rgbGreen=0;
				bmpData[k].rgbRed=255;//��ɫ����ֵΪ��255
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
			else if(inputfile[ti][tj]=='X')//��100��ֻ�ú�ɫ����ֵ����ʾΪ��ɫ
			{
				bmpData[k].rgbBlue=0;
				bmpData[k].rgbGreen=0;
				bmpData[k].rgbRed=255;//��ɫ����ֵΪ��255
				tj++;
			}
			else
            {
                bmpData[k].rgbBlue=255;
                bmpData[k].rgbGreen=255;//��ɫ
                bmpData[k].rgbRed=255;
                tj++;
            }
		}
	}
	fwrite(bmpData,sizeof(RGBDATA),dataSize,fp);//��bmpData��ָ�ڴ��е�RGB����һ����д��BMP�ļ�
	printf("\n    ��ϲ����BMP�ļ��Ѿ��ɹ����ɣ�\n");
	printf("\n    ���ڵ�ǰĿ¼�²鿴���ɵ�BMP�ļ�%s\n\n",argv[2]);

	free(bmpData);	//�ͷ�bmpData��ָ���ڴ�ռ�
	bmpData=NULL;	//��bmpDataΪ��ָ��
	fclose(fpp);
	fclose(fp);		//�ر�fp��ָ�ļ�
    return 0;
}
