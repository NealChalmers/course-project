#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef struct
{
    string ss;
    int ii;
} sp;

typedef struct
{
    int si;
    sp s[10000];                                //�����Ա�������
} xxb;

xxb &inixxb(xxb &x);                                //��ʼ���ֵ�
int findit(xxb &x,string s);                       //���ֵ��в���
void getsug(xxb &x,string s,xxb &y);                       //���ɽ��鵥��

bool com(const sp &a,const sp &b)
{
    return a.ii<b.ii;
}

int main()
{
    xxb *a=new xxb;
    inixxb(*a);
    string s;
    while(cin>>s&&s!="#")
    {
        cout<<s;
        if(findit(*a,s))
            cout<<" is correct"<<endl;
        else
        {
            xxb *c=new xxb;
            cout<<":";
            getsug(*a,s,*c);
            sort(c->s,c->s+c->si,com);
            for(int i=0; i!=c->si; ++i)
            {
                cout<<" "<<c->s[i].ss;
            }
            cout<<endl;
            delete c;
        }
    }
    delete a;
}

int bise(int h,int t,xxb &x,string s);

bool comp(const sp &a,const sp &b)
{
    return a.ss<b.ss;
}

xxb &inixxb(xxb &x)
{
    string ts;
    int i=0;
    while(cin>>ts&&ts!="#")
    {
        x.s[i].ii=i+1;
        x.s[i++].ss=ts;
    }
    sort(x.s,x.s+i,comp);
    x.si=i;
    return x;
}

int findit(xxb &x,string s)
{
    int h=0,t=x.si;
    return bise(h,t,x,s);
}

int bise(int h,int t,xxb &x,string s)
{
    if(h==t)
        return 0;
    int d=(h+t)/2;
    if(x.s[d].ss==s)
        return x.s[d].ii;
    else if(x.s[d].ss>s)
        return bise(h,d,x,s);
    else
        return bise(d+1,t,x,s);
}

bool afind(xxb &y,string s)
{
    for(int i=0; i!=y.si; ++i)
    {
        if(y.s[i].ss==s)
            return 1;
    }
    return 0;
}

void getsug(xxb &x,string s,xxb &y)
{
    string ts;
    int g;
    y.si=0;
    for(int j=0; j!=s.size(); ++j)                       //ɾ��һ����ĸ
    {
        ts=s;
        ts.erase(j,1);
        if(afind(y,ts))
            continue;
        if((g=findit(x,ts))!=0)
        {
            y.s[y.si].ii=g;
            y.s[y.si++].ss=ts;
        }
    }
    for(int j=0; j!=s.size(); ++j)                      //�滻һ����ĸ
    {
        ts=s;
        ts[j]='a';
        for(int i=0; i!=26; ++i)
        {
            if(afind(y,ts))
                continue;
            if((g=findit(x,ts))!=0)
            {
                y.s[y.si].ii=g;
                y.s[y.si++].ss=ts;
            }
            ts[j]++;
        }
    }
    for(int j=0; j<=s.size(); j++)
    {
        ts=s;
        ts.insert(j,"a");
        for(int i=0; i!=26; ++i)                        //����һ����ĸ
        {
            if(afind(y,ts))
                continue;
            if((g=findit(x,ts))!=0)
            {
                y.s[y.si].ii=g;
                y.s[y.si++].ss=ts;
            }
            ts[j]++;
        }
    }
}
/*    (1)��ÿһ������λ�ò��롮a-'z'�е�һ��
    (2)ɾ�������е�һ���ַ�
    (3)�á�a'-'z'�е�һ��ȡ�������е���һ�ַ�
*/








