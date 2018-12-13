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
		printf("\n�Ѿ����˷��˺���ˣ������ٷ���\n");
		return;
	}
	double ts;
	int tn;
	printf("\n�����뷢�ͺ��������");
	if (scanf("%d", &tn) != 1||tn>=20||tn<=0)
	{
		printf("\n���벻�Ϸ�!�����벻����20��������\n");
		return;
	}
	printf("\n�����뷢�ͽ�");
	if (scanf("%lf", &ts) != 1||ts>=200||ts<=0)
	{
		printf("\n���벻�Ϸ�!�����벻����200�Ľ��\n");
		return;
	};
	if (ts > linship->changebalance)
	{
		printf("\n���㣡�����ʧ�ܡ�\n");
		return;
	}
	else
	{
		printf("\n������ͳɹ���\n");
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
		printf("\n\n��û���˷���������ѱ�����(��o��)\n");
		return;
	}
	else
	{
		if (rpoln == 1)
		{
			linship->changebalance += rpolb;
			printf("\n%s������%s����%.2lf�ĺ����\n", linship->nickname, sender, rpolb);
			rpolb = 0;
			rpoln = 0;
			memset(sender, '\0', 20 * sizeof(char));
		}
		else
		{
			srand((unsigned)time(NULL));
			td = (rand() % 100 + 1)*1.0 / 100 * (rpolb/rpoln*2);
			printf("\n%s������%s����%.2lf�ĺ����\n", linship->nickname, sender, td);
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
	printf("\n\n��ã�%s(ѧ�ţ�%s)������˻�����%.2lfԪ\n", linship->nickname, linship->studentid, linship->changebalance);
}

/*check redpacket*/

void inquiryr(USERS *linship)
{
	printf("\n\n��ã�%s(ѧ�ţ�%s)\n\n���ѷ���%d�����\n\n����%d�����\n", linship->nickname, linship->studentid, linship->rpsend, linship->rpreceive);
}

/*create new user*/

void newuser(int ttun)
{
	int i;
	char tpun[20], tppw[20], tpun2[20];
	if (ttun >= 29)
		printf("�û������Ѵ�����");
	printf("\n�������û���\n");
	printf("\n��������Ҫ�������û���:");
	scanf("%s", tpun);
	getchar();
	p = fopen("users.txt", "r+");
	for (i = 0; i < ttun; i++)
	{
		fscanf(p, "%s %s", tpun2, tppw);
		if (strcmp(tpun, tpun2) == 0)
		{
			printf("\n����ʧ�ܣ����û����Ѵ���!\n");
			return;
		}
	}
	fclose(p);
	p = fopen("users.txt", "a+");
	printf("\n�������û����룺");
	scanf("%s", tppw);
	fprintf(p, "%s %s\n", tpun, tppw);
	fclose(p);
	printf("\n�������û��ɹ������˳���¼��ǰ�û����¼�´����û�\n\n");
}
