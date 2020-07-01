/*
	题目：如题，已知一个数列，你需要进行下面三种操作：
		将某区间每一个数乘上 x
		将某区间每一个数加上 x
		求出某区间每一个数的和

	思路：线段树模板
*/

#include<bits/stdc++.h>

using namespace std;

const int maxx = 1e5+6;
const int INF = 0x7fffffff;

int n,m,p;
int a[maxx];
 
struct node{
    long long sum;
    long long lazyadd,lazymul;
}A[maxx<<2];
 
void build(int u,int l,int r){
    A[u].lazymul=1;A[u].lazyadd=0;
    if(l==r) A[u].sum=a[l];
    else{
        int mid=(l+r)/2;
        build(2*u, l, mid);
        build(2*u+1, mid+1, r);
        A[u].sum=A[2*u].sum+A[2*u+1].sum;
    }
    A[u].sum%=p;
    return ;
}
 
void pushdown(int u, int l, int r){
    int mid=(l+r)/2;

    A[u*2].sum=(A[u*2].sum*A[u].lazymul+A[u].lazyadd*(mid-l+1))%p;
    A[u*2+1].sum=(A[u*2+1].sum*A[u].lazymul+A[u].lazyadd*(r-mid))%p;

    A[u*2].lazymul=(A[u*2].lazymul*A[u].lazymul)%p;
    A[u*2+1].lazymul=(A[u*2+1].lazymul*A[u].lazymul)%p;
    A[u*2].lazyadd=(A[u*2].lazyadd*A[u].lazymul+A[u].lazyadd)%p;
    A[u*2+1].lazyadd=(A[u*2+1].lazyadd*A[u].lazymul+A[u].lazyadd)%p;

    A[u].lazymul=1;
    A[u].lazyadd=0;
    return ;
}
 
 
 
void mul(int u,int sl,int sr,int l,int r,long long k){
    if(l>sr || r<sl) return ;
    if(l<=sl && r>=sr){
        A[u].sum*=k;
        A[u].lazymul*=k;
        A[u].lazyadd*=k;
        A[u].sum%=p;
        A[u].lazymul%=p;
        A[u].lazyadd%=p;;
        return ;
    }
    pushdown(u, sl, sr);
    int mid=(sl+sr)/2;
    mul(2*u, sl, mid, l, r, k);
    mul(2*u+1, mid+1, sr, l, r, k);
    A[u].sum=(A[2*u].sum+A[2*u+1].sum)%p;
    return ;
}
 
void add(int u,int sl,int sr,int l,int r,long long k){
    if(l>sr || r<sl) return ;
    if(l<=sl && r>=sr){
        A[u].sum+=k*(sr-sl+1);
        A[u].lazyadd+=k;
        A[u].sum%=p;
        A[u].lazyadd%=p;
        return ;
    }
    pushdown(u, sl, sr);
    int mid=(sl+sr)/2;
    add(2*u, sl, mid, l, r, k);
    add(2*u+1, mid+1, sr, l, r, k);
    A[u].sum=(A[2*u].sum+A[2*u+1].sum)%p;
    return ;
}
 
long long query(int u,int sl,int sr,int l,int r){
    if(l>sr || r<sl) return 0;
    if(l<=sl && r>=sr) return A[u].sum;
    pushdown(u, sl, sr);
    int mid=(sl+sr)/2;
    return (query(2*u, sl, mid, l, r)+query(2*u+1, mid+1, sr, l, r))%p;
}
 
 
int main (){
    std::ios::sync_with_stdio(false);
    cin>>n>>m>>p;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    while(m--){
        int x,y,z;
        long long k;
        cin>>z;
        if(z==1){
            cin>>x>>y>>k;
            mul(1,1,n,x,y,k);
        }
        else if(z==2){
            cin>>x>>y>>k;
            add(1,1,n,x,y,k);
        }
        else{
            cin>>x>>y;
            cout<<query(1,1,n,x,y)<<endl;
        }
    }
    return 0;
}