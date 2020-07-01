# Hash Table

**哈希表就是一种以键值对存储数据的结构。 **

​		当我们在编程过程中，往往需要对线性表进行查找操作。在顺序表中查找时，朴素的算法是，需要从表头开始，依次遍历比较a[i]与key的值是否相等，直到相等才返回索引i；在有序表中查找时，我们经常使用的是二分查找，通过比较key与a[i]的大小来折半查找，直到相等时才返回索引i。最终通过索引找到我们要找的元素。 

　　要说哈希表，我们必须先了解一种新的存储方式—散列技术。

　　散列技术是指在记录的存储位置和它的关键字之间建立一个确定的对应关系f，使每一个关键字都对应一个存储位置。即：```存储位置=f（关键字）```。这样，在查找的过程中，只需要通过这个对应关系f 找到给定值key的映射f（key）。只要集合中存在关键字和key相等的记录，则必在存储位置f（key）处。我们把这种对应关系f 称为散列函数或哈希函数。

　　按照这个思想，采用散列技术将记录存储在一块连续的存储空间中，这块连续的存储空间称为哈希表。所得的存储地址称为哈希地址或散列地址。

**构造方法：**

- **直接定址法**（不常用）
  取关键字或关键字的某个线性函数值为哈希地址：即：Ｈ```(key) = key``` 或 ```H(key) = a*key+b```
  优点：简单，均匀，不会产生冲突；
  缺点：需要实现直到关键字的分布情况，适合查找表比较小且连续的情况。　　
- **数字分析法**
  　　数字分析法用于处理关键字是位数比较多的数字，通过抽取关键字的一部分进行操作，计算哈希存储位置的方法。
    　　例如：关键字是手机号时，众所周知，我们的１１位手机号中，前三位是接入号，一般对应不同运营商的子品牌；中间四位是ＨＬＲ识别号，表示用户号的归属地；最后四位才是真正的用户号，所以我们可以选择后四位成为哈希地址，对其在进行相应操作来减少冲突。
    　　数字分析法适合处理关键字位数比较大的情况，事先知道关键字的分布且关键字的若干位分布均匀。
- **平方取中法**
  　　具体方法很简单：先对关键字取平方，然后选取中间几位为哈希地址；取的位数由表长决定，适用于不知道关键字的分布，而位数又不是很大的情况。
- **折叠法**
  　　 将关键字分成位数相同的几部分（最后一部分位数 可以不同），然后求这几部分的叠加和（舍去进位），并按照散列表的表长，取后几位作为哈希地址。适用于关键字位数很多，而且关键字每一位上数字分布大致均匀。
- **除留余数法 ★**
  　　 此方法为最常用的构造哈希函数方法。对于哈希表长为m的哈希函数公式为：
        　　 ```f(key) = key mod p (p <= m)```
        　　 此方法不仅可以对关键字直接取模，也可以在折叠、平方取中之后再取模。
        　　 所以，本方法的关键在于选择合适的p，若是p选择的不好，就可能产生 同义词；根据前人经验，若散列表的表长为m，通常p为小于或等于表长（最好接近m）的最小质数或不包含小于20质因子的合数。
- **随机数法**
  　　 选择一个随机数，取关键字的随机函数值作为他的哈希地址。 即：```f(key) = random (key)```
        　　 当关键字的长度不等时，采用这个方法构造哈希函数较为合适。当遇到特殊字符的关键字时，需要将其转换为某种数字。

**冲突处理办法：**

- **开放地址法**

  一旦发生了冲突就去寻找下一个空的哈希地址，只要哈希表足够大，空的散列地址总能找到，并将记录存入。 

- **再哈希法**

  公式：Hi = RHi（key）   i = 1，2，…，k 
  RHi均是不同的哈希函数，意思为：当繁盛冲突时，使用不同的哈希函数计算地址，直到不冲突为止。这种方法不易产生堆积，但是耗费时间。

- **链地址法**
  将所有关键字为同义字的记录存储在一个单链表中，我们称这种单链表为同义词子表，散列表中存储同义词子表的头指针。 

**算法实现：**

首先定义一个散列表的结构以及一些相关的常数。其中，HashTables是散列表结构。结构当中的elem为一个动态数组。

