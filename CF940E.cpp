#include<bits/stdc++.h>
using namespace std;

#define int long long

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

const int maxn = 100000 + 7;
const double lg2 = log(2.0);

int n, c;
int a[maxn], s[maxn];

int st[maxn][18];
int dp[maxn];

void Preprocess(void) {
	for(int i = 1; i <= n; i++) st[i][0] = a[i];
	for(int i = 1; i <= 17; i++) {
		for(int j = 1; j + (1 << (i - 1)) <= n; j++) {
			st[j][i] = min(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
		}
	}
}

int query(int l, int r) {
	int k = (int)(log((double)(r - l + 1)) / lg2);
	return min(st[l][k], st[r - (1 << k) + 1][k]);
}

void Init(void) {
	read(n); read(c);
	for(int i = 1; i <= n; i++) {
		read(a[i]);
		s[i] = s[i - 1] + a[i];
	}
}

void Work(void) {
	Preprocess();
	for(int i = 1; i <= n; i++) {
		dp[i] = dp[i - 1] + a[i];
		if(i >= c) dp[i] = min(dp[i], dp[i - c] + s[i] - s[i - c] - query(i - c + 1, i));
	}
	printf("%lld\n", dp[n]);
}

signed main(void) {
	Init();
	Work();
	return 0;
}

