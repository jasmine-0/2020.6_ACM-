# 图论

首先，图论有一堆基本概念：子图、连通、同构......

**图的储存方式**：邻接表，邻接矩阵，**链式前向星**。

## 链式前向星

链式前向星其实就是静态建立的邻接表，时间效率为O(m)，空间效率也为O(m)。遍历效率也为O(m）。

```C++
int n, m, cnt;//n个点，m条边
struct Edge
{
    int to, w, next;//终点，边权，同起点的上一条边的编号
}edge[maxn];//边集
int head[maxn];//head[i],表示以i为起点的第一条边在边集数组的位置（编号）
void init()//初始化
{
    for (int i = 0; i <= n; i++) head[i] = -1;
    cnt = 0;
}
void add_edge(int u, int v, int w)//加边，u起点，v终点，w边权
{
    edge[cnt].to = v; //终点
    edge[cnt].w = w; //权值
    edge[cnt].next = head[u];
    //以u为起点上一条边的编号，也就是与这个边起点相同的上一条边的编号
    head[u] = cnt++;//更新以u为起点上一条边的编号
}
```

```C++
// 完整代码
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;//点数最大值
int n, m, cnt;//n个点，m条边
struct Edge
{
    int to, w, next;//终点，边权，同起点的上一条边的编号
}edge[maxn];//边集
int head[maxn];//head[i],表示以i为起点的第一条边在边集数组的位置（编号）
void init()//初始化
{
    for (int i = 0; i <= n; i++) head[i] = -1;
    cnt = 0;
}
void add_edge(int u, int v, int w)//加边，u起点，v终点，w边权
{
    edge[cnt].to = v; //终点
    edge[cnt].w = w; //权值
    edge[cnt].next = head[u];
    //以u为起点上一条边的编号，也就是与这个边起点相同的上一条边的编号
    head[u] = cnt++;//更新以u为起点上一条边的编号
}
int main()
{
    cin >> n >> m;
    int u, v, w;
    init();//初始化
    for (int i = 1; i <= m; i++)//输入m条边
    {
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    for (int i = 1; i <= n; i++)//n个起点
    {
        cout << i << endl;
        for (int j = head[i]; j != -1; j = edge[j].next)//遍历以i为起点的边
        {
            cout << i << " " << edge[j].to << " " << edge[j].w << endl;
        }
        cout << endl;
    }
    return 0;
}
```



## 拓扑排序

拓扑排序要解决的问题是给一个图的所有节点排序。经典问题：考虑前置课程的课程的安排顺序。

```C++
// 代码的核心是，是维持一个入度为 0 的顶点。
void tuopu_sort()
{
	queue<int>q;
    vector<int>edge[n];
    for(int i=0;i<n;i++)  //n  节点的总数
        if(in[i]==0) q.push(i);  //将入度为0的点入队列
    vector<int>ans;   //ans 为拓扑序列
    while(!q.empty())
    {
        int p=q.front(); q.pop(); // 选一个入度为0的点，出队列
        ans.push_back(p);
        for(int i=0;i<edge[p].size();i++)
        {
            int y=edge[p][i];
            in[y]--;
            if(in[y]==0)
                q.push(y);  
        }
    }
    if(ans.size()==n)   
    {
        for(int i=0;i<ans.size();i++)
            printf( "%d ",ans[i] );
        printf("\n");
    }
    else printf("No Answer!\n");   
}
```

```C++
// dfs 版本
bool dfs(int u) {
  	c[u] = -1;
  	for (int v = 0; v <= n; v++)
    	if (G[u][v]) {
      		if (c[v] < 0)
        		return false;
      		else if (!c[v])
        		dfs(v);
    	}
  	c[u] = 1;
  	topo.push_back(u);
  	return true;
}
bool toposort() {
  	topo.clear();
  	memset(c, 0, sizeof(c));
  	for (int u = 0; u <= n; u++)
    	if (!c[u])
      		if (!dfs(u)) return false;
  	reverse(topo.begin(), topo.end());
  	return true;
}
```



## 最近公共祖先LCA

时间复杂度 *O*((*n*+*q*)log*n*)，*n*是问题规模，*q*是询问个数
 **倍增法求*LCA***
*fa*[*i*,*j*]表示从*i*开始向上走*2^j*所能到达的节点 (0≤*j*≤log*n*)
*depth*[*i*]表示节点*i*的深度
 哨兵：如果从*i*开始跳*2^j*步会跳过根节点，那么*fa*[i,2^j]=0，*depth*[0]=0

1. 先将两个节点跳到同一层
2. 让两个节点同时往上跳，一直跳到他们最近公共祖先的下一层。

```C++
inline void getdeep(int now,int father)//now表示当前节点，father表示它的父亲节点
{
	deep[now]=deep[father]+1;
	fa[now][0]=father;
	for(int i=1;(1<<i)<=deep[now];i++)
		fa[now][i]=fa[fa[now][i-1]][i-1];//这个转移可以说是算法的核心之一
						//意思是f的2^i祖先等于f的2^(i-1)祖先的2^(i-1)祖先
						//2^i=2^(i-1)+2^(i-1)
	for(int i=head[now];i;i=edge[i].next)//注：尽量用链式前向星来存边，速度会大大提升
	{
		if(edge[i].to==father)continue;
		getdeep(edge[i].to,now);
	}
}
```

```log2n=log(n)/log(2)+0.5;```

```C++
inline int lca(int u,int v)
{
	int deepu=deep[u],deepv=deep[v];
	if(deepu!=deepv)//先跳到同一深度
	{
		if(deep[u]<deep[v])
		{
			swap(u,v);
			swap(deepu,deepv);
		}
		int d=deepu-deepv;
		for(int i=0;i<=log2n;i++)
			if((1<<i)&d)u=fa[u][i];
	}
	if(u==v)return u;
	for(int i=log2n;i>=0;i--)
	{
		if(deep[fa[u][i]]<=0)continue;
		if(fa[u][i]==fa[v][i])continue;
		else u=fa[u][i],v=fa[v][i];
        //因为我们要跳到它们LCA的下面一层，所以它们肯定不相等，如果不相等就跳过去。
	}
	return fa[u][0];
}
```

或者这个代码更容易理解：

```C++
int LCA(int x, int y) {
	if(depth[x] < depth[y]) 
    	swap(x, y);
    while(depth[x] > depth[y])
    	x = fa[x][lg[depth[x]-depth[y]] - 1]; //先跳到同一深度
	if(x == y)  
    	return x;
	for(int k = lg[depth[x]] - 1; k >= 0; --k) 
    //不断向上跳（lg就是之前说的常数优化）
    	if(fa[x][k] != fa[y][k])  
        //因为我们要跳到它们LCA的下面一层，所以它们肯定不相等，如果不相等就跳过去。
        	x = fa[x][k], y = fa[y][k];
	return fa[x][0];  //返回父节点
}
```



## Tarjan 算法

### 算法求强连通分量

首先，一个概念：强连通分量(scc, strong connected component)

Tarjan 算法是基于**深度优先搜索的算法，用于求解图的连通性问题**。Tarjan 算法可以在线性时间内求出无向图的割点与桥，进一步地可以求解无向图的双连通分量；同时，也可以求解有向图的强连通分量、必经点与必经边。

先引入两个非常重要的数组：*dfn[ ]* 与 *low[ ]*

- **dfn[ ]**：就是一个时间戳（被搜到的次序），一旦某个点被DFS到后，这个时间戳就不再改变（且每个点只有唯一的时间戳）。所以常根据dfn的值来判断是否需要进行进一步的深搜。
- **low[ ]**：该子树中，且仍在栈中的最小时间戳，像是确立了一个关系，low[ ]相等的点在同一强连通分量中。

注意初始化时 dfn[ ] = low[ ] = ++cnt.

```c++
int dfn[N], low[N], dfncnt, s[N], in_stack[N], tp;
int scc[N], sc;  // 结点 i 所在 scc 的编号
int sz[N];       // 强连通 i 的大小
void tarjan(int u) {
  	low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
  	for (int i = h[u]; i; i = e[i].nex) {
    	const int &v = e[i].t;
    	if (!dfn[v]) {
      		tarjan(v);
      		low[u] = min(low[u], low[v]);
    	} else if (in_stack[v]) {
      		low[u] = min(low[u], dfn[v]);
    	}
  	}
  	if (dfn[u] == low[u]) {
    	++sc;
    	while (s[tp] != u) {
      		scc[s[tp]] = sc;
      		sz[sc]++;
      		in_stack[s[tp]] = 0;
      		--tp;
    	}
    	scc[s[tp]] = sc;
    	sz[sc]++;
    	in_stack[s[tp]] = 0;
    	--tp;
  	}
}
```



### 割点和桥

下面代码实现了求割边，其中，当 `isbridge[x]` 为真时， `(father[x],x)` 为一条割边。

```C++
int low[MAXN], dfn[MAXN], iscut[MAXN], dfs_clock;
bool isbridge[MAXN];
vector<int> G[MAXN];
int cnt_bridge;
int father[MAXN];

void tarjan(int u, int fa) {
  	father[u] = fa;
  	low[u] = dfn[u] = ++dfs_clock;
  	for (int i = 0; i < G[u].size(); i++) {
    	int v = G[u][i];
    	if (!dfn[v]) {
      		tarjan(v, u);
      		low[u] = min(low[u], low[v]);
      		if (low[v] > dfn[u]) {
        		isbridge[v] = true;
        		++cnt_bridge;
      		}
    	} else if (dfn[v] < dfn[u] && v != fa) {
      		low[u] = min(low[u], dfn[v]);
    	}
  	}
}
```



## 欧拉图

给定一张有 500 个顶点的无向图，求这张图的一条欧拉路或欧拉回路。如果有多组解，输出最小的那一组。

**Hierholzer** 算法

```C++
#include <algorithm>
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

struct edge {
  int to;
  bool exists;
  int revref;

  bool operator<(const edge& b) const { return to < b.to; }
};

vector<edge> beg[505];
int cnt[505];

const int dn = 500;
stack<int> ans;

void Hierholzer(int x) {  // 关键函数
  for (int& i = cnt[x]; i < (int)beg[x].size();) {
    if (beg[x][i].exists) {
      edge e = beg[x][i];
      beg[x][i].exists = 0;
      beg[e.to][e.revref].exists = 0;
      ++i;
      Hierholzer(e.to);
    } else {
      ++i;
    }
  }
  ans.push(x);
}

int deg[505];
int reftop[505];

int main() {
  for (int i = 1; i <= dn; ++i) {
    beg[i].reserve(1050);  // vector 用 reserve 避免动态分配空间，加快速度
  }

  int m;
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    beg[a].push_back((edge){b, 1, 0});
    beg[b].push_back((edge){a, 1, 0});
    ++deg[a];
    ++deg[b];
  }

  for (int i = 1; i <= dn; ++i) {
    if (!beg[i].empty()) {
      sort(beg[i].begin(), beg[i].end());  // 为了要按字典序贪心，必须排序
    }
  }

  for (int i = 1; i <= dn; ++i) {
    for (int j = 0; j < (int)beg[i].size(); ++j) {
      beg[i][j].revref = reftop[beg[i][j].to]++;
    }
  }

  int bv = 0;
  for (int i = 1; i <= dn; ++i) {
    if (!deg[bv] && deg[i]) {
      bv = i;
    } else if (!(deg[bv] & 1) && (deg[i] & 1)) {
      bv = i;
    }
  }

  Hierholzer(bv);

  while (!ans.empty()) {
    printf("%d\n", ans.top());
    ans.pop();
  }
}
```



## 并查集

### 路径压缩

路径压缩，就是在每次查找时，令查找路径上的每个节点都直接指向根节点。

```C++
int find(int x) {
	if (x != uset[x]) uset[x] = find(uset[x]);
	return uset[x];
}
     
int find(int x) {//查找根节点
	int p = x, t;
	while (uset[p] != p) p = uset[p];//返回根节点；
	while (x != p) { t = uset[x]; uset[x] = p; x = t; }//路径压缩
	return x;
}
```

### 并查集的合并

**按秩合并**，在合并时，总是将具有较小秩的树根指向具有较大秩的树根。

```C++
void unionSet(int x, int y) {
	if ((x = find(x)) == (y = find(y))) return;
	if (rank[x] > rank[y]) uset[y] = x;
	else {
		uset[x] = y;
		if (rank[x] == rank[y]) rank[y]++;
	}
}
```

**按集合中包含的元素个数合并**，（或者说树中的节点数）将包含节点较少的树根，指向包含节点较多的树根。这个策略与按秩合并的策略类似，同样可以提升并查集的运行速度，而且省去了额外的 rank 数组。

```C++
void unionSet(int x, int y) {
    if ((x = find(x)) == (y = find(y))) return;
    if (uset[x] < uset[y]) {
        uset[x] += uset[y];
        uset[y] = x;
    } else {
        uset[y] += uset[x];
        uset[x] = y;
    }
}
```

