#include<bits/stdc++.h>
using namespace std;

#define int long long

template < typename Tp >
void read(Tp &x) {
	x = 0; int fh = 1; char ch = 1;
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= fh;
}

template < typename Tp >
void biread(Tp &x) {
	x = 0; int fh = 1; char ch = 1;
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 2 + ch - '0', ch = getchar();
	x *= fh;
}

const int maxn = 200000 + 7;
const int maxm = 400000 + 7;

int n, dp[maxn], size[maxn];
int Head[maxn], to[maxm], Next[maxm], tot;
void addedge(int x, int y) {
	to[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void add(int x, int y) {
	addedge(x, y); addedge(y, x);
}

void Init(void) {
	read(n);
	for(int i = 1, x, y; i < n; i++) {
		read(x); read(y);
		add(x, y);
	}
}

void dfs(int x, int f) {
	size[x] = 1;
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == f) continue;
		dp[y] = dp[x] + 1;
		dfs(y, x); size[x] += size[y];
	}
}

void Work(void) {
	int ans(0), cnt(0);
	dfs(1, 0);
	for(int i = 1; i <= n; i++) {
		ans += (size[i] * (n - size[i]));
		if(dp[i] & 1) ++cnt;
	}
	ans += (cnt * (n - cnt));
	ans /= 2;
	printf("%lld\n", ans);
}

signed main(void) {
	Init();
	Work();
	return 0;
}
