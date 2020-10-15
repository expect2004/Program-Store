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

int n; long double S;
double a[maxn], b[maxn], R[maxn], f[maxn];

struct Interval {
	int id;
	long double k, b;
}val[5000000];
int lfc[5000000], rgc[5000000], cnt = 1;

inline void Init(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> S;
	for(int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i] >> R[i];
	}
}

inline int New() {
	return ++cnt;
}

inline long double Na(int j) {
	return R[j] / (R[j] * a[j] + b[j]) * f[j];
}

inline long double Nb(int j) {
	return 1.0 / (R[j] * a[j] + b[j]) * f[j];
}

inline long double calc(Interval a, long double x) {
	return a.k * x + a.b;
}

const long double eps = 1e-10;

void modify(int x, long double l, long double r, long double L, long double R, Interval p) {
	long double mid = (l + r) / 2.0;
//	if(L <= l && r <= R) {
		if(!val[x].id || calc(val[x], mid) < calc(p, mid)) swap(val[x], p);
		if(!p.id || r - l <= eps || p.k == val[x].k) return ;
		long double cross = (p.b - val[x]. b) / (val[x].k - p.k);
		if(cross < (long double)l || cross > (long double)r) return ;
		if(p.k < val[x].k) {
			if(!lfc[x]) lfc[x] = New();
			modify(lfc[x], l, mid, L, R, p);
		}
		else {
			if(!rgc[x]) rgc[x] = New();
			modify(rgc[x], mid + eps, r, L, R, p);
		}
//	}
//	else {
//		if(L <= mid) {
//			if(!lfc[x]) lfc[x] = New();
//			modify(lfc[x], l, mid, L, R, p);
//		}
//		if(R > mid) {
//			if(!rgc[x]) rgc[x] = New();
//			modify(rgc[x], mid + eps, r, L, R, p);
//		}
//	}
}

Interval query(int x, long double l, long double r, long double pos) {
	if(r - l <= eps) return val[x];
	long double mid = (l + r) / 2.0;
	Interval res;
	if(pos <= mid) {
		if(!lfc[x]) lfc[x] = New();
		res = query(lfc[x], l, mid, pos);
	}
	else {
		if(!rgc[x]) rgc[x] = New();
		res = query(rgc[x], mid + eps, r, pos);
	}
	if(!res.id || calc(res, pos) < calc(val[x], pos)) return val[x];
	return res;
}

inline void Work(void) {
	f[1] = S;
	Interval line; line.id = 1, line.k = Na(1), line.b = Nb(1);
	modify(1, 0.0, 1e9, 0.0, 1e9, line);
	for(int i = 2; i <= n; i++) {
		line = query(1, 0.0, 1e9, a[i] / b[i]);
		int j = line.id;
		f[i] = Na(j) * a[i] + Nb(j) * b[i];
		f[i] = max(f[i - 1], f[i]);
		line.id = i, line.k = Na(i), line.b = Nb(i);
		modify(1, 0.0, 1e9, 0.0, 1e9, line);
	}
//	f[1] = S;
//	for(int i = 2; i <= n; i++) {
//		f[i] = f[i - 1];
//		for(int j = 1; j < i; j++) f[i] = max(f[i], Na(j) * a[i] + Nb(j) * b[i]);
//	}
	cout << fixed << setprecision(3) << f[n] << '\n';
//	f[i] = max(f[i], Na(j) * a[i] + Nb(j) * b[i]);
}
 
signed main(void) {
	Init();
	Work();
	return 0;
}

