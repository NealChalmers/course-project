#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"

void printfa(int);
void printfb(int);
int check(char *u, char*p);

/*temp data*/

struct tempd
{
	char tempu[20], tempp[20], tempi[20], tempn[20];
};

struct tempd ta, tb;
FILE *p;
int un = 3;
USERS item[30];
USERS linshi;

/*remaining redpacket*/

int rpoln = 0;
double rpolb = 0;
char sender[20];

/*initial user*/

char fu[20] = { "bigpig" };
char fp[20] = { "straw" };
char su[20] = { "midpig" };
char sp[20] = { "sticks" };
char tu[20] = { "smlpig" };
char tp[20] = { "bricks" };

int main()
{
	printf("\n��ӭʹ�������ϵͳ\n\n");
	printf("��ʼ�û�Ϊ��\n");
	printf("�û�1��bigpig ����straw\n");
	printf("�û�2��midpig ����sticks\n");
	printf("�û�3��smlpig ����bricks\n");

	/*create initial*/

	if ((p = fopen("users.txt", "r+")) == NULL)
	{
		p = fopen("users.txt", "w+");
	}
	strcpy(item[0].username, fu);
	strcpy(item[0].password, fp);
	strcpy(item[1].username, su);
	strcpy(item[1].password, sp);
	strcpy(item[2].username, tu);
	strcpy(item[2].password, tp);
	fprintf(p, "%s %s\n%s %s\n%s %s\n", fu, fp, su, sp, tu, tp);
	fclose(p);

	/*redpacket files*/

	if((p=fopen("redpacket.txt","r+"))==NULL)
    {
        p=fopen("redpacket.txt","w+");
        fprintf(p,"%d %lf %s\n",rpoln,rpolb,sender);
    }
    else
    {
        fscanf(p,"%d %lf %s\n",&rpoln,&rpolb,sender);
    }
    fclose(p);

    /*login system*/

	while (1)
	{
		int flag = 1;
		printfa(un);
		while (1 && flag)
		{
			/*main menu*/

			printfb(1);

			char choose;
			do
            {
                printf("������ѡ�� a-g ��");
                scanf("%c", &choose);
            }while(choose>'g'||choose<'a');
			switch (choose)
			{
			case 'a':sendrp(&linshi); break;
			case 'b':receiverp(&linshi); break;
			case 'c':inquiryb(&linshi); break;
			case 'd':inquiryr(&linshi); break;
			case 'e':flag = 0; break;
			case 'f':newuser(un++); break;
			case 'g':exit(1); break;
			}
		}
	}
	return 0;
}

/*print log-in page*/

void printfa(int a)
{
	if (!a)
	{
		printf("\n�û��������������������Ѵ����ޣ�\n\n");
		exit(1);
	}
	printf("\n��¼ϵͳ��\n");
	printf("\n�������û���������\nCtrl+Z �˳�\n\n");
	printf("�û�����");

	while (scanf("%s", ta.tempu) == EOF)
		exit(1);
	printf("���룺");
	scanf("%s", ta.tempp);

	if (!check(ta.tempu, ta.tempp))
	{
		printf("\n\n�û����������������������\n\n");
		printfa(--a);
	}
	else
	{
		printf("\n��¼�ɹ���");
		if ((p = fopen(ta.tempu, "r+")) == NULL)
		{
			p = fopen(ta.tempu, "w+");
			printf("\n\n�״ε�¼���������û��ǳƣ�");
			scanf("%s", ta.tempn);
			printf("ѧ�ţ�");
			scanf("%s", ta.tempi);
			fprintf(p, "%s %s %lf %d %d\n", ta.tempn, ta.tempi, 8.0, 0, 0);
			fclose(p);
		}
		p = fopen(ta.tempu, "r+");
		strcpy(linshi.username, ta.tempu);
		strcpy(linshi.password, ta.tempp);
		fscanf(p, "%s %s %lf %d %d", linshi.nickname, linshi.studentid, &linshi.changebalance, &linshi.rpreceive, &linshi.rpsend);
		fscanf(p, "%s", linshi.studentid);
		fclose(p);
	}
}

/*check user/password*/

int check(char *um, char *pw)
{
	p = fopen("users.txt", "r+");
	while (fscanf(p, "%s %s", tb.tempu, tb.tempp) != EOF)
	{
		if (!strcmp(um, tb.tempu))
			if (!strcmp(pw, tb.tempp))
				return 1;
	}
	fclose(p);
	return 0;
}

/*print log-in page*/

void printfb(int a)
{
	getchar();
	printf("\n\n\n*****************���˵�*****************\n\n");
	printf("        a:�����\n");
	printf("        b:�����\n");
	printf("        c:��ѯ���\n");
	printf("        d:��ѯ����շ���¼\n");
	printf("        e:�˳���¼\n");
	printf("        f:�������û�\n");
	printf("        g:�˳�����\n\n");
	printf("****************************************\n\n");
}
