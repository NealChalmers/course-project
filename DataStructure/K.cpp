#include <iostream>
#include <string>

using namespace std;

typedef struct node
{
    string s;
    int f;
    node *left,*right;
    node(const string ss):s(ss),f(0),left(NULL),right(NULL) {};
} node;

node* grow(node *n,string s);
void through(node *n);

int main()
{
    string c;
    while(cin>>c)
    {
        node *h=new node(c);
        grow(h,c);
        through(h);
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

void through(node *n)
{
    if(n==NULL)
        return;
    if(n->s=="+"||n->s=="-"||n->s=="*"||n->s=="/")
        cout<<"(";
    through(n->left);
    delete n->left;
    cout<<n->s;
    through(n->right);
    delete n->right;
    if(n->s=="+"||n->s=="-"||n->s=="*"||n->s=="/")
        cout<<")";
}
