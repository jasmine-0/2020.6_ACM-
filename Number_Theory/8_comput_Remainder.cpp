/*
	题目：给出正整数 n 和 k ，计算G(n,k)= ∑ ​k mod i (i=1~n)
	
	思路：a%b 可以表示为 a−b∗⌊a/b⌋，所以
		ans = ∑ ​k−i∗⌊i/k​⌋ = n∗k− ∑ ​i∗⌊i/k​⌋ (i=1~n)
*/

#include<cstdio>
#include<algorithm>

using namespace std;
typedef long long ll;

int main() {
    ll n,k;
    scanf("%lld%lld",&n,&k);
    ll ans=n*k;
    
    for(ll l=1,r;l<=n;l=r+1) {
        if(k/l!=0) r=min(k/(k/l),n); 
        else r=n;
        ans-=(k/l)*(r-l+1)*(l+r)/2;
    }
    printf("%lld",ans);
    return 0;
}