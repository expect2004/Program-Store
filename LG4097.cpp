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

struct Interval {
	int id;
	double k, b;
}val[maxn * 4];

int T, las, cnt;

inline Interval transmit(int x0, int y0, int x1, int y1, int id) {
	Interval res;
	if(x0 == x1) {
		res.id = id, res.k = 0, res.b = max(y0, y1);
		return res;
	}
	res.k = (double)(y1 - y0) / (double)(x1 - x0); res.id = id;
	res.b = -res.k * (double)x1 + (double)y1;
}

double calc(Interval a, int x) {
	return a.k * x + a.b;
}

inline void Init(void) {
	read(T);
}

#define lfc (x << 1)
#define rgc ((x << 1) | 1)

void modify(int x, int l, int r, int L, int R, Interval p) {
	int mid = (l + r) >> 1;
	if(L <= l && r <= R) {
		if(!val[x].id || calc(val[x], mid) < calc(p, mid)) swap(val[x], p);
		if(!p.id || p.k == val[x].k || l == r) return ;
		double cross = (p.b - val[x].b) / (val[x].k - p.k);
		if(cross < (double)l || cross > (double)r) return ;
		if(p.k < val[x].k) modify(lfc, l, mid, L, R, p);
		else modify(rgc, mid + 1, r, L, R, p);
	}
	else {
		if(L <= mid) modify(lfc, l, mid, L, R, p);
		if(R > mid) modify(rgc, mid + 1, r, L, R, p);
	}
}

Interval query(int x, int l, int r, int pos) {
	if(l == r) return val[x];
	int mid = (l + r) >> 1;
	Interval res;// res.id = 0; res.k = 0; res.b = -1e9;
	if(pos <= mid) res =  query(lfc, l, mid, pos);
	else res = query(rgc, mid + 1, r, pos);
	if(!res.id || calc(res, pos) < calc(val[x], pos)) res=val[x];
	return res;
}

inline void Work(void) {
	
	while(T--) {
		int op; read(op);
		if(op == 0) {
			int k; read(k);
			k = (k + las - 1) % 39989 + 1;
			Interval ans = query(1, 1, 40000, k);
			printf("%d\n", las = ans.id);
		}
		else {
			int X0, Y0, X1, Y1; read(X0); read(Y0); read(X1); read(Y1); ++cnt;
			X0 = (X0 + las - 1) % 39989 + 1, Y0 = (Y0 + las - 1) % 1000000000 + 1;
			X1 = (X1 + las - 1) % 39989 + 1, Y1 = (Y1 + las - 1) % 1000000000 + 1;
			Interval se = transmit(X0, Y0, X1, Y1, cnt);
			if(X0 > X1) swap(X0, X1);
			modify(1, 1, 40000, X0, X1, se);
		}
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}
