#include<bits/stdc++.h>
using namespace std;
#define int long long
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

const int maxn = 300000 + 7;

struct Interval {
	int id;
	int k, b;
}val[5000000];
int lfc[5000000], rgc[5000000], cnt = 1;

int n, s, dp[maxn];
int C[maxn], T[maxn];

inline int New() {
	return ++cnt;
}

int calc(Interval a, int x) {
	return a.k * x + a.b;
}

void modify(int x, int l, int r, int L, int R, Interval p) {
	int mid = (l + r) >> 1;
	if(L <= l && r <= R) {
		if(!val[x].id || calc(val[x], mid) > calc(p, mid)) swap(val[x], p);
		if(l == r || !p.id || p.k == val[x].k) return ;
		double cross = (double)(p.b - val[x].b) / (val[x].k - p.k);
		if(cross < (double)l || cross > (double)r) return ;
		if(p.k > val[x].k) {
			if(!lfc[x]) lfc[x] = New();
			modify(lfc[x], l, mid, L, R, p);
		}
		else {
			if(!rgc[x]) rgc[x] = New();
			modify(rgc[x], mid + 1, r, L, R, p);
		}
	}
	else {
		if(L <= mid) {
			if(!lfc[x]) lfc[x] = New();
			modify(lfc[x], l, mid, L, R, p);
		}
		if(R > mid) {
			if(!rgc[x]) rgc[x] = New();
			modify(rgc[x], mid + 1, r, L, R, p);
		}
	}
}

Interval query(int x, int l, int r, int pos) {
	if(l == r) return val[x];
	int mid = (l + r) >> 1;
	Interval res;
	if(pos <= mid) {
		if(!lfc[x]) return val[x];
		res = query(lfc[x], l, mid, pos);
	}
	else {
		if(!rgc[x]) return val[x];
		res = query(rgc[x], mid + 1, r, pos);
	}
	if(!res.id || calc(res, pos) > calc(val[x], pos)) return val[x];
	return res;
}

inline void Init(void) {
	read(n); read(s);
	for(int i = 1; i <= n; i++) {
		read(T[i]); read(C[i]);
		T[i] += T[i - 1], C[i] += C[i - 1];
	}
}

inline void Work(void) {
	memset(dp, 0x3f, sizeof(dp)); dp[0] = 0;
	Interval position;
	position.id = 1, position.k = 0, position.b = s * C[n];
	modify(1, -256 * 3 * 100000, 256 * 3 * 100000, -256 * 3 * 100000, 256 * 3 * 100000, position);
	for(int i = 1; i <= n; i++) {
		position = query(1, -256 * 3 * 100000, 256 * 3 * 100000, T[i]);
		int j = position.id - 1;
		dp[i] = dp[j] + s * C[n] - s * C[j] + T[i] * C[i] - T[i] * C[j];
		position.id = i + 1, position.k = -C[i], position.b = dp[i] + s * C[n] - s * C[i];
		modify(1, -256 * 3 * 100000, 256 * 3 * 100000, -256 * 3 * 100000, 256 * 3 * 100000, position);
	}
	printf("%lld\n", dp[n]);
}

signed main(void) {
	Init();
	Work();
	return 0;
}
