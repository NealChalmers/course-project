#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "users.h"
extern int rpoln;
extern double rpolb;
extern char sender[20];
extern USERS item[30];

FILE *p;

/*send redpacket*/

void sendrp(USERS *linship)
{
	if (rpoln != 0)
	{
		printf("\n已经有人发了红包了，抢完再发吧\n");
		return;
	}
	double ts;
	int tn;
	printf("\n请输入发送红包数量：");
	if (scanf("%d", &tn) != 1||tn>=20||tn<=0)
	{
		printf("\n输入不合法!请输入不超过20的正整数\n");
		return;
	}
	printf("\n请输入发送金额：");
	if (scanf("%lf", &ts) != 1||ts>=200||ts<=0)
	{
		printf("\n输入不合法!请输入不超过200的金额\n");
		return;
	};
	if (ts > linship->changebalance)
	{
		printf("\n余额不足！发红包失败。\n");
		return;
	}
	else
	{
		printf("\n红包发送成功！\n");
		strcpy(sender, linship->nickname);
		linship->changebalance -= ts;
		rpolb += ts;
		rpoln += tn;
		linship->rpsend++;
		p = fopen(linship->username, "w+");
		fprintf(p, "%s %s %lf %d %d\n", linship->nickname, linship->studentid, linship->changebalance, linship->rpsend, linship->rpreceive);
		fclose(p);
		p = fopen("redpacket.txt", "w+");
		fprintf(p, "%d %lf %s\n", rpoln, rpolb, sender);
		fclose(p);
	}
}

/*get redpacket*/

void receiverp(USERS *linship)
{
	double td;
	if (rpoln == 0)
	{
		printf("\n\n还没有人发红包或红包已被抢光(⊙o⊙)\n");
		return;
	}
	else
	{
		if (rpoln == 1)
		{
			linship->changebalance += rpolb;
			printf("\n%s抢到了%s发的%.2lf的红包！\n", linship->nickname, sender, rpolb);
			rpolb = 0;
			rpoln = 0;
			memset(sender, '\0', 20 * sizeof(char));
		}
		else
		{
			srand((unsigned)time(NULL));
			td = (rand() % 100 + 1)*1.0 / 100 * (rpolb/rpoln*2);
			printf("\n%s抢到了%s发的%.2lf的红包！\n", linship->nickname, sender, td);
			linship->changebalance += td;
			rpolb -= td;
			rpoln--;
		}
		linship->rpreceive++;
		p = fopen(linship->username, "w+");
		fprintf(p, "%s %s %lf %d %d\n", linship->nickname, linship->studentid, linship->changebalance, linship->rpsend, linship->rpreceive);
		fclose(p);
		p = fopen("redpacket.txt", "w+");
		fprintf(p, "%d %lf %s\n", rpoln, rpolb, sender);
		fclose(p);
	}
}

/*check balance*/

void inquiryb(USERS *linship)
{
	printf("\n\n你好，%s(学号：%s)，你的账户余额还有%.2lf元\n", linship->nickname, linship->studentid, linship->changebalance);
}

/*check redpacket*/

void inquiryr(USERS *linship)
{
	printf("\n\n你好，%s(学号：%s)\n\n你已发送%d个红包\n\n抢到%d个红包\n", linship->nickname, linship->studentid, linship->rpsend, linship->rpreceive);
}

/*create new user*/

void newuser(int ttun)
{
	int i;
	char tpun[20], tppw[20], tpun2[20];
	if (ttun >= 29)
		printf("用户数量已达上限");
	printf("\n创建新用户：\n");
	printf("\n请输入所要创建的用户名:");
	scanf("%s", tpun);
	getchar();
	p = fopen("users.txt", "r+");
	for (i = 0; i < ttun; i++)
	{
		fscanf(p, "%s %s", tpun2, tppw);
		if (strcmp(tpun, tpun2) == 0)
		{
			printf("\n创建失败，此用户名已存在!\n");
			return;
		}
	}
	fclose(p);
	p = fopen("users.txt", "a+");
	printf("\n请输入用户密码：");
	scanf("%s", tppw);
	fprintf(p, "%s %s\n", tpun, tppw);
	fclose(p);
	printf("\n创建新用户成功，可退出登录当前用户后登录新创建用户\n\n");
}
