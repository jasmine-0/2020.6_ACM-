/*
	题目：有 n 个人按顺序排列，升高分别为 h[1],h[2]... 现在挑选出一些人，排成的队列满足：
		1、挑出的人保持原队形的相对顺序不变，且必须都是在原队形中连续的；
　　	2、左右对称，假设有m个人形成新的队形，则第1个人和第m个人身高相同，第2个人和第m-1个人身高相同，依此类推，当然如果m是奇数，中间那个人可以任意；
　　	3、从左到中间那个人，身高需保证不下降，如果用H表示新队形的高度，则H[1] <= H[2] <= H[3] .... <= H[mid]。

	思路：马拉车模板
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int INF    = 0x3f3f3f3f;
const int MAX_N  = 2e5 + 10;
const int MOD    = 1000000007;
const double PI  = acos(-1.0);
const double EPS = 1e-10;



int str[MAX_N];
int newStr[MAX_N<<1];
int p[MAX_N<<1];
int n;

int manacher()
{
    newStr[0]=-1;
    newStr[1]=0;

    int len=2;
    for(int i=0;i<n;i++)
    {
        newStr[len++]=str[i]; newStr[len++]=0;
    }
    
    int id=0,mx=0,ans=0;
    for(int i=1;i<len;i++)
    {
        int j=2*id-i;
        if(i<mx) p[i]=min(p[j],mx-i);
        else p[i]=1;

        while(newStr[i-p[i]]==newStr[i+p[i]] && newStr[i-p[i]]<=newStr[i-p[i]+2])
            p[i]++;
        if(mx<i+p[i])
        {
            id=i;
            mx=i+p[i];
        }
        ans=max(ans,p[i]-1);
    }
    return ans;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++) scanf("%d",&str[i]);
        printf("%d\n",manacher());
    }

    return 0;
}