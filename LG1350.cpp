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

const int mod = 100000 + 3;
const int maxn = 2000 + 7;

int a, b, c, d, k;
int dp[maxn][maxn];

inline void Init(void) {
	read(a); read(b); read(c); read(d); read(k);
}

inline void Work(void) {
	dp[0][0] = 1;
	for(int i = 1; i <= b + d; i++) {
		dp[i][0] = 1;
		int m = a * (i <= b) + (i > b) * (a + c);
		for(int j = 1; j <= min(i, m); j++) {
//			int m;
//			if(i <= b) m = a;
//			else m = a + c;
			dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] * (m - j + 1)) % mod;
		}
	}
	printf("%d\n", dp[b + d][k]);
}

signed main(void) {
	Init();
	Work();
	return 0;
}

