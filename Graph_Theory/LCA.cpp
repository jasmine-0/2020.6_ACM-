/*
	题目描述:如题，给定一棵有根多叉树，请求出指定两个点直接最近的公共祖先。
	
	思路：LCA模板
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int INF    = 0x3f3f3f3f;
const long long MAX_N  = 5e5 + 10;
const int MOD    = 1000000007;
const double PI  = acos(-1.0);
const double EPS = 1e-10;

int n,m,s;
int cnt=0;
int head[MAX_N],d[MAX_N],p[MAX_N][21];
struct Edge
{
    int v,next;
}edge[MAX_N << 1];

void build(int x,int y)
{
    edge[cnt].v=y;
    edge[cnt].next=head[x];
    head[x]=cnt++;
}

void dfs(int u,int fa)
{
    d[u]=d[fa]+1;
    p[u][0]=fa;
    for(int i=1;(1<<i)<=d[u];i++)
        p[u][i]=p[p[u][i-1]][i-1];
    for(int i=head[u]; i!=-1; i=edge[i].next)
    {
        int v=edge[i].v;
        if(v!=fa)
            dfs(v,u);
    }
}

int lca(int a,int b)
{
    if(d[a]>d[b]) swap(a,b);
    for(int i=20;i>=0;i--)
        if(d[a]<=d[b]-(1<<i))
            b=p[b][i];

    if(a==b)
        return a;
    
    for(int i=20;i>=0;i--)
    {
        if(p[a][i]==p[b][i])
            continue;
        else
            a=p[a][i], b=p[b][i];
    }
    return p[a][0];
}

int main(void)
{
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&s);
    int x,y;
    for(int i=1;i<=n-1;i++)
    {
        scanf("%d%d",&x,&y);
        build(x,y);
        build(y,x);
    }
    dfs(s,0);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x,y));
    }
    
    return 0;
}
