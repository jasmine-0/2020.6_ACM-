/*
	题目：有 n 组数据，每一组数据读入一个分数的分子 p、分母 q 和进制 b（分子、分母均以十进制读入）
		求在 b 进制下 p/q 是否为有限小数。如果是，输出 Finite，否则输出 Infinite
	
	思路：其实可以先忽略分子，如果进制的质因数（忽略指数）中包括分母的所有质因数（同样忽略指数），
		就说明这个分数能化为有限小数。否则就不是有限小数（就是循环小数）。
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

ll gcd(ll x,ll y)
{
    if(y==0) return x;
    return gcd(y,x%y);
}

int main(void)
{ 
    int cases;
    ll p,q,b;
    scanf("%d",&cases);
    while(cases--)
    {
        scanf("%lld%lld%lld",&p,&q,&b);
        if(p==0) { printf("Finite\n"); continue; }
        ll g=gcd(p,q); q/=g;
        g=gcd(q,b);
        while(g!=1)
        {
            while(q%g==0) q/=g;
            g=gcd(q,b);
        }
        if(q==1) printf("Finite\n");
        else printf("Infinite\n");
    }    

    return 0;
}
