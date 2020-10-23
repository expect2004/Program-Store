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

const int mod = 1000000007;

int n, m, k;
int s[750 * 750 + 7];
int dp[757][757], a[757][757];

void cdq(int l, int r) {
	if(l == r) return ;
	int mid = (l + r) >> 1;
	cdq(l, mid);
	int total = 0;
	for(int i = 1; i <= m; i++) {
		for(int j = mid + 1; j <= r; j++) {
			dp[i][j] = ((dp[i][j] + total - s[a[i][j]]) % mod + mod) % mod;
		}
		for(int j = l; j <= mid; j++) {
//			dp[i][j] = (dp[i][j] + total - s[a[i][j]]) % mod;
			s[a[i][j]] = (s[a[i][j]] + dp[i][j]) % mod;
			total = (total + dp[i][j]) % mod;
		}
	}
	for(int i = 1; i <= m; i++) {
		for(int j = l; j <= mid; j++) s[a[i][j]] = ((s[a[i][j]] - dp[i][j]) % mod + mod) % mod;
	}
	cdq(mid + 1, r);
}

inline void Init(void) {
	read(n); read(m); read(k);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			read(a[i][j]);
		}
	}
}

inline void Work(void) {
	dp[1][1] = 1;
	cdq(1, n);
	printf("%d\n", dp[n][m]);
}

signed main(void) {
	Init();
	Work();
	return 0;
}