```c++
/* 首先定义一个散列表的结构以及一些相关的常数。
   其中，HashTables是散列表结构。结构当中的elem为一个动态数组。*/
#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12    /*定义哈希表长为数组的长度*/
#define NULLKEY -32768
{
    int *elem;        /*数组元素存储基址，动态分配数组*/
    int count;        /*当前数据元素的个数*/
}HashTable;
int m = 0;            

```

```C++
/*初始化哈希表*/
Status InitHashTable(HashTable *H)
{
    int i;
    m = HASHSIZE;
    H->count = m;
    H->elem = (int *)malloc(m*sizeof(int));
    for(i = 0;i<m;i++)
        H->elem[i] = NULLKEY;

    return OK;
}   
```

```c++
/*定义哈希函数*/
int Hash(int key)
{
    return key % m;     /*除留取余法*/
}
```

```C++
/*将关键字插入散列表*/
void InsertHash(HashTable *H,int key)
｛
     int addr = Hash(Key);             	/*求哈希地址*/
     while(H->elem[addr] != NULLKEY)    /*如果不为空则冲突*/
         addr = (addr + 1) % m;         /*线性探测*/
     H->elem[addr] = key;            	/*直到有空位后插入关键字*/        
｝   
```

```C++
/*查找*/
Status SearchHash(HashTable H,int key,int *addr)
{
    *addr = Hash(key);        		/*求哈希地址*/
    while(H.elem[*addr] != key)     /*若不为空，则冲突*/
    {
        *addr = (*addr + 1) % m;    /*线性探测*/
        if(H.elem[*addr) == NULLKEY || *addr == Hash(key))
        {							/*如果循环回到原点*/
            return UNSUCCESS;       /*则说明关键字不存在*/
        }
    }
    return SUCCESS;
} 
```

对于冲突的处理还有一种方法：拉链法

拉链法是在每个存放数据的地方开一个链表，如果有多个 key  索引到同一个地方，只用把他们都放到那个位置的链表里就行了。查询的时候需要把对应位置的链表整个扫一遍，对其中的每个数据比较其 key 与查询的  key 是否一致。如果索引的范围是 1~M，哈希表的大小为 N，那么一次插入/查询需要进行期望 O(N/M) 次比较。

```C++
const int SIZE = 1000000;
const int M = 999997;
struct HashTable {
  	struct Node {
    	int next, value, key;
  	} data[SIZE];
  	int head[M], size;
  	int f(int key) { return key % M; }
  	int get(int key) {
    	for (int p = head[f(key)]; p; p = data[p].next)
      		if (data[p].key == key) return data[p].value;
    	return -1;
  	}
  	int modify(int key, int value) {
    	for (int p = head[f(key)]; p; p = data[p].next)
      		if (data[p].key == key) return data[p].value = value;
  	}
  	int add(int key, int value) {
    	if (get(key) != -1) return -1;
    	data[++size] = (Node){head[f(key)], value, key};
    	head[f(key)] = size;
    	return value;
  	}
};
```

还有一个封装过的模板，可以像 map 一样用

```C++
struct hash_map {  // 哈希表模板
  	struct data {
    	long long u;
    	int v, nex;
  	};                // 前向星结构
  	data e[SZ << 1];  // SZ 是 const int 表示大小
  	int h[SZ], cnt;
  	int hash(long long u) { return u % SZ; }
  	int& operator[](long long u) {
    	int hu = hash(u);  // 获取头指针
    	for (int i = h[hu]; i; i = e[i].nex)
      		if (e[i].u == u) return e[i].v;
    	return e[++cnt] = (data){u, -1, h[hu]}, h[hu] = cnt, e[cnt].v;
  	}
  	hash_map() {
    	cnt = 0;
    	memset(h, 0, sizeof(h));
  	}
};
```



# 康托展开和逆康托展开

康托展开是一个全排列到一个自然数的双射，常用于构建hash表时的空间压缩。设有n个数（1，2，3，4,…,n），可以有组成不同(n!种)的排列组合，康托展开表示的就是是当前排列组合在n个不同元素的全排列中的名次。

