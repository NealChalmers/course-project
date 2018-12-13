#include <iostream>
#include <cmath>
#include <queue>
#include <cstdio>

using namespace std;

typedef struct edge                          //ÿ����
{
    int f,t;
    double v,a;
    edge(int tf,int tt,double tv,double ta):f(tf),t(tt),v(tv),a(ta) {};
} edge;

double timeto[101][101];                                    //ͼ
double bte;

void input(int,queue<edge> &);
void floyd(int);
void findless(int,queue<edge> &qe);

int main()
{
    int c,r;
    while(cin>>c>>r&&(c||r))
    {

        for(int i=1; i!=c+1; ++i)                             //��ʼ��ͼ
            for(int j=1; j!=c+1; ++j)
            {
                if(i==j)
                    timeto[i][j]=0;
                else
                    timeto[i][j]=1e7;
            }
        queue<edge> qe;
        input(r,qe);
        floyd(c);
        bte=timeto[1][c];
        findless(c,qe);
        printf("%.3lf\n",bte);
    }
}
void input(int r,queue<edge> &qe)
{
    int tf,tt;
    double tv,ta;
    for(int i=0; i!=r; ++i)                             //��������
    {
        cin>>tf>>tt>>tv>>ta;
        if(timeto[tf][tt]>ta)
            timeto[tf][tt]=timeto[tt][tf]=tv;           //����ͼ
        qe.push(edge(tf,tt,tv,ta));
        qe.push(edge(tt,tf,tv,ta));
    }
}

void floyd(int c)
{
    for(int k=1; k!=c+1; ++k)                           //floyd�㷨�����·����Ԥ����
        for(int i=1; i!=c+1; ++i)
            for(int j=1; j!=c+1; ++j)
                timeto[i][j]=(timeto[i][j]<timeto[i][k]+timeto[k][j])?timeto[i][j]:(timeto[i][k]+timeto[k][j]);
}

void findless(int c,queue<edge> &qe)
{
    double t;
    while(!qe.empty())
    {
        edge te=qe.front();
        qe.pop();
        if (abs(te.a-1)>1e-6)
            t=log(te.v*log(te.a))/log(te.a);                   //����y = t + v*a^(-t); => y'=1+(-v*a^(-t)ln(a))=0; => a^t=v*ln(a);
        else                                                   //     => t=log(v*ln(a))=log(v*ln(a))/log(a);
            t=0;
        if(t>timeto[1][te.f])
        {
            if (t+te.v*pow(te.a,-t)+timeto[te.t][c] < bte)
                bte=t+te.v*pow(te.a,-t)+timeto[te.t][c];                  //��·ǰʱ�� + ��·ʱ�� + ���յ���ʱ
        }
        else
        {
            t=timeto[1][te.f];                                            //���������·ʱ�䣬�ӳ���·ʱ��
            if (t+te.v*pow(te.a,-t)+timeto[te.t][c] < bte)
                bte=t+te.v*pow(te.a,-t)+timeto[te.t][c];
        }
    }
}


