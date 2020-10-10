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

const int maxn = 300000 + 7;
const int maxm = 600000 + 7;

int n, T;
int Head[maxn], to[maxm], Next[maxm], tot;
void addedge(int x, int y) {
	to[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void add(int x, int y) {
	addedge(x, y); addedge(y, x);
}

void Init(void) {
	read(n); read(T);
	for(int i = 1, x, y; i < n; i++) {
		read(x); read(y);
		add(x, y);
	}
}

int size[maxn], dep[maxn], rt[maxn];
int cnt, lfc[20000000], rgc[20000000];
long long val[20000000];
int New() {
	return ++cnt;
}

void modify(int x, int l, int r, int pos, int need) {
	if(l == r) {
		val[x] += need; return;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) {
		if(!lfc[x]) lfc[x] = New();
		modify(lfc[x], l, mid, pos, need);
	}
	else {
		if(!rgc[x]) rgc[x] = New();
		modify(rgc[x], mid + 1, r, pos, need);
	}
	val[x] = val[lfc[x]] + val[rgc[x]];
}
int merge(int p, int q, int l, int r) {
	if(!p || !q) return p + q;
	if(l == r) {
		int x = New();
		val[x] = val[p] + val[q];
		return x;
	}
	int mid = (l + r) >> 1; int x = New();
	lfc[x] = merge(lfc[p], lfc[q], l, mid);
	rgc[x] = merge(rgc[p], rgc[q], mid + 1, r);
	val[x] = val[lfc[x]] + val[rgc[x]];
	return x;
}
long long query(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) return val[x];
	if(r < L || R < l) return 0;
	long long res = 0, mid = (l + r) >> 1;
	if(lfc[x]) res += query(lfc[x], l, mid, L, R);
	if(rgc[x]) res += query(rgc[x], mid + 1, r, L, R);
	return res;
}

void dfs(int x, int f, int dp) {
	dep[x] = dp, size[x] = 1, rt[x] = New();
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == f) continue;
		dfs(y, x, dp + 1); size[x] += size[y];
	}
	modify(rt[x], 1, n, dep[x], size[x] - 1);
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == f) continue;
		rt[x] = merge(rt[x], rt[y], 1, n);
	}
}

void Work(void) {
	dfs(1, 0, 1);
	while(T--) {
		int p, k;
		read(p); read(k);
		long long ans = (long long)(size[p] - 1) * min(dep[p] - 1, k);
		ans = ans + query(rt[p], 1, n, dep[p] + 1, dep[p] + k);
		printf("%lld\n", ans);
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}
