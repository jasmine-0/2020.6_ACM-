/*
	题目：有一种神奇的自动刷题机，刷题的方式非常简单：首先会瞬间得出题目的正确做法，然后开始写程序。
		每秒，自动刷题机的代码生成模块会有两种可能的结果：
			1.写了x行代码。
			2.心情不好，删掉了之前写的y行代码（如果y大于当前代码长度则相当于全部删除）。
		对于一个 OJ，存在某个固定的长度n>0，一旦自动刷题机在某秒结束时积累了大于等于n行的代码，
		它就会自动提交并 AC 此题，然后新建一个文件（即弃置之前的所有代码）并开始写下一题。
		
		已知某天切题 k 道，计算 n 的可能的最大值和最小值。
		
	思路：用两次二分来完成这道题，一次求最小值，一次求最大值。
*/

#include<bits/stdc++.h>

using namespace std;

long long l,k,c[100010];

long long check(long long x) {
	long long w=0,s=0;
	for(int i=1;i<=l;i++) {
		w+=c[i];
		if(w>=x) {
			s++;
			w=0;
		}
		if(w<0) w=0;
	}
	return s;
}
	
int main() {
	cin>>l>>k;
	long long maxn=0;
	for(int i=1;i<=l;i++) {
		cin>>c[i];
		if(c[i]>0) maxn+=c[i];
	}
	
	long long l=1,r=maxn,ans=-1;
	while(l<=r) {
		long long mid=l+r>>1;
		long long s=check(mid);
		if(s>k) l=mid+1;
		if(s==k) ans=mid;
		if(s<=k) r=mid-1;
			
	}
	cout<<ans<<" ";
	if(ans==-1) return 0;
	
	l=1,r=maxn,ans=-1;
	while(l<=r) {
		long long mid=l+r>>1;
		long long s=check(mid);
		if(s>=k) l=mid+1;
		if(s==k) ans=mid;
		if(s<k) r=mid-1;
			
	}
	cout<<ans<<endl;
	
	return 0;
}