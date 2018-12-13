#include <iostream>
#include <string>
#include <cstdio>
#include <cctype>

using namespace std;

typedef struct node                  //双向链表的节点
{
    int key;
    node *left,*right;
}*nodep,node;

typedef struct drl                      //双向链表
{
    nodep head;
    nodep tail;
    int fn;
    bool dir;
} drl;

nodep drl_insert(nodep,nodep &,int);
void drl_reverse(drl *);
bool drl_delete(drl *);
void drl_print(nodep,bool);
int drl_read();

int main()
{
    int n;
    string s,ts;
    cin>>n;
    while(n--)
    {
        drl *td=new drl;
        cin>>s;
        cin>>td->fn;
        if(!td->fn)
            cin>>ts;
        td->tail=drl_insert(NULL,td->head,td->fn);
        td->dir=1;
        bool er=1;
        for(string::iterator si=s.begin(); er&&si!=s.end(); ++si)
            if(*si=='R')
                drl_reverse(td);
            else if(*si=='D')
                er=drl_delete(td);
        if(!er)
            cout<<"error"<<endl;
        else
        {
            cout<<"[";
            if(td->fn)
                drl_print(td->head,td->dir);
            cout<<"]"<<endl;
        }
        delete td;
    }
}

nodep drl_insert(nodep prv,nodep &cur,int n)
{
    if(!n)
        return prv;
    cur=new node;
    cur->key=drl_read();
    cur->left=prv;
    cur->right=NULL;
    return drl_insert(cur,cur->right,n-1);
}

void drl_reverse(drl *td)
{
    nodep temp;
    temp=td->head;
    td->head=td->tail;
    td->tail=temp;
    td->dir=!td->dir;
}

bool drl_delete(drl *td)
{
    if(!td->fn)
        return 0;
    if(td->fn==1)
    {
        delete td->head;
        td->fn=0;
        td->head=td->tail=NULL;
        return 1;
    }
    nodep temp=td->head;
    nodep temp2=td->dir?temp->right:temp->left;
    td->head=temp2;
    (td->dir?temp2->left:temp2->right)=NULL;
    --td->fn;
    delete temp;
    return 1;
}

void drl_print(nodep cur,bool dir)
{
    cout<<cur->key;
    nodep temp=dir?cur->right:cur->left;
    if(temp!=NULL)
    {
        cout<<",";
        drl_print(temp,dir);
    }
    delete cur;
}

int ssttoi(string s)
{
    int re=0;
    for(int i=0; i!=s.size(); ++i)
    {
        char c=s[i];
        re=re*10+c-'0';
    }
    return re;
}

int drl_read()
{
    char c;
    string s("");
    while(cin>>c&&!isdigit(c));
    while(isdigit(c))
    {
        s+=c;
        cin>>c;
    }
    return ssttoi(s);
}
/*
10
RDRDRD
10
[1,2,3,4,5,,6,7,8,9,10]
DRDRDR
10
[1,2,3,4,5,6,7,8,9,10]
DDRRDDRR
10
[1,2,3,4,5,,6,7,8,9,10]
RRR
0
[]
RRRD
1
[500]

*/
