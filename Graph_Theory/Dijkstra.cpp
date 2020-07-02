/*
	题目：送餐，已知在地图上，有 N 个地方，而且目前处在标注为 “1” 的小镇上，而送餐的地点在标注为 “N” 的小镇，且路都是单向的。
		从小镇 I 到 J 需要花费 D[I,J] 的时间，问送到每个顾客所花的最短路的条数？
	
	思路：Dijkstra算法
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int INF    = 0x3f3f3f3f;

int G[2005][2005];
int dis[2005],vis[2005],cnt[2005];

struct edge
{
    int to,dis;

    edge(int t,int d){to=t,dis=d;}

    bool operator<(const edge &a)const { return this->dis > a.dis;}
};
vector<edge> node[2005];

void dij(int n)
{
    memset(dis,INF,sizeof(dis));
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
    dis[1]=0; cnt[1]=1;
    priority_queue<edge> que;
    que.push(edge(1,dis[1]));
    while(!que.empty())
    {
        edge now=que.top();
        que.pop();
        if(vis[now.to]) continue;
        vis[now.to]=1;
        for(int i=0;i<node[now.to].size();i++)
        {
            edge nex=node[now.to][i];
            if(!vis[nex.to])
            {
                if(dis[nex.to]==dis[now.to]+nex.dis)
                    cnt[nex.to]+=cnt[now.to];
                else if(dis[nex.to] > dis[now.to]+nex.dis)
                {
                    dis[nex.to]=dis[now.to]+nex.dis;
                    cnt[nex.to]=cnt[now.to];
                    que.push(edge(nex.to,dis[nex.to]));
                }
            }
        }
    }

    if(dis[n]>=INF-1)
        printf("No answer\n");
    else printf("%d %d\n",dis[n],cnt[n]);
}

int main(void)
{
    int N,E,a,b,c;
    scanf("%d%d",&N,&E);
    memset(G,INF,sizeof(G));
    for(int i=0;i<E;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        if(G[a][b]>c) G[a][b]=c;
    }
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            if(G[i][j]<INF)
                node[i].push_back(edge(j,G[i][j]));
    dij(N);

    return 0;
}
