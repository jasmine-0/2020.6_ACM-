/*
	题目描述：
		给出一个 n 个点，m 条边的无向图，求图的割点。
	
	思路：割点模板
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int INF    = 0x3f3f3f3f;
const long long MAX_N  = 1e6 + 10;
const int MOD    = 1000000007;
const double PI  = acos(-1.0);
const double EPS = 1e-10;

int a[MAX_N], nxt[MAX_N], head[MAX_N], dfn[MAX_N], low[MAX_N], cnt=0, k=0;
bool cut[MAX_N],bst[MAX_N];

void add(int x,int y)
{
    a[++k]=y;
    nxt[k]=head[x];
    head[x]=k;
}

void tarjan(int u,int mr)
{
    int rc=0;
    dfn[u] = low[u] = ++cnt;
    for(int p=head[u]; p; p=nxt[p])
    {
        int v=a[p];
        if(!dfn[v])
        {
            tarjan(v,mr);
            low[u]=min(low[u],low[v]);
            if(low[v] >= dfn[u] && u!=mr)
                cut[u]=true;
            if(u==mr) rc++;
        }
        low[u]=min(low[u],dfn[v]);
    }
    if(u == mr && rc>=2) cut[mr]=true;
}

int main(void)
{
    int n,m,ans=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) tarjan(i,i);

    for (int i=1;i<=n;i++) 
        if (cut[i]) ans++;
    printf("%d\n",ans);
    for (int i=1;i<=n;i++) 
        if (cut[i]) printf("%d ",i);

    return 0;
}
