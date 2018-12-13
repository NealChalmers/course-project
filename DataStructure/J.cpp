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
void through(node *n,int);

int main()
{
    string c;
    while(cin>>c)
    {
        node *h=new node(c);
        grow(h,c);
        through(h,0);
        delete h;
        cout<<endl;
    }
}

//A ST C # # D 10 # G # # F # # #
//4 2 1 # # 3 # # 5 # 6 # #



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

void through(node *n,int sj)
{
    if(n==NULL)
        return;
    through(n->right,sj+1);
    delete n->right;
    for(int i=0; i!=sj; ++i)
        cout<<"    ";
    cout<<n->s<<endl;
    through(n->left,sj+1);
    delete n->left;
}
