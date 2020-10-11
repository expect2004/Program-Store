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

const int maxn = 1000000 + 7;
const int maxm = 2000000 + 7;

int n;
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

int size[maxn], dfn[maxn], ind, dep[maxn], son[maxn], Pre[maxn];

void dfs1(int x, int f, int dp) {
	size[x] = 1, dep[x] = dp, dfn[x] = ++ind, Pre[ind] = x;
	int mx = -1;
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == f) continue;
		dfs1(y, x, dp + 1); size[x] += size[y];
		if(size[y] > mx) son[x] = y, mx = size[y];
	}
}

int curr[maxn], ans[maxn], pos[maxn];
void Add(int x, int opt) {
	int L1, L2, R1, R2;
	L1 = dfn[x], R2 = dfn[x] + size[x] - 1;
	if(son[x] && opt == 1) R1 = dfn[son[x]] - 1, L2 = dfn[son[x]] + size[son[x]];
	else R1 = R2, L2 = 1, R2 = 0;
	for(int i = L1; i <= R1; i++) {
		curr[dep[Pre[i]]] += opt;
		if(opt == 1) {
			if(curr[dep[Pre[i]]] > ans[x]) ans[x] = curr[dep[Pre[i]]], pos[x] = dep[Pre[i]];
			else if(curr[dep[Pre[i]]] == ans[x]) pos[x] = min(pos[x], dep[Pre[i]]);
		}
	}
	for(int i = L2; i <= R2; i++) {
		curr[dep[Pre[i]]] += opt;
		if(opt == 1) {
			if(curr[dep[Pre[i]]] > ans[x]) ans[x] = curr[dep[Pre[i]]], pos[x] = dep[Pre[i]];
			else if(curr[dep[Pre[i]]] == ans[x]) pos[x] = min(pos[x], dep[Pre[i]]);
		}
	}
}

void dfs2(int x, int f, bool op) {
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == f || y == son[x]) continue;
		dfs2(y, x, false);
	}
	if(son[x]) dfs2(son[x], x, true);
	ans[x] = ans[son[x]], pos[x] = pos[son[x]];
	Add(x, 1);
	if(op == false) Add(x, -1);
}

void Work(void) {
	dfs1(1, 0, 1);
	dfs2(1, 0, true);
	for(int i = 1; i <= n; i++) {
		printf("%d\n", pos[i] - dep[i]);
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}

