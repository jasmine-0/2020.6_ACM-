/*
	题目描述:
		John的农场在给奶牛挤奶前有很多杂务要完成，每一项杂务都需要一定的时间来完成它。
		比如：他们要将奶牛集合起来，将他们赶进牛棚，为奶牛清洗乳房以及一些其它工作。
		尽早将所有杂务完成是必要的，因为这样才有更多时间挤出更多的牛奶。当然，有些杂务必须在另一些杂务完成的情况下才能进行。
		比如：只有将奶牛赶进牛棚才能开始为它清洗乳房，还有在未给奶牛清洗乳房之前不能挤奶。我们把这些工作称为完成本项工作的准备工作。
		至少有一项杂务不要求有准备工作，这个可以最早着手完成的工作，标记为杂务1。
		John有需要完成的n个杂务的清单，并且这份清单是有一定顺序的，杂务k(k>1)的准备工作只可能在杂务1至k−1中。
		写一个程序从1到n读入每个杂务的工作说明。计算出所有杂务都被完成的最短时间。当然互相没有关系的杂务可以同时工作，
		并且，你可以假定John的农场有足够多的工人来同时完成任意多项任务。
	
	思路：因为任务可以并发，所以一个任务如果有前驱的话，最优方案便是在它的最晚一个前驱结束后就立即开始，
		而且任务k的前驱节点一定小于k，所以读入时顺便从它的前驱里挑一个最大的转移即可。同时可以更新最终答案。
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int INF    = 0x3f3f3f3f;
const long long MAX_N  = 1e5 + 10;
const int MOD    = 1000000007;
const double PI  = acos(-1.0);
const double EPS = 1e-10;

int n,t,k,ans=0;
int fei[10005];

int main(void)
{
    scanf("%d",&n);
    memset(fei,0,sizeof(fei));
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&k,&t);
        while(scanf("%d",&k) && k)
        {
            fei[i]=max(fei[k],fei[i]);
        }
        fei[i]+=t;
        ans=max(ans,fei[i]);
    }
    printf("%d\n",ans);
    
    return 0;
}
