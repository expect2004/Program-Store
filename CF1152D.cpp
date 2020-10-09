#include<bits/stdc++.h>
using namespace std;

template < typename Tp >
void read(Tp &x) {
	x = 0; int fh = 1; char ch = 1;
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= fh;
}

template < typename Tp >
void biread(Tp &x) {
	x = 0; int fh = 1; char ch = 1;
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 2 + ch - '0', ch = getchar();
	x *= fh;
}

const int maxn = 1000 + 7;
const int mod = 1000000007;

int n, ans;
int dp[maxn][maxn];

void Init(void) {
	read(n);
}

void Work(void) {
	dp[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		dp[i][0] = dp[i - 1][0];
		if(i & 1) ans = (ans + dp[i][0]) % mod;
		for(int j = 1; j <= i; j++) {
			dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % mod;
			if((i + j) & 1) ans = (ans + dp[i][j]) % mod;
		}
	}
	printf("%d\n", ans);
}

signed main(void) {
	Init();
	Work();
	return 0;
}

