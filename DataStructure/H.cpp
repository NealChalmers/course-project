#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cstdio>

using namespace std;

int ssttoi(string);
int cal(int a,int b,char c);

int main()
{
    stack<int> si;
    string ts("");
    char c;
    int a,b;
    while(scanf("%c",&c)!=EOF&&c!='@')
    {
        if(isdigit(c))
        {
            ts+=c;
            while(scanf("%c",&c)!=EOF&&isdigit(c))
                ts+=c;
            si.push(ssttoi(ts));
            ts="";
        }
        if(c=='+'||c=='-'||c=='*'||c=='/')
        {
            a=si.top();
            si.pop();
            b=si.top();
            si.pop();
            si.push(cal(b,a,c));
        }
    }
    cout<<si.top()<<endl;
}

int ssttoi(string s)
{
    int re=0;
    for(int i=0;i!=s.size();++i)
    {
        char c=s[i];
        re=re*10+c-'0';
    }
    return re;
}

int cal(int a,int b,char c)
{
    if(c=='+')
        return a+b;
    else if(c=='-')
        return a-b;
    else if(c=='*')
        return a*b;
    else if(c=='/')
        return a/b;
}


