/*
	题目：给出一个有理数 c = a/b 求 c mod 19260817 的值
	
	思路：问题转化为：bx ≡ a (mod p)，求 x。
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int mod = 19260817;

inline long long read()
{
    char ch=getchar();
    long long op=1,x=0;
    while(ch>'9' || ch<'0') {if(ch=='-') op=-1; ch=getchar();}
    while(ch>='0' && ch<='9') {x= ((x*10)%mod) + (ch-'0')%mod; ch = getchar();}
    return x%mod *op;
}

long long a,b;

inline long long q_pow(ll x,ll y)
{
    ll ans=1;
    while(y)
    {
        if(y&1) ans=ans*x % mod;
        x=x*x % mod;
        y>>=1;
    }
    return ans % mod;
}

int main(void)
{ 
    a=read(); b=read();
    if(b==0) {printf("Angry!\n"); return 0;}
    ll cnt = (a * q_pow(b,mod-2)) % mod;
    printf("%lld\n",(cnt+mod)%mod);

    return 0;
}
