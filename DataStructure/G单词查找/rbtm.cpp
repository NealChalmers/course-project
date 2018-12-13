#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef struct
{
    string ss;
    int ii;
} sa;

typedef struct
{
    sa sas[10000];
    int ie;
} save;

typedef struct rbt                      //平衡二叉树（红黑树）结点
{
    string key;                         //储存的键（单词）
    int n,index;                        //子树中结点总数(n),字典输入顺序(index)
    bool color;                         //该结点父结点指向其的链接(true为red）
    rbt *left;                          //左子树
    rbt *right;                         //右子树
    rbt(string &s,int a,int b,bool rb):key(s),n(a),index(b),color(rb),left(NULL),right(NULL) {};
    rbt &operator=(const rbt &tr)
    {
        key=tr.key;
        left=tr.left;
        right=tr.right;
        n=tr.n;
        index=tr.index;
        color=tr.color;
        return *this;
    }
} rbt;

struct phecs                            //根结点
{
    rbt *next;
};

bool isRed(rbt *x);                     //判断结点颜色
int sizein(rbt *x);                     //判断结点大小
rbt rotateLeft(rbt *h);                 //左旋转结点链接
rbt rotateRight(rbt &h);                //右旋转结点链接
void trancolor(rbt &h);                 //转变结点颜色
int findrbt(rbt *h,string s);          //查找结点
rbt *insertrbt(rbt *h,string s,int);        //插入结点
void inirbt(phecs &p);                  //生成字典
void getsug(rbt &x,string s,save &ss);           //生成建议单词
void test(rbt *a);

bool com(const sa &a,const sa &b)
{
    return a.ii<b.ii;
}

int main()
{
    phecs a;
    a.next=NULL;
    inirbt(a);
    string s;
    while(cin>>s&&s!="#")
    {
        cout<<s;
        if(findrbt(a.next,s))
            cout<<" is correct"<<endl;
        else
        {
            save *ss=new save ;
            cout<<":";
            getsug(*a.next,s,*ss);
            sort(ss->sas,ss->sas+ss->ie,com);
            for(int i=0; i!=ss->ie; ++i)
            {
                cout<<" "<<ss->sas[i].ss;
            }
            cout<<endl;
            delete ss;
        }
    }
}

bool isRed(rbt *x)
{
    if(x==NULL)
        return 0;
    return x->color==1;
}

int sizein(rbt *x)
{
    if(x==NULL)
        return 0;
    else
        return x->n;
}

rbt rotateLeft(rbt &h)
{
    rbt *q=h.right;
    rbt x=*h.right;
    *q=h;
    q->right=x.left;
    x.left=q;
    x.color=h.color;
    q->color=1;
    x.n=h.n;
    q->n=1+sizein(h.left)+sizein(h.right);
    return x;
}

rbt rotateRight(rbt &h)
{
    rbt *q=h.left;
    rbt x=*h.left;
    *q=h;
    q->left=x.right;
    x.right=q;
    x.color=h.color;
    q->color=1;
    x.n=h.n;
    q->n=1+sizein(h.left)+sizein(h.right);
    return x;
}

void trancolor(rbt &h)
{
    h.color=1;
    h.left->color=0;
    h.right->color=0;
}

int findrbt(rbt *h,string s)
{
    if(h==NULL)
        return 0;
    if(h->key==s)
        return h->index;
    else if(h->key>s)
        return findrbt(h->left,s);
    else
        return findrbt(h->right,s);
}

rbt *insertrbt(rbt *h,string s,int index)
{
    if(h==NULL)
        return new rbt(s,1,index,1);
    if(h->key==s)
        return h;
    else if(h->key>s)
        h->left=insertrbt(h->left,s,index);
    else
        h->right=insertrbt(h->right,s,index);
    if(isRed(h->right)&&!isRed(h->left))
        *h=rotateLeft(*h);
    if(isRed(h->left)&&isRed(h->left->left))
        *h=rotateRight(*h);
    if(isRed(h->left)&&isRed(h->right))
        trancolor(*h);
    h->n=sizein(h->left)+sizein(h->right)+1;
    return h;
}

void inirbt(phecs &p)
{
    string ts;
    int index=1;
    while(cin>>ts&&ts!="#")
    {
        p.next=insertrbt(p.next,ts,index++);
    }
}

bool afind(save &y,string s)
{
    for(int i=0; i!=y.ie; ++i)
    {
        if(y.sas[i].ss==s)
            return 1;
    }
    return 0;
}

void getsug(rbt &x,string s,save &ss)
{
    string ts;
    int gg=0;
    ss.ie=0;
    for(int j=0; j!=s.size(); ++j)                       //删除一个字母
    {
        ts=s;
        ts.erase(j,1);
        if(afind(ss,ts))
            continue;
        if(gg=findrbt(&x,ts))
        {
            ss.sas[ss.ie].ss=ts;
            ss.sas[ss.ie++].ii=gg;
        }
    }
    for(int j=0; j!=s.size(); ++j)                      //替换一个字母
    {
        ts=s;
        ts[j]='a';
        for(int i=0; i!=26; ++i)
        {
            if(!afind(ss,ts))
            {
                if(gg=findrbt(&x,ts))
                {
                    ss.sas[ss.ie].ss=ts;
                    ss.sas[ss.ie++].ii=gg;
                }
            }
            ts[j]++;
        }
    }
    for(int j=0; j<=s.size(); j++)
    {
        ts=s;
        ts.insert(j,"a");
        for(int i=0; i!=26; ++i)                        //插入一个字母
        {
            if(!afind(ss,ts))
            {
                if(gg=findrbt(&x,ts))
                {
                    ss.sas[ss.ie].ss=ts;
                    ss.sas[ss.ie++].ii=gg;
                }
            }
            ts[j]++;
        }
    }
}
