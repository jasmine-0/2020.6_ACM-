/*
	题目描述:
		给出B地区的村庄数N，村庄编号从0到N−1，和所有M条公路的长度，公路是双向的。
		并给出第i个村庄重建完成的时间ti，你可以认为是同时开始重建并在第ti天重建完成，并且在当天即可通车。
		若ti为0则说明地震未对此地区造成损坏，一开始就可以通车。之后有Q个询问(x,y,t)，对于每个询问你要回答在第ttt天，
		从村庄x到村庄y的最短路径长度为多少。如果无法找到从x村庄到y村庄的路径，经过若干个已重建完成的村庄，
		或者村庄x或村庄y在第t天仍未重建完成 ，则需要返回−1。
	
	思路：最短路径，生成树
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int INF    = 0x3f3f3f3f;
const long long MAX_N  = 1e5 + 10;
const int MOD    = 1000000007;
const double PI  = acos(-1.0);
const double EPS = 1e-10;

int _cost[205];
int fei[205][205];
int n,m,n1,n2,s,q;

void up_data(int k)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(fei[i][j] > fei[i][k]+fei[k][j])
                fei[i][j] = fei[j][i] = fei[i][k]+fei[k][j];
    return;
}

int main(void)
{ 
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
        scanf("%d",&_cost[i]);
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) fei[i][j]=0;
            else fei[i][j]=1e9;
        }
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&n1,&n2,&s);
        fei[n1][n2]=fei[n2][n1]=s;
    }
    scanf("%d",&q);
    int now=0;
    while(q--)
    {
        scanf("%d%d%d",&n1,&n2,&s);
        while(_cost[now]<=s && now<n)
        {
            up_data(now);
            now++;
        }
        if(_cost[n1]>s || _cost[n2]>s) printf("-1\n");
        else{
            if(fei[n1][n2]==1e9) printf("-1\n");
            else printf("%d\n",fei[n1][n2]);
        }
    }
    
    return 0;
}
