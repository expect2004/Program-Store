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
const int INF = 0x3f3f3f3f;

int n, T;
int Head[maxn], Next[maxn], to[maxn], tot;
void add(int x, int y) {
	to[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}

int size[maxn], fa[maxn], son[maxn], top[maxn], dep[maxn];
int dfn[maxn], ind;

void dfs1(int x, int f, int dp) {
	size[x] = 1, fa[x] = f, dep[x] = dp;
	dfn[x] = ++ind;
	int mx = -1;
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		dfs1(y, x, dp + 1); size[x] += size[y];
		if(size[y] > mx) mx = size[y], son[x] = y;
	}
}

void dfs2(int x, int tp) {
	top[x] = tp;
	if(!son[x]) return ;
	dfs2(son[x], tp);
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == son[x]) continue;
		dfs2(y, y);
	}
}

int LCA(int x, int y) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	return x;
}

inline void Init(void) {
	read(n); read(T);
	for(int i = 2, x; i <= n; i++) {
		read(x);
		add(x, i);
	}
}

namespace Segment1 {
	#define lfc (x << 1)
	#define rgc ((x << 1) | 1)
	#define mid ((l + r) >> 1)
	int val[maxn * 4];
	void build(int x, int l, int r) {
		if(l == r) {
			val[x] = l; return ;
		}
		build(lfc, l, mid); build(rgc, mid + 1, r);
		val[x] = LCA(val[lfc], val[rgc]);
	}
	int query(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return val[x];
		int A = 0, B = 0;
		if(L <= mid) A = query(lfc, l, mid, L, R);
		if(R > mid) B = query(rgc, mid + 1, r, L, R);
		if(!A || !B) return A + B;
		return LCA(A, B);
	}
	#undef lfc
	#undef rgc
	#undef mid
}

namespace Segment2 {
	#define lfc (x << 1)
	#define rgc ((x << 1) | 1)
	#define mid ((l + r) >> 1)
	int mx[maxn * 4], mn[maxn * 4], mxpos[maxn * 4], mnpos[maxn * 4];
	void build(int x, int l, int r) {
		if(l == r) {
			mx[x] =  mn[x] = dfn[l];
			mxpos[x] = mnpos[x] = l;
			return ;
		}
		build(lfc, l, mid); build(rgc, mid + 1, r);
		if(mx[lfc] > mx[rgc]) mx[x] = mx[lfc], mxpos[x] = mxpos[lfc];
		else mx[x] = mx[rgc], mxpos[x] = mxpos[rgc];
		if(mn[lfc] < mn[rgc]) mn[x] = mn[lfc], mnpos[x] = mnpos[lfc];
		else mn[x] = mn[rgc], mnpos[x] = mnpos[rgc];
	}
	pair <int, int> querymx(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return make_pair(mx[x], mxpos[x]);
		if(r < L || R < l) return make_pair(-INF, 0);
		pair <int, int> A = querymx(lfc, l, mid, L, R), B = querymx(rgc, mid + 1, r, L, R);
		if(A.first > B.first) return A;
		else return B;
	}
	pair <int, int> querymn(int x, int l, int r, int L, int R) {
		if(L <= l && r <= R) return make_pair(mn[x], mnpos[x]);
		if(r < L || R < l) return make_pair(INF, 0);
		pair <int, int> A = querymn(lfc, l, mid, L, R), B = querymn(rgc, mid + 1, r, L, R);
		if(A.first < B.first) return A;
		else return B;
	}
	#undef lfc
	#undef rgc
	#undef mid
}

inline int solve(pair <int, int> p, int l, int r) {
	int pos = p.second;
	int A = 0, B = 0;
	int L1 = l, R1 = pos - 1;
	if(L1 <= R1) A = Segment1::query(1, 1, n, L1, R1);
	int L2 = pos + 1, R2 = r;
	if(L2 <= R2) B = Segment1::query(1, 1, n, L2, R2);
	if(!A || !B) return A + B;
	return LCA(A, B);
}

inline void Work(void) {
	dfs1(1, 0, 1);
	dfs2(1, 1);
	Segment1::build(1, 1, n);
	Segment2::build(1, 1, n);
	while(T--) {
		int l, r; read(l); read(r);
		pair <int, int> MX = Segment2::querymx(1, 1, n, l, r), MN = Segment2::querymn(1, 1, n, l, r);
		int A = solve(MX, l, r), B = solve(MN, l, r);
		if(dep[A] > dep[B]) printf("%d %d\n", MX.second, dep[A] - 1);
		else printf("%d %d\n", MN.second, dep[B] - 1);
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}
