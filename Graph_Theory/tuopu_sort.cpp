/*
	题目描述：
		一个不同的值的升序排序数列指的是一个从左到右元素依次增大的序列，例如，一个有序的数列A,B,C,D 表示A<B,B<C,C<D。
		在这道题中，我们将给你一系列形如A<B的关系，并要求你判断是否能够根据这些关系确定这个数列的顺序。
	
	思路：拓扑排序
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int INF    = 0x3f3f3f3f;
const long long MAX_N  = 3e4 + 10;
const int MOD    = 1000000007;
const double PI  = acos(-1.0);
const double EPS = 1e-10;

inline int read()
{
    int date=0,m=1; char ch=0;
    while((ch<'0' || ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-'){ m=-1; ch=getchar();}
    while(ch>='0' && ch<='9'){ date=date*10+ch-'0'; ch=getchar();}
    return date*m;
}

inline void write(int x){
    if(x<0){ putchar('-'); x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

int n,m,idx;
int indeg[30],tmp[30],stk[30],top,d[30];
bool circle=false,certain=false;
vector<int> G[30];
char op[10];

inline void add_edge(int from,int to)
{
    G[from].push_back(to);
    indeg[to]++;
}

void tuopu_sort(int now)
{
    queue<int> q;
    int dep=1;
    for(int i=1;i<=n;i++) d[i]=0;
    for(int i=1;i<=n;i++)
    {
        tmp[i]=indeg[i];
        if(tmp[i]==0)
        {
            q.push(i);
            d[i]=1;
        }
    }
    top=0;
    while(!q.empty())
    {
        int u=q.front(); q.pop();
        stk[++top]=u;
        for(int i=0;i<G[u].size();i++)
        {
            int v=G[u][i];
            --tmp[v];
			if(!tmp[v]) q.push(v);
			d[v]=max(d[v],d[u]+1);
			dep=max(dep,d[v]);
        }
    }
    if(top^n) circle=1, idx=now;
	else if(dep==n) certain=1, idx=now;
}

int main(void)
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%s",op+1);
        if(circle || certain) break;
        int from=op[1]-'A'+1;
        int to=op[3]-'A'+1;
        add_edge(from,to);
        tuopu_sort(i);
    }
    if(certain){
		printf("Sorted sequence determined after %d relations: ",idx);
		for(int i=1;i<=n;i++)printf("%c",stk[i]+'A'-1);
		printf(".\n");
	}
	else if(circle)printf("Inconsistency found after %d relations.\n",idx);
	else printf("Sorted sequence cannot be determined.\n");

    return 0;
}