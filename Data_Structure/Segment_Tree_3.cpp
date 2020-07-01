/*
	题目：第一行包含两个正整数N、M，分别表示数列中实数的个数和操作的个数。
		第二行包含N个实数，其中第i个实数表示数列的第i项。
		接下来M行，每行为一条操作，格式为以下两种之一：
			操作1：1 x y k ，表示将第x到第y项每项加上k，k为一实数。
			操作2：2 x y ，表示求出第x到第y项这一子数列的平均数。
			操作3：3 x y ，表示求出第x到第y项这一子数列的方差。
	
	思路：线段树改版
*/

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAX_N  = 1e5 + 10;

int n,m;
double a[MAX_N];

struct node
{
    double sum, squ, tot;
}t[MAX_N << 2];

void build(int o,int l,int r)
{
    if(l==r){
        t[o].sum=a[l];
        t[o].squ=a[l]*a[l];
    }else{
        int mid=(l+r)>>1;
        build(o << 1, l, mid);
        build(o << 1|1, mid + 1, r);
        t[o].sum = t[o<<1].sum + t[o<<1|1].sum;
        t[o].squ = t[o<<1].squ + t[o<<1|1].squ;
    }
}

inline void down(int o,int len)
{
    if(!t[o].tot) return;
    t[o<<1].squ += 2*t[o].tot*t[o<<1].sum + t[o].tot*t[o].tot*(len-(len>>1));
    t[o<<1|1].squ += 2*t[o].tot*t[o<<1|1].sum + t[o].tot*t[o].tot*(len>>1);
    
    t[o<<1].sum += t[o].tot*(len-(len>>1));
    t[o<<1|1].sum += t[o].tot*(len>>1);
    t[o<<1].tot+=t[o].tot;
    t[o<<1|1].tot+=t[o].tot;
    t[o].tot=0;
}

void updata(int o,int l,int r,int q_l,int q_r,double v)
{
    if(q_l<=l && q_r>=r){
        t[o].squ+= 2*v*t[o].sum + v*v*(r-l+1);
        t[o].sum+= v*(r-l+1);
        t[o].tot+=v;
    }else{
        down(o,r-l+1);
        int mid=(l+r)>>1;
        if(q_l<=mid)updata(o<<1,l,mid,q_l,q_r,v);
        if(q_r>mid) updata(o<<1|1,mid+1,r,q_l,q_r,v);
        
        t[o].sum=t[o<<1].sum+t[o<<1|1].sum;
        t[o].squ=t[o<<1].squ+t[o<<1|1].squ;
    }
}

double ssum,ssqu;
void Query(int o,int l,int r,int q_l,int q_r)
{
    if(q_l<=l && r<=q_r){
        ssum+=t[o].sum;
        ssqu+=t[o].squ;
    }else{
        down(o,r-l+1);
        int mid=(l+r)>>1;
        if(q_l<=mid) Query(o<<1,l,mid,q_l,q_r);
        if(q_r>mid)  Query(o<<1|1,mid+1,r,q_l,q_r);
    }
}

inline double averag(int l,int r)
{
    ssum=ssqu=0.0;
    Query(1,1,n,l,r);
    return ssum*1.0/(r-l+1);
}

inline double s2(int l,int r)
{
    int num=r-l+1;
    ssum=ssqu=0;
    Query(1,1,n,l,r);
    double ave = ssum*1.0/num;
    double res = ssqu - 2*ave*ssum + num*ave*ave;
    return res/num;
}

int main(void)
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lf",&a[i]);
    build(1,1,n);
    while(m--)
    {
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if(op==2) printf("%.4lf\n",averag(x,y));
        else if(op==3) printf("%.4lf\n",s2(x,y));
        else{
            double k;
            scanf("%lf",&k);
            updata(1,1,n,x,y,k);
        }
    }

    return 0;
}