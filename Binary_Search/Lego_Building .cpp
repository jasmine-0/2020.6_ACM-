/*
	题目：有1~n等级的蚂蚁，两种操作，p，把a等级蚂蚁数目改成b。q，问排名第x的蚂蚁是属于第几个等级
	
	思路：线段树，线段树单点更新
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;
typedef long long ll;

const int maxn = 100000 + 5;

int room[maxn];
int tot[maxn*4];

void build(int o,int l,int r)
{
    if(l==r){ tot[o]=room[l]; return;}
    int mid=(l+r)>>1;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    tot[o]=tot[o<<1]+tot[o<<1|1];
}

void update(int o,int l,int r,int a,int b)
{
    if(l==r && l==a){ tot[o]=b; return;}
    int mid=(l+r)>>1;
    if(a<=mid) update(o<<1,l,mid,a,b);
    else update(o<<1|1,mid+1,r,a,b);
    tot[o]=tot[o<<1]+tot[o<<1|1];
}

int query(int o,int l,int r,int a)
{
    if(l==r) return l;
    int mid=(l+r)>>1;
    if(a>tot[o<<1]) return query(o<<1|1,mid+1,r,a-tot[o<<1]);
    else return query(o<<1,l,mid,a);
}

int main(void)
{
    int floor=0;
    int qur;
    int ans=0;
    while(scanf("%d",&floor)!=EOF)
    {
        char op;
        int a,b;
        for(int i=1;i<=floor;i++) scanf("%d",&room[i]);
        
        build(1,1,floor);
        scanf("%d\n",&qur);
        while(qur--)
        {
            scanf(" %c",&op);
            if(op=='q') 
            {
                ans=0;
                scanf("%d",&a);
                ans=query(1,1,floor,a);
                printf("%d\n",ans);
            }
            else if(op=='p')
            {
                scanf("%d%d",&a,&b);
                update(1,1,floor,a,b);
            }

        }
    }
    
    return 0;
}
