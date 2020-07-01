/*
	题目：输入两个正整数 x0,y0，求出满足下列条件的 P,Q 的个数：
		P,Q 是正整数。
		要求 P,Q 以 x0 为最大公约数，以 y0 为最小公倍数。
		试求：满足条件的所有可能的 P,Q 的个数。
	
	思路：最大公因数模板

*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int INF    = 0x3f3f3f3f;
const int MAX_N  = 1e8 + 5;
const int MOD    = 1000000007;
const double PI  = acos(-1.0);
const double EPS = 1e-10;

int x,y;
int ans=0,n,m;

int gcd(int x,int y)
{
    if(y==0) return x;
    return gcd(y,x%y);
}

int main(void)
{ 
    cin>>n>>m;
    for(int i=1;(i*i)<(m*n);i++)
    {
        if((n*m)%i==0 && gcd(i,(n*m)/i)==n)
            ans++;
    }
    if(n==m) printf("%d\n",(ans*2+1));
    else printf("%d\n",ans*2);

    return 0;
}
