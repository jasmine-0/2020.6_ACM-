/*
	题目描述:
		给定一个 n 个点，m 条有向边的带非负权图，请你计算从 s 出发，到每个点的距离。
		数据保证你能从 s 出发到任意点。
	
	思路：单源最短路径模板
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int INF    = 0x3f3f3f3f;
const long long MAX_N  = 1e5 + 10;
const int MOD    = 1000000007;
const double PI  = acos(-1.0);
const double EPS = 1e-10;

ll n,m,s,u,v,w;

struct edge
{
    ll from, to, w;
    edge(ll f,ll t,ll w_){ from=f; to=t; w=w_;}
};
vector<edge> adj[500100];

struct node
{
    ll id, dis;
    node(int i,int d) { id=i; dis=d;}
    bool operator < (const node &a) const{return dis>a.dis;}
};

bool vis[500100];
ll d[500100];

void dijst(ll s)
{
    for(ll i=1;i<=n;i++) { vis[i]=false; d[i]=INF;}
    d[s]=0;
    priority_queue<node> Q;
    Q.push(node(s,d[s]));

    while(!Q.empty())
    {
        node v=Q.top(); Q.pop();
        if(vis[v.id]) continue;
        vis[v.id]=true;
        for(int i=0;i<adj[v.id].size();i++)
        {
            edge now=adj[v.id][i];
            if(vis[now.to]) continue;
            if(now.w+v.dis < d[now.to])
            {
                d[now.to]=now.w+v.dis;
                Q.push(node(now.to,d[now.to]));
            }
        }
    }
    for(int i=1;i<=n;i++)
        printf("%lld ",d[i]);
}


int main(void)
{
    scanf("%lld%lld%lld",&n,&m,&s);
    for(ll i=0;i<m;i++)
    {
        scanf("%lld%lld%lld",&u,&v,&w);
        adj[u].push_back(edge(u,v,w));
    }
    dijst(s);

    return 0;
}
