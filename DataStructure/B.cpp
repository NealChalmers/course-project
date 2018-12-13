#include <iostream>

 using namespace std;

 int main()
 {
     long long int n,g,m;
     while(cin>>m)
     {
        if(m>1)
        {
            n=m-1;
            g=(n*(n+1)*(2*n+1)/6+n*(n+1)/2)/2;
            cout<<g<<" "<<(m+1)*3<<endl;
        }
        else
        {
            g=0;
            cout<<g<<" "<<"RANDOM"<<endl;
        }
    }
 }