```C++
const int factorial[]={1,1,2,6,24,120,720,5040,40320,362880,3628800};//阶乘0-10
int cantor(int a[],int n){//cantor展开,n表示是n位的全排列，a[]表示全排列的数（用数组表示）
    int ans=0,sum=0;
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++)
            if(a[j]<a[i])
                sum++;
        ans+=sum*factorial[n-i];//累积
        sum=0;//计数器归零
    }
    return ans+1;
}
```



# Sparse Table

ST表类似树状数组，线段树这两种算法，是一种用于解决RMQ(Range Minimum/Maximum Query,即区间最值查询)问题的离线算法。与线段树相比，预处理复杂度同为O(nlogn),查询时间上，ST表为O(1),线段树为O(nlogn)

```C++
int a[1010];//原始输入数组
int st[1010][20];//st表

void init(int n)
{
    for (int i = 0; i < n; i++)
        st[i][0] = a[i];

    for (int j = 1; (1 << j) <= n; j++)
    {
        for (int i = 0; i + (1 << j) - 1 < n; i++)
            st[i][j] = min(st[i][j - 1],st[i + (1 << (j - 1))][j - 1]);
    }
}
```

```c++
int search(int l, int r)
{
    int k = (int)(log((double)(r - l + 1)) / log(2.0));
    return min(st[l][k],st[r - (1 << k) + 1][k]);
}
```



# 线段树

线段树是用来维护区间信息的数据结构

**线段树的基本结构与建树：**

线段树将每个长度不为 1 的区间划分成左右两个区间递归求解，把整个线段划分为一个树形结构，通过合并左右两区间信息来求得该区间的信息。这种数据结构可以方便的进行大部分的区间操作。

```C++
void build(int s, int t, int p) {
  	// 对 [s,t] 区间建立线段树,当前根的编号为 p
  	if (s == t) {
    	d[p] = a[s];
    	return;
  	}
  	int m = (s + t) >> 1;
  	build(s, m, p * 2), build(m + 1, t, p * 2 + 1);
  	// 递归对左右区间建树
  	d[p] = d[p * 2] + d[(p * 2) + 1];
}
```

```C++
int getsum(int l, int r, int s, int t, int p) {
  	// [l,r] 为查询区间,[s,t] 为当前节点包含的区间,p 为当前节点的编号
  	if (l <= s && t <= r)
    	return d[p];  // 当前区间为询问区间的子集时直接返回当前区间的和
  	int m = (s + t) >> 1 , sum = 0;
  	if (l <= m) sum += getsum(l, r, s, m, p * 2);
  	// 如果左儿子代表的区间 [l,m] 与询问区间有交集,则递归查询左儿子
  	if (r > m) sum += getsum(l, r, m + 1, t, p * 2 + 1);
  	// 如果右儿子代表的区间 [m+1,r] 与询问区间有交集,则递归查询右儿子
  	return sum;
}
```



**懒惰标记**：

数组 b 为节点的懒惰标记值

区间修改（区间加上某个值）：

```C++
void update(int l, int r, int c, int s, int t, int p) {
  	// [l,r] 为修改区间,c 为被修改的元素的变化量,[s,t] 为当前节点包含的区间,p为当前节点的编号
  	if (l <= s && t <= r) {
    	d[p] += (t - s + 1) * c, b[p] += c;
    	return;
  	}  // 当前区间为修改区间的子集时直接修改当前节点的值,然后打标记,结束修改
  	int m = (s + t) / 2;
  	if (b[p] && s != t) {
    	// 如果当前节点的懒标记非空,则更新当前节点两个子节点的值和懒标记值
    	d[p * 2] += b[p] * (m - s + 1);
        d[p * 2 + 1] += b[p] * (t - m);
    	b[p * 2] += b[p];
        b[p * 2 + 1] += b[p];  // 将标记下传给子节点
    	b[p] = 0;              // 清空当前节点的标记
  	}
  	if (l <= m) update(l, r, c, s, m, p * 2);
  	if (r > m) update(l, r, c, m + 1, t, p * 2 + 1);
  	d[p] = d[p * 2] + d[p * 2 + 1];
}
```

区间查询（区间求和）：

