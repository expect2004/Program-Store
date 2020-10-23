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

const int maxn = 100000 + 7;
const int maxm = 200000 + 7;
const int maxk = 1000000 + 7;

int n, k, s[maxk];
int Head[maxn], to[maxm], Next[maxm], w[maxm], tot = 1;
int up[maxn], down[maxn];

void addedge(int x, int y, int z) {
	to[++tot] = y, Next[tot] = Head[x], Head[x] = tot, w[tot] = z;
}
void add(int x, int y, int z) {
	addedge(x, y, z); addedge(y, x, 0);
}

const int mod = 1000000007;

int size[maxn], dep[maxn], top[maxn], fa[maxn];
int son[maxn];

inline void Init(void) {
	read(n);
	for(int i = 1, x, y, z; i < n; i++) {
		read(x); read(y); read(z);
		add(y, x, z);
	}
	read(k);
	for(int i = 1; i <= k; i++) read(s[i]);
}

void dfs1(int x, int f, int dp) {
	size[x] = 1, fa[x] = f, dep[x] = dp;
	int mx = -1;
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == f) continue;
		dfs1(y, x, dp + 1);
		size[x] += size[y];
		if(size[y] > mx) mx = size[y], son[x] = y;
	}
}

void dfs2(int x, int tp) {
	top[x] = tp;
	if(!son[x]) return ;
	dfs2(son[x], tp);
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == fa[x] || y == son[x]) continue;
		dfs2(y, y);
	}
}

inline int LCA(int x, int y) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	return x;
}

int ans;

int fpow(long long x, int p) {
	long long res = 1ll;
	while(p) {
		if(p & 1) res = res * x % mod; p >>= 1;
		x = x * x % mod;
	}
	return res;
}

void dfs3(int x, int &d, int &u) {
//	int d = 0, u = 0;
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == fa[x]) continue;
		int p = 0, q = 0;
		dfs3(y, p, q);
		if(w[i]) ans = ((ans + fpow(2, p) - 1) % mod + mod) % mod;
		if(w[i ^ 1]) ans = ((ans + fpow(2, q) - 1) % mod + mod) % mod;
		d += p, u += q;
	}
	d += down[x], u += up[x];
}

inline void Work(void) {
	dfs1(1, 0, 1);
	dfs2(1, 1);
	s[0] = 1;
	for(int i = 0, x, y; i < k; i++) {
		x = s[i], y = s[i + 1];
		int lca = LCA(x, y);
		up[x]++, up[lca]--;
		down[y]++, down[lca]--;
	}
	int p = 0, q = 0;
	dfs3(1, p, q);
	printf("%d\n", ans);
}

signed main(void) {
	Init();
	Work();
	return 0;
}
