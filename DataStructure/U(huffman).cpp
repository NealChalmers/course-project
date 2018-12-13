#include <queue>
#include <cstdio>
#include <vector>
#include <functional>

using namespace std;

priority_queue<long long int,vector<long long int>,greater<long long int> > pi;
long long re,ti,i1,i2;

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        re=0;
        for(int i=0; i!=n; ++i)
        {
            scanf("%lld",&ti);
            pi.push(ti);
        }
        while(pi.size()!=1)
        {
            i1=pi.top();
            pi.pop();
            i2=pi.top();
            pi.pop();
            ti=i1+i2;
            pi.push(ti);
            re+=ti;
            re%=1000000007;
        }
        pi.pop();
        printf("%lld\n",re);
    }
}
