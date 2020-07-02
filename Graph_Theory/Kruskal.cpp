/*
	题目描述：

		国防部计划用无线网络连接若干个边防哨所。2 种不同的通讯技术用来搭建无线网络；
		每个边防哨所都要配备无线电收发器；有一些哨所还可以增配卫星电话。
		任意两个配备了一条卫星电话线路的哨所（两边都ᤕ有卫星电话）均可以通话，无论他们相距多远。而只通过无线电收发器通话的哨所之间的距离不能超过 D，这是受收发器的功率限制。收发器的功率越高，通话距离 D 会更远，但同时价格也会更贵。
		收发器需要统一购买和安装，所以全部哨所只能选择安装一种型号的收发器。换句话说，每一对哨所之间的通话距离都是同一个 D。你的任务是确定收发器必须的最小通话距离 D，使得每一对哨所之间至少有一条通话路径（直接的或者间接的）。
	
	思路：Kruskal模板
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int INF    = 0x3f3f3f3f;
const int MAX_N  = 1e6 + 10;
const int MOD    = 1000000007;
const double PI  = acos(-1.0);
const double EPS = 1e-10;

int S,P,cnt=0;
double ans=0;

struct Node{ int x,y;}node[505];

struct Edge
{
    int from,to;
    double dis;
}edge[505 * 505];

int f[505*505];

bool cmp(const Edge a,const Edge b){return a.dis<b.dis;}

double get_dis(int f,int t)
{
    return sqrt((node[f].x-node[t].x)*(node[f].x-node[t].x)+(node[f].y-node[t].y)*(node[f].y-node[t].y));
}

void to_change(int f,int t,double val)
{
    edge[cnt].from=f;
    edge[cnt].to=t;
    edge[cnt].dis=val;
    cnt++;
}

int find(int x)
{
    if(f[x]==x) return x;
    else return f[x]=find(f[x]);
}

void krus()
{
    int tot=0;
    for(int i=0;i<P;i++) f[i]=i;
    for(int i=0;i<cnt;i++)
    {
        if(tot==P-S) break;
        int x=find(edge[i].from);
        int y=find(edge[i].to);
        if(x!=y)
        {
            f[x]=y;
            tot++;
            ans=edge[i].dis;
        }
    }
}

int main(void)
{ 
    scanf("%d%d",&S,&P);
    for(int i=0;i<P;i++)
        scanf("%d%d",&node[i].x,&node[i].y);

    for(int i=0;i<P;i++)
    {
        for(int j=0;j<P;j++)
        {
            if(i==j) continue;
            to_change(i,j,get_dis(i,j));
        }
    }
    sort(edge,edge+cnt,cmp);
    // for(int i=0;i<cnt;i++) printf("%d %d %lf\n",edge[i].from,edge[i].to,edge[i].dis);
    krus();
    printf("%.2f\n",ans);

    return 0;
}
