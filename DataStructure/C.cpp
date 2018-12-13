#include <iostream>
#include <memory.h>

using namespace std;

int main()
{
    bool dd[1000];
    int n;
    while(cin>>n)
    {
        memset(dd,0,1000*sizeof(bool));
        int p=0,q=0,m=n;
        while(m!=1)
        {
            if(dd[q])
            {
                q++;
                q%=n;
                continue;
            }
            if(p)
            {
                dd[q]=1;
                m--;
            }
            p=!p;
            q++;
            q%=n;
        }
        for(int i=0;i!=n;++i)
        {
            if(!dd[i])
            {
                cout<<i+1<<endl;
                break;
            }
        }
    }
}
