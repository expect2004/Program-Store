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

template < typename Tp >
inline void chread(Tp &x) {
	char ch = 1;
	while(ch != 'Q' && ch != 'P') ch = getchar();
	if(ch == 'P') x = 0;
	else x = 1;
}

const int maxn = 100000 + 7;

struct Interval {
	int id;
	double k, b;
}val[maxn * 4];

double calc(Interval a, int x) {
	return a.k * x + a.b;
}

int T, cnt;

#define lfc (x << 1)
#define rgc ((x << 1) | 1)

void modify(int x, int l, int r, int L, int R, Interval p) {
	int mid = (l + r) >> 1;
	if(L <= l && r <= R) {
		if(!val[x].id || calc(val[x], mid) < calc(p, mid)) swap(val[x], p);
		if(l == r || !p.id || p.k == val[x].k) return ;
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
	Interval res;
	if(pos <= mid) res = query(lfc, l, mid, pos);
	else res = query(rgc, mid + 1, r, pos);
	if(!res.id || calc(res, pos) < calc(val[x], pos)) return val[x];
	return res;
}

inline void Init(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
}

inline void Work(void) {
	while(T--) {
		string s; int op; cin >> s;
		if(s[0] == 'P') op = 0;
		else op = 1;
		if(op == 0) {
			double s, k; cin >> s >> k;
			Interval se; se.id = ++cnt, se.k = k, se.b = s - k;
			modify(1, 1, 50000, 1, 50000, se);
		}
		else {
			int k; cin >> k;
			Interval ans = query(1, 1, 50000, k);
			cout << max(0, (int)floor((calc(ans, k) / 100.0))) << '\n';
//			printf("%d\n", max(0, (int)calc(ans, k) / 100));
		}
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}

