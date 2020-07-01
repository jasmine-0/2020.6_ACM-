/*
	题目：对于给定的一个长度为 N 的正整数数列 A ，现要将其分成 M 段，并要求每段连续，且每段和的最大值最小。
	
	思路：用贪心和二分的思想
	
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

int a[100005];

int main(void)
{
    int m,n;
    int sum=0;
    int ans=0;
    int l=0,r;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        l=max(l,a[i]);
        sum+=a[i];
    }
    r=sum;

    while(l <= r)
    {
        int mid=(l+r)>>1;
        int tot=0;
        int count=1;

        for(int i=1;i<=n;i++)
        {
            if(tot+a[i]<=mid) tot+=a[i];
            else{
                tot=a[i];
                count++;
            }
        }
        if(count>m) l=mid+1;
        else {r=mid-1; ans=mid;}
    }
    printf("%d\n",ans);
    
    return 0;
}