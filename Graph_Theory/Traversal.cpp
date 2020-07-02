/*
	题目描述：
		给出N个点，M条边的有向图，对于每个点v，求A(v)表示从点v出发，能到达的编号最大的点。
		
	思路：图的遍历
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int INF    = 0x3f3f3f3f;
const long long MAX_N  = 1e5 + 10;
const int MOD    = 1000000007;
const double PI  = acos(-1.0);
const double EPS = 1e-10;

struct node
{
    int from,to;
};

vector<int> G[MAX_N];
int lo[MAX_N];

void dfs(int f,int d)
{
    if(lo[f]) return;
    lo[f]=d;
    for(int i=0;i<G[f].size();i++)
    {
        dfs(G[f][i],d);
    }
}

int main(void)
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[v].push_back(u);
    }
    for(int i=n;i>0;i--)
    {
        dfs(i,i);
    }
    for(int i=1;i<=n;i++)
        printf("%d ",lo[i]);
    printf("\n");

    return 0;
}
