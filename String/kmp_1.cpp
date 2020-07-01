/*
	题目： 给定字符串S，求出S的所有可能相同前后缀的长度。比如： 
		"alala"的前缀分别为{"a", "al", "ala", "alal", "alala"}, 后缀分别为{"a", "la", "ala", "lala", "alala"}. 
		其中有{"a", "ala", "alala"}是相同的，即输入1,3,5.
		
	思路：求kmp算法的next数组,对next数组的理解。 
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int INF    = 0x3f3f3f3f;
const int MAX_N  = 4e5 + 10;
const int MOD    = 1000000007;
const double PI  = acos(-1.0);
const double EPS = 1e-10;

int next_[MAX_N],ans[MAX_N];
char str[MAX_N];
int n;

void getnext(const char P[],int next[])
{
    int m=strlen(P);
    int i=0;
    int j=-1; next[0]=-1;
    while(i<m)
    {
        while(j!=-1 && P[i]!=P[j]) j=next[j];
        next[++i]=++j;
    }
}

int main()
{
    while(scanf("%s",str)!=EOF)
    {
        memset(next_,0,sizeof(next_));
        n=strlen(str);
        getnext(str,next_);
        int cnt=0;
        int j=next_[n];
        while(j>0)
        {
            ans[++cnt]=j;
            j=next_[j];
        }
        for(int i=cnt;i>0;i--)
            printf("%d ",ans[i]);
        printf("%d\n",n);
    }

    return 0;
}