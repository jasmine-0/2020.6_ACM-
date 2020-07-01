/*
	题目：求 1,2,⋯ ,N 中素数的个数。
	
	思路：线性筛模板
	
	2020.6.17
*/

#include<bits/stdc++.h>

const int INF    = 0x3f3f3f3f;
const int MAX_N  = 1e8 + 5;
const int MOD    = 1000000007;

int prime[5800000];
bool vis[MAX_N];
int n,ans;

void Prime()
{
    ans=0;
    for(int i=2;i<=n;i++)
    {
        if(!vis[i])
            prime[++ans]=i;
        for(int j=1;j<=ans && i*prime[j]<=n;j++)
        {
            vis[i*prime[j]]=true;
            if(!(i%prime[j]))
                break;
        }
    }
}


int main(void)
{ 
    scanf("%d",&n);
    Prime();
    printf("%d\n",ans);

    return 0;
}
