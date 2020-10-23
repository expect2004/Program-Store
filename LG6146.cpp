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
const int mod = 1000000007;

int n;
struct Interval {
	int l, r;
}a[maxn];

bool comp(Interval a, Interval b) {
	return a.l == b.l ? a.r < b.r : a.l < b.l;
}

inline void Init(void) {
	read(n);
	for(int i = 1; i <= n; i++) {
		read(a[i].l); read(a[i].r);
	}
}

int dp[maxn];

struct BIT {
	#define lowbit(x) (x & (-x))
	int c[maxn];
	void add(int x, int k) {
		while(x <= 2 * n) c[x] += k, x += lowbit(x);
	}
	int query(int x) {
		int res = 0;
		while(x) res += c[x], x -= lowbit(x);
		return res;
	}
}T;

int fpow(long long x, int p) {
	long long res = 1ll;
	while(p) {
		if(p & 1) res = res * x % mod; p >>= 1;
		x = x * x % mod;
	}
	return res;
}

inline void Work(void) {
	sort(a + 1, a + n + 1, comp);
	for(int i = 1; i <= n; i++) {
		dp[i] = 2ll * dp[i - 1] % mod;
		int x = T.query(a[i].l - 1);
		dp[i] = (dp[i] + fpow(2, x)) % mod;
		T.add(a[i].r, 1);
	}
	printf("%d\n", dp[n]);
}

signed main(void) {
	Init();
	Work();
	return 0;
}

