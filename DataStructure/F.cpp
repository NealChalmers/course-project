#include<iostream>
#include<stdio.h>

using namespace std;

#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1


int ans[100001];
int xw[100001];
const int maxn=200000;
int w,sum[maxn<<2];

void build(int l,int r,int rt)
{
    sum[rt] = r - l + 1;
    if(l == r) return ;
    int m = (l+r) >> 1;
    build(lson);
    build(rson);
}

int update(int p,int l,int r,int rt)
{
    sum[rt]--;
    if(l == r) return l ;
    int m = (l + r) >> 1;
    if(p <= sum[rt<<1])
        return    update(p,lson);
    else
        return   update(p-sum[rt<<1],rson);

}

int main()
{
    int n,m,i;
    int x,A,B,M;
    while(scanf("%d%d%d%d%d%d",&n,&m,&x,&A,&B,&M)!=EOF)
    {
        build(1,n,1);
        int z = 1;
        for(i = 1; i <= n; i++)
        {
            z = ((int)x+z)%sum[1];
            if(z == 0) z = sum[1];
            int s = update(z,1,n,1);
            ans[i] = s;
            x = (int)(((long long)x * A + B) % M);
        }
        for(i = 0; i < m; i++)
            scanf("%d",&xw[i]);
        for(i=0;i<m-1;i++)
            printf("%d ",ans[xw[i]]);
        if(m!=0) printf("%d",ans[xw[m-1]]);
        printf("\n");
    }
}
