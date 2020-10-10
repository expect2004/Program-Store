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

const int maxn = 400000 + 7;

int n;
int tot = 1, ls[maxn], rs[maxn], a[maxn], size[maxn];
int cnt, val[1000000], lfc[1000000], rgc[1000000];
int rt[maxn];

int New() {
	return ++cnt;
}

void Init(int x) {
	int p; read(p);
	if(p != 0) {
		a[x] = p; return ;
	}
	ls[x] = ++tot; rs[x] = ++tot;
//	fa[ls[x]] = x, fa[rs[x]] = x;
	Init(ls[x]); Init(rs[x]);
}

int ans;

void modify(int x, int l, int r, int pos, int need) {
	if(l == r) {
		val[x] = need; return ;
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
int query(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) return val[x];
	if(r < L || R < l) return 0;
	int res = 0, mid = (l + r) >> 1;
	if(lfc[x]) res += query(lfc[x], l, mid, L, R);
	if(rgc[x]) res += query(rgc[x], mid + 1, r, L, R);
	return res;
}
int merge(int p, int q, int l, int r) {
	if(!p || !q) return p + q;
	if(l == r) {
		val[p] += val[q];
		return p;
	}
	int mid = (l + r) >> 1;
	lfc[p] = merge(lfc[p], lfc[q], l, mid);
	rgc[p] = merge(rgc[p], rgc[q], mid + 1, r);
	val[p] = val[lfc[p]] + val[rgc[p]];
	return p;
}

vector <int> v;

void dfs2(int x) {
	if(a[x]) {
		v.push_back(a[x]); return ;
	}
	dfs2(ls[x]); dfs2(rs[x]);
}

void dfs(int x) {
	if(a[x]) {
		size[x] = 1; rt[x] = New();
		modify(rt[x], 1, n, a[x], 1);
		return ;
	}
	dfs(ls[x]); dfs(rs[x]);
	size[x] = size[ls[x]] + size[rs[x]];
	if(size[ls[x]] > size[rs[x]]) swap(ls[x], rs[x]);
	v.clear(); dfs2(ls[x]);
	int conl = 0, conr = 0;
	for(auto i : v) {
		conl += query(rt[rs[x]], 1, n, 1, i - 1);
		conr += query(rt[rs[x]], 1, n, i + 1, n);
	}
	ans += min(conl, conr);
	for(auto i : v) {
		modify(rt[rs[x]], 1, n, i, 1);
	}
	rt[x] = rt[rs[x]];
//	rt[x] = merge(rt[rs[x]], rt[ls[x]])
//	rt[ls[x]] = merge()
}

void Work(void) {
	dfs(1);
	printf("%d\n", ans);
//	for(int i = 1; i <= n; i++) rt[i] = New();
}

signed main(void) {
	read(n);
	Init(1);
	Work();
	return 0;
}
