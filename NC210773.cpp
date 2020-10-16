#include<bits/stdc++.h>
using namespace std;

template < typename Tp >
inline void read(Tp &x) {
	x = 0; int fh = 1; char ch = 1;
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= fh;
}

template < typename Tp >
inline void biread(Tp &x) {
	x = 0; int fh = 1; char ch = 1;
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 2 + ch - '0', ch = getchar();
	x *= fh;
}
int n;
inline void Init(void) {
	read(n);
}
#define maxn 1005
int a[maxn][maxn];

inline void Work(void) {
	--n;
	int ans=n*n+2*n-1;
	ans>>=1;
	++n;
	cout<<ans<<endl;
	if(n%2==0){
		int tot=n*n+1;
		for(int i=1;i<=n;++i)a[i][1]=--tot;
		for(int i=(n>>1);i;--i){
			int t1=(i<<1),t2=t1-1;
			for(int j=2;j<=n;++j)a[t1][j]=--tot;
			for(int j=n;j>=2;--j)a[t2][j]=--tot;
		}
	}
	else{
		int tot=n*n+1;
		for(int i=1;i<=n;++i)a[i][1]=--tot;
		for(int i=n;i>3;i-=2){
			int t1=i,t2=i-1;
			for(int j=2;j<=n;++j)a[t1][j]=--tot;
			for(int j=n;j>=2;--j)a[t2][j]=--tot;
		}
		for(int j=2;j<=n;++j)a[3][j]=--tot;
		for(int j=n;j>1;j-=2){
			a[2][j]=--tot;
			a[1][j]=--tot;
			a[1][j-1]=--tot;
			a[2][j-1]=--tot;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			printf("%d%c",a[i][j]," \n"[j==n]);
		}
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}

