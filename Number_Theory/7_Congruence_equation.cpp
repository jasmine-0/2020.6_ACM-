/*
	题目：求关于x的同余方程 ax≡1(modb) 的最小正整数解
	
	思路：线性同余方程模板
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

// ax+by=1 => ax+by=m

ll x,y;

void exgcd(int a,int b)
{
    if(b==0)
    {
        x=1; y=0;
        return;
    }
    exgcd(b,a%b);
    ll temp=x;
    x=y;
    y=temp-(a/b)*y;  
}

int main(void)
{ 
    ll a,b;
    scanf("%d%d",&a,&b);
    exgcd(a,b);
    x=(x%b+b)%b;
    printf("%lld\n",x);

    return 0;
}
