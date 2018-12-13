#include <iostream>

using namespace std;

int main()
{
    long long n;
    while(cin>>n)
    {
        long long m=n,cc=1;
        while(m!=1)
        {
            m/=2;
            cc*=2;
        }
        cout<<(n-cc)*2+1<<endl;
    }
}
