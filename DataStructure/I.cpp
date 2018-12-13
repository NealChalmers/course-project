#include <iostream>
#include <cctype>
#include <stack>
#include <sstream>

using namespace std;

int main()
{
    stack<char> sc;
    char c;
    string in;
    getline(cin,in);
    istringstream si(in);
    while(si>>c)
        if(isalpha(c))
            cout<<c;
        else if(sc.empty()||c=='(')
            sc.push(c);
        else if(c==')')
        {
            while(sc.top()!='(')
            {
                cout<<sc.top();
                sc.pop();
            }
            sc.pop();
        }
        else if(c=='+'||c=='-')
        {
            while(!sc.empty()&&sc.top()!='('&&sc.top()!=')')
            {
                cout<<sc.top();
                sc.pop();
            }
            sc.push(c);
        }
        else
        {
            while(!sc.empty()&&(sc.top()=='*'||sc.top()=='/'))
            {
                cout<<sc.top();
                sc.pop();
            }
            sc.push(c);
        }
    while(!sc.empty())
    {
        cout<<sc.top();
        sc.pop();
    }
}
