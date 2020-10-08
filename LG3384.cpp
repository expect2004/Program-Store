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

int n, T, root, mod, a[maxn];
int Head[maxn], to[maxm], Next[maxm], tot;
void addedge(int x, int y) {
	to[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void add(int x, int y) {
	addedge(x, y); addedge(y, x);
}

int son[maxn], dep[maxn], fa[maxn], size[maxn];
void dfs1(int x, int f) {
	size[x] = 1, fa[x] = f; int mx = -1;
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == f) continue;
		dep[y] = dep[x] + 1;
		dfs1(y, x); size[x] += size[y];
		if(size[y] > mx) mx = size[y], son[x] = y;
	}
}

int top[maxn], New[maxn], Pre[maxn], ind;
void dfs2(int x, int tp) {
	top[x] = tp, New[x] = ++ind; Pre[ind] = x;
	if(son[x] == 0) return ;
	dfs2(son[x], tp);
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == fa[x] || y == son[x]) continue;
		dfs2(y, y);
	}
}

#define lfc (x << 1)
#define rgc ((x << 1) | 1)
#define mid ((l + r) >> 1)

int val[maxn << 2], tag[maxn << 2], L, R, need;
void build(int x, int l, int r) {
	if(l == r) {
		val[x] = a[Pre[l]] % mod;
		return ;
	}
	build(lfc, l, mid); build(rgc, mid + 1, r);
	val[x] = (val[lfc] + val[rgc]) % mod;
}
void pushdown(int x, int l, int r) {
	if(tag[x] == 0) return ;
	tag[lfc] = (tag[lfc] + tag[x]) % mod, tag[rgc] = (tag[rgc] + tag[x]) % mod;
	val[lfc] = (val[lfc] + (mid - l + 1) * tag[x] % mod) % mod;
	val[rgc] = (val[rgc] + (r - mid) * tag[x] % mod) % mod;
	tag[x] = 0;
}
void modify(int x, int l, int r) {
	if(L <= l && r <= R) {
		tag[x] = (tag[x] + need) % mod;
		val[x] = (val[x] + (r - l + 1) * need % mod) % mod;
		return ;
	}
	if(R < l || r < L) return ;
	pushdown(x, l, r);
	modify(lfc, l, mid); modify(rgc, mid + 1, r);
	val[x] = (val[lfc] + val[rgc]) % mod;
}
int query(int x, int l, int r) {
	if(L <= l && r <= R) return val[x];
	if(R < l || r < L) return 0;
	pushdown(x, l, r);
	return (query(lfc, l, mid) + query(rgc, mid + 1, r)) % mod;
}

#undef lfc
#undef rgc
#undef mid

void Init(void) {
	read(n); read(T); read(root); read(mod);
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 1, x, y; i < n; i++) {
		read(x); read(y);
		add(x, y);
	}
}

void op1(void) {
	int x, y; read(x); read(y); read(need);
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		R = New[x], L = New[top[x]];
		x = fa[top[x]];
		modify(1, 1, n);
	}
	if(dep[x] > dep[y]) swap(x, y);
	L = New[x], R = New[y];
	modify(1, 1, n);
}

void op2(void) {
	int x, y, ans(0); read(x); read(y);
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		R = New[x], L = New[top[x]];
		x = fa[top[x]];
		ans = (ans + query(1, 1, n)) % mod;
	}
	if(dep[x] > dep[y]) swap(x, y);
	L = New[x], R = New[y];
	ans = (ans + query(1, 1, n)) % mod;
	printf("%d\n", ans);
}

void op3(void) {
	int x; read(x); read(need);
	L = New[x], R = New[x] + size[x] - 1;
	modify(1, 1, n);
}

void op4(void) {
	int x; read(x);
	L = New[x], R = New[x] + size[x] - 1;
	int ans = query(1, 1, n) % mod;
	printf("%d\n", ans);
}

void Work(void) {
	dfs1(root, 0);
	dfs2(root, root);
	build(1, 1, n);
	while(T--) {
		int op;
		read(op);
		if(op == 1) op1();
		else if(op == 2) op2();
		else if(op == 3) op3();
		else op4();
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}

