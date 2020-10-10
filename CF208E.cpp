#include<bits/stdc++.h>
using namespace std;

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

const int maxn = 100000 + 7;
const int maxm = 200000 + 7;

int n, T;
int Head[maxn], to[maxm], Next[maxm], tot;
void addedge(int x, int y) {
	to[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void add(int x, int y) {
	addedge(x, y); addedge(y, x);
}

int fa[maxn][19], ans[maxn];

struct Question {
	int id, dp;
};
vector < Question > q[maxn];

int size[maxn], dep[maxn], son[maxn], dfn[maxn], ind, Pre[maxn];
void dfs1(int x, int f, int dp) {
	size[x] = 1, dep[x] = dp, fa[x][0] = f; int mx = -1;
	dfn[x] = ++ind; Pre[ind] = x;
	for(int i = 1; i <= 17; i++) {
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	}
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == f) continue;
		dfs1(y, x, dp + 1); size[x] += size[y];
		if(size[y] > mx) mx = size[y], son[x] = y;
	}
}

int curr[maxn];

void Add(int x, int opt) {
	int L1, L2, R1, R2;
	L1 = dfn[x], R2 = dfn[x] + size[x] - 1;
	if(son[x] && opt == 1) R1 = dfn[son[x]] - 1, L2 = dfn[son[x]] + size[son[x]];
	else R1 = R2, L2 = 1, R2 = 0;
	for(int i = L1; i <= R1; i++) {
		curr[dep[Pre[i]]] += opt;
	}
	for(int i = L2; i <= R2; i++) {
		curr[dep[Pre[i]]] += opt;
	}
}

void dfs2(int x, bool op) {
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == son[x] || y == fa[x][0]) continue;
		dfs2(y, false);
	}
	if(son[x]) dfs2(son[x], true);
	Add(x, 1);
	for(auto p : q[x]) {
		int id = p.id, dp = p.dp + dep[x];
		if(dp <= n) ans[id] = curr[dp];
	}
	if(!op) Add(x, -1);
}

int Get(int x, int k) {
	int res = x;
	for(int i = 17; i >= 0 && k; i--) {
		if(fa[x][i] == 0) continue;
		if((1 << i) <= k) res = fa[res][i], k -= (1 << i);
	}
	return res;
}

void Init(void) {
	read(n);
	for(int i = 1, x; i <= n; i++) {
		read(x);
		if(x) add(i, x);
		else add(i, n + 1);
	}
	read(T);
	dfs1(n + 1, 0, 0);
	for(int i = 1, x, y; i <= T; i++) {
		read(x); read(y);
		if(dep[x] - y <= 0) {
			ans[i] = 1; continue;
		}
		int ancestor = Get(x, y);
		q[ancestor].push_back((Question){i, y});
	}
}

void Work(void) {
	dfs2(n + 1, true);
	for(int i = 1; i <= T; i++) printf("%d%c", ans[i] - 1, " \n"[i == T]);
}

signed main(void) {
	Init();
	Work();
	return 0;
}

