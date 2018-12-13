#include <iostream>
#include <string>
#include <stack>

using namespace std;

typedef struct node
{
    string s;
    int f;
    node *left,*right;
    node(const string ss):s(ss),f(0),left(NULL),right(NULL) {};
} node;

node* grow(node *n,string s);
double through(node *n,string &);

int main()
{
    string c;
    while(cin>>c)
    {
        string save;
        node *h=new node(c);
        grow(h,c);
        double exm=through(h,save);
        if(exm-24<=0.0001&&exm-24>=-0.0001)
            cout<<save<<"=24";
        else
            cout<<"NO";
        delete h;
        cout<<endl;
    }
}

node* grow(node *n,string s)
{
    if(n==NULL)
        n=new node(s);
    cin>>s;
    if(s!="#")
        n->left=grow(n->left,s);
    cin>>s;
    if(s!="#")
        n->right=grow(n->right,s);
    return n;
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

double cal(double a,double b,char c)
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

double through(node *n,string &save)
{
    bool in=1;
    double a,b;
    if(n->s=="+"||n->s=="-"||n->s=="*"||n->s=="/")
    {
        save+="(";
        in=0;
    }
    if(!in)
        a=through(n->left,save);
    delete n->left;
    save+=n->s;
    if(!in)
        b=through(n->right,save);
    delete n->right;
    if(n->s=="+"||n->s=="-"||n->s=="*"||n->s=="/")
    {
        save+=")";
        in=0;
    }
    if(in)
        return ssttoi(n->s);
    else
        return cal(a,b,n->s[0]);
}
