/*
	题目：如题，已知一个数列，你需要进行下面两种操作：
		将某区间每一个数数加上 x；
		求出某一个数的值。

	思路：树状数组模板
*/

#include<iostream>
#include<cstdio>

typedef long long ll
using namespace std;

ll n,q,mod,x,y,s,inn[500001],tree[500001];
ll lowbit(ll num){return num&-num;}

void add(ll s,ll num){
	for(ll i=s;i<=n;i+=lowbit(i)) tree[i]+=num;
}

ll ask(ll s){
	ll ans=0;
	for(ll i=s;i>=1;i-=lowbit(i)) ans+=tree[i];
	return ans;
}

int main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++) 
		scanf("%lld",&inn[i]);
	for(int i=1;i<=q;i++){
		scanf("%lld",&mod);
		if(mod==1){
			scanf("%lld%lld%lld",&x,&y,&s);
			add(x,s);
			add(y+1,-s);
		}
		if(mod==2){
			scanf("%lld",&x);
			printf("%lld\n",inn[x]+ask(x));
		}
	}
}