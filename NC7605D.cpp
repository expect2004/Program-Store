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

const int maxn = 500000 + 7;

int n, m;
int buff[maxn], v[maxn];

struct Interval {
	int id;
	int k, b;
}val[5000000];
int lfc[5000000], rgc[5000000], cnt;

int dp[maxn];

inline int id(int x, int y) {
	return (x - 1) * m + y;
}

inline void reserv(int k, int &x ,int &y) {
	x = k / m + 1, y = k % m;
	if(y == 0) y = m, x--;
}

inline int calc(Interval p, int x) {
	return p.k * x + p.b;
}

inline int New(){
	++cnt;
	lfc[cnt] = rgc[cnt] = val[cnt].id = val[cnt].k = val[cnt].b = 0;
	return cnt;
}

void modify(int x, int l, int r, int L, int R, Interval p) {
	int mid = (l + r) >> 1;
	if(L <= l && r <= R) {
		if(!val[x].id || calc(val[x], mid) < calc(p, mid)) swap(val[x], p);
		if(!p.id || p.k == val[x].k || l == r) return ;
		double cross = (double)(p.b - val[x].b) / (double)(val[x].k - p.k);
		if(cross < (double)l || cross > (double)r) return ;
		if(p.k < val[x].k) {
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
		if(!lfc[x]) lfc[x] = New();
		res = query(lfc[x], l, mid, pos);
	}
	else {
		if(!rgc[x]) rgc[x] = New();
		res = query(rgc[x], mid + 1, r, pos);
	}
	if(!res.id || calc(res, pos) < calc(val[x], pos)) return val[x];
	return res;
}

void cdq(int l, int r) {
	if(l == r) {
		cnt = 0; New();// val[1].b = -0x3f3f3f3f3f3f3f3fll;
		Interval q;
//		if(l == 1) 
		q.id = id(l, 1), q.k = buff[id(l, 1)], q.b = dp[id(l, 1)] - (l + 1) * buff[id(l, 1)];
		modify(1, 1, m + n, 1, m + n, q);
		for(int i = 2; i <= m; i++) {
			Interval p = query(1, 1, n + m, (l + i));
			int k = p.id, x, y; reserv(k, x, y);
			dp[id(l, i)] = max(dp[id(l, i)], dp[k] + (l + i - x - y) * buff[k] + v[id(l, i)]);
			p.id = id(l, i), p.k = buff[id(l, i)], p.b = dp[id(l, i)] - (l + i) * buff[id(l, i)];
			modify(1, 1, n + m, 1, n + m, p);
		}
		return ;
	}
	int mid = (l + r) >> 1;
	cdq(l, mid);
	cnt = 0; New();// val[1].b = -0x3f3f3f3f3f3f3f3fll;
	for(int j = 1; j <= m; j++) {
		for(int i = l; i <= mid; i++) {
			Interval p; p.id = id(i, j), p.k = buff[id(i, j)], p.b = dp[id(i, j)] - (i + j) * buff[id(i, j)];
			modify(1, 1, n + m, 1, n + m, p);
		}
		for(int i = mid + 1; i <= r; i++) {
			Interval p = query(1, 1, n + m, i + j);
			int k = p.id, x, y; reserv(k, x, y);
			dp[id(i, j)] = max(dp[id(i, j)], dp[k] + (i + j - x - y) * buff[k] + v[id(i, j)]);
			p.id = id(i, j), p.k = buff[id(i, j)], p.b = dp[id(i, j)] - (i + j) * buff[id(i, j)];
//			modify(1, 1, n + m, 1, n + m, p);
		}
	}
	cdq(mid + 1, r);
}

inline void Init(void) {
	read(n); read(m);
//	for(int i = 1; i <= id())
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			read(buff[id(i, j)]);
			dp[id(i, j)] = -0x3f3f3f3f3f3f3f3fll;
		}
	}
	dp[1] = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			read(v[id(i, j)]);
		}
	}
}

inline void Work(void) {
	cdq(1, n);
	printf("%lld\n", dp[id(n, m)]);
}

signed main(void) {
	Init();
	Work();
	return 0;
}
