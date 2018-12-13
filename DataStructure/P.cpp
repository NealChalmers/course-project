#include <iostream>
#include <vector>

using namespace std;

vector<int> a,b,c;
int main()
{
    int n;
    while(cin>>n&&n!=0)
    {
        int m;
        for(int i=0;i!=n;++i)
        {
            cin>>m;
            a.push_back(m);
        }
        for(int i=0;i!=n;++i)
        {
            cin>>m;
            b.push_back(m);
        }
        vector<int>::iterator ia,ib;
        ia=a.begin();
        ib=b.begin();
        while(ia!=a.end()&&ib!=b.end())
        {
            while(*ia<*ib&&ia!=a.end())
                ia++;
            if(*ia==*ib)
                c.push_back(*ia++);
            while(*ia>*ib&&ib!=b.end())
                ib++;
            if(*ia==*ib)
                c.push_back(*ib++);
        }
        a.clear();
        b.clear();
        cout<<c.size();
        ia=c.begin();
        while(ia!=c.end())
            cout<<" "<<*ia++;
        c.clear();
        cout<<endl;
    }

}
