LIS

```C++
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
        //最长上升子序列 LIS
        //维护low数组 low[i]表示长度为i的最长上升子序列的最后一个元素的值
        //若a[j]>=low[i](有没有等号 看具体情况) 则可把a[j]接在low[i]之后
        //即low[++i]=a[j]
        //若a[j]<low[i]则在low[1]->low[i]二分搜索第一个大于a[j]的的位置
        //用a[j]替换该位置的值
        //因为对一个上升子序列 若其中一个值越小 则越有利 时间复杂度O(nlgn)
int LOW[100005];//最上上升子序列
int MAX[100005];//最长非升子序列
int a[100005];
 
int main()
{
    int n=0;
    while(~scanf("%d",&a[n]))
        ++n;
    int k1=0,k2=0;
    LOW[0]=a[0];
    MAX[0]=a[0];
    for(int i=1;i<n;i++)
    {
        if(a[i]>LOW[k1])//最长上升子序列
            LOW[++k1]=a[i];
        else if(a[i]<=LOW[k1])
            *lower_bound(LOW,LOW+k1+1,a[i])=a[i];
        if(a[i]<=MAX[k2])//最长非升子序列
            MAX[++k2]=a[i];
        else if(a[i]>MAX[k2])
            *upper_bound(MAX,MAX+k2+1,a[i],greater<int>())=a[i];//默认是升序的 这里要改成降序的
    }
    printf("%d\n%d\n",k2+1,k1+1);
    return 0;
}
```

