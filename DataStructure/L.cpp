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
int through(node *n);

int main()
{
    string c;
    while(cin>>c)
    {
        node *h=new node(c);
        grow(h,c);
        cout<<"="<<through(h);
        delete h;
        cout<<endl;
    }
}

//+ 13 # # * 5 # # 9 # #
//* + 13 # # 5 # # 9 # #

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

int through(node *n)
{
    bool in=1;
    if(n==NULL)
        return -1;
    if(n->s=="+"||n->s=="-"||n->s=="*"||n->s=="/")
    {
        cout<<"(";
        in=0;
    }
    int a=through(n->left);
    delete n->left;
    cout<<n->s;
    int b=through(n->right);
    delete n->right;
    if(n->s=="+"||n->s=="-"||n->s=="*"||n->s=="/")
    {
        cout<<")";
        in=0;
    }
    if(in)
        return ssttoi(n->s);
    else
        return cal(a,b,n->s[0]);
}