```C++
int getsum(int l, int r, int s, int t, int p) {
  	// [l,r] 为查询区间,[s,t] 为当前节点包含的区间,p为当前节点的编号
  	if (l <= s && t <= r) return d[p];
  	// 当前区间为询问区间的子集时直接返回当前区间的和
  	int m = (s + t) >> 1;
  	if (b[p]) {
    	// 如果当前节点的懒标记非空,则更新当前节点两个子节点的值和懒标记值
    	d[p * 2] += b[p] * (m - s + 1);
        d[p * 2 + 1] += b[p] * (t - m);
        b[p * 2] += b[p], b[p * 2 + 1] += b[p];  // 将标记下传给子节点
    	b[p] = 0;                                // 清空当前节点的标记
  	}
  	int sum = 0;
  	if (l <= m) sum = getsum(l, r, s, m, p * 2);
  	if (r > m) sum += getsum(l, r, m + 1, t, p * 2 + 1);
  	return sum;
}
```

如果你是要实现区间修改为某一个值而不是加上某一个值的话，代码如下：

```C++
void update(int l, int r, int c, int s, int t, int p) {
  	if (l <= s && t <= r) {
    	d[p] = (t - s + 1) * c;
        b[p] = c;
    	return;
  	}
  	int m = (s + t) >> 1;
  	if (b[p]) {
    	d[p * 2] = b[p] * (m - s + 1);
        d[p * 2 + 1] = b[p] * (t - m);
        b[p * 2] = b[p * 2 + 1] = b[p];
    	b[p] = 0;
  	}
  	if (l <= m) update(l, r, c, s, m, p * 2);
  	if (r > m) update(l, r, c, m + 1, t, p * 2 + 1);
  	d[p] = d[p * 2] + d[p * 2 + 1];
}

int getsum(int l, int r, int s, int t, int p) {
  	if (l <= s && t <= r) return d[p];
  	int m = (s + t) >> 1;
  	if (b[p]) {
    	d[p * 2] = b[p] * (m - s + 1);
        d[p * 2 + 1] = b[p] * (t - m);
        b[p * 2] = b[p * 2 + 1] = b[p];
    	b[p] = 0;
  	}
  	int sum = 0;
  	if (l <= m) sum = getsum(l, r, s, m, p * 2);
  	if (r > m) sum += getsum(l, r, m + 1, t, p * 2 + 1);
  	return sum;
}
```



# 树状数组

树状数组的代码要比线段树短得多，思维也更清晰，在解决一些单点修改的问题时，可以考虑使用树状数组。

树状数组```lowbit()```函数所求的就是最低位1的位置所以可以通过位运算来计算 

```C++
int lowbit(x) {return x & -x;}
```

```C++
int getsum(int x) {
  	int ans = 0;
  	while (x >= 1) {
    	ans = ans + c[x];
    	x = x - lowbit(x);
  	}
  	return ans;
}
```

```C++
// 单点修改
void add(int x, int k) {
  	while (x <= n) {
    	c[x] = c[x] + k;
    	x = x + lowbit(x);
  	}
}
```

**区间加 & 区间求和：**

维护序列 a 的差分数组 b ，ai =  Σ bj ( j = 1 ~ i )

区间和可以用两个前缀和相减得到，因此只需要用两个树状数组分别维护 Σ bi 和 Σ i*bi，就可以实现区间求和。

```C++
int t1[MAXN], t2[MAXN], n;

inline int lowbit(int x) { return x & (-x); }

void add(int k, int v) {
  	int v1 = k * v;
  	while (k <= n) {
    	t1[k] += v, t2[k] += v1;
    	k += lowbit(k);
  	}
}

int getsum(int *t, int k) {
  	int ret = 0;
  	while (k) {
    	ret += t[k];
    	k -= lowbit(k);
  	}
  	return ret;
}

void add1(int l, int r, int v) {
  	add(l, v), add(r + 1, -v);  // 将区间加差分为两个前缀加
}

long long getsum1(int l, int r) {
  	return (r + 1ll) * getsum(t1, r) - 1ll * l * getsum(t1, l - 1) -
         (getsum(t2, r) - getsum(t2, l - 1));
}
```