/*
	题目：给你三个正整数，a,m,b，求：a^b mod m
		数据范围：1≤a≤1e9，1≤b≤1e20000000，1≤m≤1e8
	
	思路：扩展欧拉定理模板
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

inline int read(int mod) // 快读板子
{
    int s=0,w=1,flag=0; char c=getchar();
    while (c<'0'||c>'9') if (c=='-') w=-1; else c=getchar();
    while (c>='0' && c<='9')
    {
        s=((s<<3)+(s<<1)+(c-'0'));
        if(s>=mod){ s%=mod; flag=1;}
        c=getchar();
    }
    if(flag) s+=mod;
    return s;
}

long long q_pow(ll a,ll b,ll mod) // 快速幂
{
    ll x=a,ans=1;
    while(b)
    {
        if(b&1) ans=ans*x % mod;
        x=x*x % mod;
        b>>=1;
    }
    return ans;
}

int main(void)
{ 
    int a,b,m;
    cin>>a>>m;
    int temp=m,phi=m;
    for(int i=2;i<=m;i++)
    {
        if(temp % i==0)
        {
            phi=phi/i*(i-1);
            while(temp%i==0)
                temp/=i;
        }
    }
    if(temp>1) phi=phi-phi/temp;
    b=read(phi);
    cout<<q_pow(a,b,m);

    return 0;
}
