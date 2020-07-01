/*
	问题：C君负责这次运动会仪仗队的训练。仪仗队是由学生组成的 N * N 的方阵，
		为了保证队伍在行进中整齐划一，C君会跟在仪仗队的左后方，
		每个学生站在由 N * N 方正划分的方格点上排列整齐，问C君能看到的学生人数

	思路：用总人数减去看不到的人数就是看得到的人数，
		当一个点的横坐标和纵坐标的 GCD 大于 1 时就会被遮挡
		欧拉函数求 phi 模板
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int n,phi[40005];
ll ans;

void eular()
{
    phi[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!phi[i])
        {
            for(int j=i;j<=n;j+=i)
            {
                if(!phi[j]) phi[j]=j;
                phi[j]=phi[j]/i*(i-1);
            }
        }
    }
}

int main(void)
{ 
    scanf("%d",&n); eular();
    
	if(n==1) { printf("0\n"); return 0;} // 特殊情况单独考虑
    
	for(int i=2;i<=n-1;i++) 
		ans+=(long long)phi[i];
	
    printf("%lld\n",(ans*2+3));

    return 0;
}
