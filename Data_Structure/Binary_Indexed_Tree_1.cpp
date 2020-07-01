/*
	问题：如题，已知一个数列，你需要进行下面两种操作：
		将某一个数加上 xxx
		求出某区间每一个数的和

	思路：树状数组模板
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int INF    = 0x3f3f3f3f;
const long long MAX_N  = 5e5 + 10;
const int MOD    = 1000000007;
const double PI  = acos(-1.0);
const double EPS = 1e-10;

int m,n;
int tree[4*MAX_N];

void add_(int x,int k)
{
    while(x<=n)
    {
        tree[x]+=k;
        x+=lowbit(x);
    }
}

int sum_(int x)
{
    int ans=0;
    while(x>0)
    {
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int main(void)
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int a;
        scanf("%d",&a);
        add_(i,a);
    }
    for(int i=1;i<=m;i++)
    {
        int op,b,c;
        scanf("%d%d%d",&op,&b,&c);
        if(op==1) add_(b,c);
        if(op==2) printf("%d\n",sum_(c)-sum_(b-1));
    }

    return 0;
}
