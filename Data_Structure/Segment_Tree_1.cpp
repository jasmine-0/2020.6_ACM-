/*
	题目：如题，已知一个数列，你需要进行下面两种操作：
		将某一个数加上 xxx
		求出某区间每一个数的和

	思路：线段树模板
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll ;
 
const int N = 1e5+5;
 
int n, a[N], m, P;
struct node{
    int l, r;
    ll add, mul, sum;
    void update(int Mul, int Add)
    {
        sum = (1ll*sum*Mul + Add*1ll*(r-l+1))%P;
        add = (add*Mul + Add) % P;
        mul = (mul * Mul) % P;
    }
}tree[N<<2];
 
void push_up(int x)
{
    tree[x].sum = (tree[x<<1].sum + tree[x<<1|1].sum) % P;
}
 
void push_down(int x)
{
    int Mul = tree[x].mul;
    int Add = tree[x].add;
 
    if(Mul!=1 || Add!=0){
        tree[x<<1].update(Mul,Add);
        tree[x<<1|1].update(Mul,Add);
        tree[x].add = 0, tree[x].mul = 1;
    }
}
 
void build(int x,int l, int r)
{
    tree[x].l = l, tree[x].r = r;
    tree[x].add = tree[x].sum = 0,tree[x].mul = 1;
    if(l == r){
        tree[x].sum = a[l];
    }else{
        int mid = l+r >> 1;
        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);
        push_up(x);
    }
}
 
void update(int x, int l, int r, ll val,int fg)
{
    int L = tree[x].l, R = tree[x].r;
    if(l<=L && R<=r){
        if(fg==1) tree[x].update(val,0);
        else tree[x].update(1,val);
    }else{
        push_down(x);
        int mid = (L+R)/2;
        if(mid>= l) update(x<<1,l,r,val,fg);
        if(r > mid) update(x<<1|1,l,r,val,fg);
        push_up(x);
    }
}
 
ll query(int x, int l, int r)
{
    int L = tree[x].l, R = tree[x].r;
    if(l<=L && R<=r){
        return tree[x].sum%P;
    }else{
        push_down(x);
        ll Ans = 0;
        int mid = (L+R)/2;
        if(mid>= l) Ans = (Ans + query(x<<1,l,r)) % P;
        if(r > mid) Ans = (Ans + query(x<<1|1,l,r)) % P;
        push_up(x);
        return Ans;
    }
}
 
int main()
{
    scanf("%d%d%d",&n,&m,&P);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int op, l, r;
        scanf("%d%d%d",&op,&l,&r);
        if(op != 3){
            ll val; scanf("%lld",&val);
            update(1,l,r,val,op);
        }
        else printf("%lld\n",query(1,l,r));
    }
 
    return 0;
}