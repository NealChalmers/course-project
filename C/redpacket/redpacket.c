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
	printf("\n欢迎使用抢红包系统\n\n");
	printf("初始用户为：\n");
	printf("用户1：bigpig 密码straw\n");
	printf("用户2：midpig 密码sticks\n");
	printf("用户3：smlpig 密码bricks\n");

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
                printf("请输入选项 a-g ：");
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
		printf("\n用户名或密码错误，输入次数已达上限！\n\n");
		exit(1);
	}
	printf("\n登录系统：\n");
	printf("\n请输入用户名与密码\nCtrl+Z 退出\n\n");
	printf("用户名：");

	while (scanf("%s", ta.tempu) == EOF)
		exit(1);
	printf("密码：");
	scanf("%s", ta.tempp);

	if (!check(ta.tempu, ta.tempp))
	{
		printf("\n\n用户名或密码错误，请重新输入\n\n");
		printfa(--a);
	}
	else
	{
		printf("\n登录成功！");
		if ((p = fopen(ta.tempu, "r+")) == NULL)
		{
			p = fopen(ta.tempu, "w+");
			printf("\n\n首次登录，请输入用户昵称：");
			scanf("%s", ta.tempn);
			printf("学号：");
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
	printf("\n\n\n*****************主菜单*****************\n\n");
	printf("        a:发红包\n");
	printf("        b:抢红包\n");
	printf("        c:查询余额\n");
	printf("        d:查询红包收发记录\n");
	printf("        e:退出登录\n");
	printf("        f:创建新用户\n");
	printf("        g:退出程序\n\n");
	printf("****************************************\n\n");
}
