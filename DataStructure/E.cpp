#include<cstdio>
using namespace std;
long long solve(long long n,long long m,long long s)
{
    if(m==1) return (n-1+s)%n;
    long long start=0,i=2;
    while(i<=n)
    {
        if(start+m<i)
        {
            long long x;
            if((i-start-1)%(m-1))
                x=(i-start-1)/(m-1);
            else
                x=(i-start-1)/(m-1)-1;
            if(i+x>n)
            {
                start+=(n+1-i)*m;
                break;
            }
            i+=x;
            start+=x*m;
        }
        else
        {
            start=(start+m)%i;
            i++;
        }
    }
    return (start+s)%n;
}
int main()
{
    long long n,m;
    while(scanf("%lld %lld",&n,&m)!=EOF)
    {
        long long start=solve(n,m,1);
        printf("%lld\n",start?start:n);
    }
}
