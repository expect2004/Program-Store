#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define LL long long
#define mod 1000000007
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp>void read(Tp &x){
	x=0;int fh=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=fh;
}
int n,m;
int a[6];
int b[maxn][6];
int tans[maxn];

int pnt[maxn];
struct node{
	int id,vl;
	bool operator <(node y)const{
		return vl>y.vl;
	}
	bool operator >(node y)const{
		return vl<y.vl;
	}
};
priority_queue<node>q2;
priority_queue<node,vector<node>,greater<node> >q1;
int ans=inf;
signed main(){
	for(int i=0;i<6;++i)read(a[i]);
	read(n);
	for(int i=1,x;i<=n;++i){
		read(x);
		for(int j=0;j<6;++j){
			b[i][j]=x-a[j];
		}
		sort(b[i],b[i]+6);
		pnt[i]=0;tans[i]=b[i][0];
		for(int j=0;j<6;++j){
			q2.push((node){i,b[i][j]});
		}
		q1.push((node){i,b[i][0]});
	}
	while(!q2.empty()){
		node x=q2.top();q2.pop();
		while(b[q1.top().id][pnt[q1.top().id]]!=q1.top().vl)q1.pop();
		if(!q1.empty())ans=min(ans,q1.top().vl-x.vl);
		pnt[x.id]++;
		if(pnt[x.id]>=6)break;
		q1.push((node){x.id,b[x.id][pnt[x.id]]});
	}
	printf("%d\n",ans);
	return 0;
}
