#include <iostream>
#include <memory.h>

using namespace std;

typedef struct linkv
{
    int n;
    int edge[50];
}linkv;

typedef struct
{
    linkv lv[50];
    int p;
}pict;

typedef struct
{
    int f,t,q;
}egs;

void createpic(pict *,int,int);
int prim(pict *pic);

int main()
{
    int p,e;
    while(cin>>p&&p)
    {
        cin>>e;
        pict *pic=new pict;
        pic->p=p;
        createpic(pic,p,e);
        cout<<prim(pic)<<endl;
        delete pic;
    }
    return 0;
}

void createpic(pict *pic,int p,int e)
{
    for(int i=0;i!=50;++i)
    {
        for(int j=0;j!=50;++j)
            pic->lv[i].edge[j]=0;
        pic->lv[i].n=0;
    }
    int cp1,cp2,ce;
    for(int i=0;i!=e;++i)
    {
        cin>>cp1>>cp2>>ce;
        if(pic->lv[cp1-1].edge[cp2-1]==0&&pic->lv[cp2-1].edge[cp1-1]==0)
        {
            pic->lv[cp1-1].edge[cp2-1]=pic->lv[cp2-1].edge[cp1-1]=ce;
            ++pic->lv[cp1-1].n;
            ++pic->lv[cp2-1].n;
        }
        else
        {
            pic->lv[cp1-1].edge[cp2-1]=pic->lv[cp1-1].edge[cp2-1]<ce?pic->lv[cp1-1].edge[cp2-1]:ce;
            pic->lv[cp2-1].edge[cp1-1]=pic->lv[cp1-1].edge[cp2-1];
        }
    }
}
/*
5 7
1 2 5
2 3 7
2 4 8
4 5 11
3 5 10
1 5 6
4 2 12

*/
int prim(pict *pic)
{
    int re=0;
    bool marked[50];
    int lowest[50];
    memset(marked,0,50*sizeof(bool));
    memset(lowest,0,50*sizeof(int));

    marked[0]=1;
    for(int i=0;i!=pic->p;++i)
    {
        int tq;
        for(int j=0;j!=pic->lv[i].n;++j)
            if((tq=pic->lv[i].edge[j])!=0)
            {
                if(marked[j])
                {
                    if(tq<lowest[j])
                        lowest[j]=tq;
                }
                else
                {
                    marked[j]=1;
                    lowest[j]=tq;
                }
            }
    }
    for(int i=0;i!=pic->p;++i)
    {
        if(!marked[i])
            continue;
        re+=lowest[i];
    }
    return re;
}












