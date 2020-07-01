/*
	题目：给定 n,p 求 1∼n 中所有整数在模 p 意义下的乘法逆元。
	思路：乘法逆元模板
*/

#include <cstdio>

int n,p,inv[20000529];

int main(){
	
    scanf("%d%d",&n,&p);
	
    puts("1");
    
	inv[1]=1;
    
	for(int i=2;i<=n;++i)
		printf("%d\n",inv[i]=(long long)(p-p/i)*inv[p%i]%p);
    
	return 0;
}