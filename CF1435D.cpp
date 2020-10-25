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
int typ[maxn],a[maxn];
char str[10];
priority_queue<int,vector<int>,greater<int> >q;
int ans[maxn];
signed main(){
	read(n);
	for(int i=1;i<=2*n;++i){
		scanf("%s",str);
		if(str[0]=='+')typ[i]=-1;
		else typ[i]=1,read(a[i]);
	}
	for(int i=2*n;i;--i){
		if(typ[i]==1){
			if(q.empty()||q.top()>a[i]){
				q.push(a[i]);
			}
			else{
				puts("NO");
				return 0;
			}
		}
		else{
			if(q.empty()){
				puts("NO");
				return 0;
			}
			ans[i]=q.top();q.pop();
		}
	}
	puts("YES");
	for(int i=1;i<=2*n;++i){
		if(typ[i]==-1)printf("%d ",ans[i]);
	}
	puts("");
	return 0;
}
