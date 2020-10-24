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

int n, Te;
int Head[maxn], to[maxm], Next[maxm], tot;
inline void addedge(int x, int y) {
	to[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
inline void add(int x, int y) {
	addedge(x, y); addedge(y, x);
}

inline void Init(void) {
	read(n); read(Te);
	for(int i = 1, x, y; i < n; i++) {
		read(x); read(y);
		add(x, y);
	}
}

int dep[maxn], dfn[maxn], ind, low[maxn];

void dfs(int x, int f, int dp) {
	dep[x] = dp, dfn[x] = ++ind;
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == f) continue;
		dfs(y, x, dp + 1);
	}
	low[x] = ind;
}

#define lfc (x << 1)
#define rgc ((x << 1) | 1)
#define mid ((l + r) >> 1)

int val[maxn << 2], tag[maxn << 2];

inline void down(int x, int l, int r){
	if(!tag[x]) return ;
	val[lfc] = val[lfc] + (mid - l + 1) * tag[x];
	val[rgc] = val[rgc] + (r - mid) * tag[x];
	tag[lfc] += tag[x], tag[rgc] += tag[x];
	tag[x] = 0;
}

inline void up(int x) {
	val[x] = val[lfc] + val[rgc];
}

void modify(int x, int l, int r, int L, int R, int need) {
	if(L <= l && r <= R) {
		tag[x] += need, val[x] += (r - l + 1) * need;
		return ;
	}
	down(x, l, r);
	if(L <= mid) modify(lfc, l, mid, L, R, need);
	if(R > mid) modify(rgc, mid + 1, r, L, R, need);
	up(x);
}

int query(int x, int l, int r, int pos) {
	if(l == r) return val[x];
	down(x, l, r);
	if(pos <= mid) return query(lfc, l, mid, pos);
	else return query(rgc, mid + 1, r, pos);
}

#undef lfc
#undef rgc
#undef mid

struct BIT {
	#define lowbit(x) (x & (-x))
	int c[maxn];
	void add(int x, int k) {while(x <= n) { c[x] += k; x += lowbit(x); }}
	int query(int x) {int res = 0; while(x) {res += c[x]; x -= lowbit(x);} return res; }
	#undef lowbit(x)
}T;

inline void op0(void) {
	int x, necc, d; read(x); read(necc); read(d);
	int dis = dep[x] - dep[1];
	if(dis <= d) {
		int pr = d - dis + 1;
		T.add(pr, necc);
		int L = dfn[x] - dep[x] + 2 + pr - 1, R = min(low[x], dfn[x] + d);
		if(L > R) return ;
		modify(1, 1, n, L, R, necc);
	}
	else {
		int L = dfn[x] - d, R = min(dfn[x] + d, low[x]);
		modify(1, 1, n, L, R, necc);
	}
}

inline void op1(void) {
	int x; read(x);
	int ans = query(1, 1, n, dfn[x]) + T.query(n) - T.query(dep[x] - 1);
	printf("%d\n", ans);
}

inline void Work(void) {
	dfs(1, 0, 1);
	while(Te--) {
		int op; read(op);
		if(op == 0) op0();
		else op1();
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}

