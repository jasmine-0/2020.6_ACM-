/*
	题目：找出字符中最长回文串，以END结束；
	
	思路：Manacher算法模板
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000000 + 5;

char s[maxn<<1];
char schange[maxn<<1];
int ans=0;
int p[maxn<<1];

void manacher()
{
    int len=strlen(s);
    schange[0]='$';
    for(int i=0;i<len;i++)
    {
        schange[i*2 + 1]='#';
        schange[i*2 + 2]=s[i];
    }
    schange[len*2 + 1]='#';
    schange[len*2 + 2]='\0';
    int k=strlen(schange);
    int m=0,id=0;
    for(int i=0;i<= maxn<<1;i++) p[i]=1;
    for(int i=1;i<k;i++)
    {
        if(m>i) p[i]=min(p[2*id-i],m-i);
        else p[i]=1;
        while(schange[i-p[i]]==schange[i+p[i]]) p[i]++;
        if(p[i]+i>m)
        {
            m=p[i]+i;
            id=i;
        }
        // printf("%d******\n",ans);
        ans=max(ans,p[i]-1);
    }
}

int main(void)
{
    int cases=1;
    while(~scanf("%s",s))
    {
        if(s[0]=='E') return 0;
        ans=0;
        manacher();
        printf("Case %d: %d\n",cases++,ans);
    }
    
    return 0;
}