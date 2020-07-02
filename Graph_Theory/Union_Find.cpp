/*
	题目描述：
		S 城现有两座监狱，一共关押着 N 名罪犯，编号分别为 1−N。他们之间的关系自然也极不和谐。很多罪犯之间甚至积怨已久，如果客观条件具备则随时可能爆发冲突。我们用“怨气值”（一个正整数值）来表示某两名罪犯之间的仇恨程度，怨气值越大，则这两名罪犯之间的积怨越多。如果两名怨气值为 c 的罪犯被关押在同一监狱，他们俩之间会发生摩擦，并造成影响力为 c 的冲突事件。
		每年年末，警察局会将本年内监狱中的所有冲突事件按影响力从大到小排成一个列表，然后上报到 S 城 Z 市长那里。公务繁忙的 Z 市长只会去看列表中的第一个事件的影响力，如果影响很坏，他就会考虑撤换警察局长。
		在详细考察了N 名罪犯间的矛盾关系后，警察局长觉得压力巨大。他准备将罪犯们在两座监狱内重新分配，以求产生的冲突事件影响力都较小，从而保住自己的乌纱帽。假设只要处于同一监狱内的某两个罪犯间有仇恨，那么他们一定会在每年的某个时候发生摩擦。
		那么，应如何分配罪犯，才能使 Z 市长看到的那个冲突事件的影响力最小？这个最小值是多少？
	
	思路：并查集版子
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
    int u,v,w;
}criminal[MAX_N];

bool cmp(const node a,const node b){return a.w>b.w;}

int f[MAX_N],b[MAX_N];
int n,m;

inline int find(int x)
{
    if(f[x]==x) return x;
    return f[x]=find(f[x]);
}

int main(void)
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&criminal[i].u,&criminal[i].v,&criminal[i].w);
    sort(criminal+1,criminal+m+1,cmp);
    for(int i=1;i<=n;i++) f[i]=i;

    for(int i=1;i<=m;i++)
    {
        int x=find(criminal[i].u);
        int y=find(criminal[i].v);

        if(x==y) 
        {
            printf("%d\n",criminal[i].w);
            return 0;
        }
        if(!b[criminal[i].u]) b[criminal[i].u]=criminal[i].v;
        else f[find(b[criminal[i].u])]=f[criminal[i].v];

        if(!b[criminal[i].v]) b[criminal[i].v]=criminal[i].u;
        else f[find(b[criminal[i].v])]=f[criminal[i].u];
    }
    printf("0\n");

    return 0;
}
