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

const int maxn = 5000 + 7;
int dp[maxn / 2][3], a[maxn];
int n;

void Init(void) {
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]);
}

void Work(void) {
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = dp[1][1] = 0;
	for(int i = 2; i <= n; i++) {
		for(int j = (i + 1) >> 1; j >= 1; j--) {
			dp[j][0] = min(dp[j][0], dp[j][2]);
			dp[j][2] = dp[j][1] + max(a[i] - a[i - 1] + 1 , 0);
			dp[j][1] = min(dp[j - 1][0] + max(a[i - 1] - a[i] + 1, 0), dp[j - 1][2] + max(min(a[i - 1], a[i - 2] - 1) - a[i] + 1, 0));
		}
	}
	for(int i = 1; i <= (n + 1) >> 1; i++) {
		printf("%d ", min(dp[i][0], min(dp[i][1], dp[i][2])));
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}

