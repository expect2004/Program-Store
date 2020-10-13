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

const int maxn = 100000 + 7;
const int maxp = 100 + 3;

int n, m, p;
int que[maxp][maxn], f[maxp], r[maxp], d[maxn];
int t[maxn], s[maxn], dp[maxp][maxn];

inline void Init(void) {
	read(n); read(m); read(p);
	for(int i = 2; i <= n; i++) {
		read(d[i]); d[i] += d[i - 1];
	}
	for(int i = 1, x, y; i <= m; i++) {
		read(x); read(y);
		t[i] = y - d[x];
	}
}

inline double X(int i) {return (double)i;}
inline double Y(int i, int p) {return (double)(dp[i][p] + s[p]);}
inline double K(int i, int x, int y) {return (Y(i, x) - Y(i, y)) / (X(x) - X(y));}

inline void Work(void) {
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	sort(t + 1, t + m + 1);
	for(int i = 1; i <= m; i++) s[i] = s[i - 1] + t[i];
	for(int i = 1; i <= p; i++) f[i] = r[i] = 1;
	for(int j = 1; j <= p; j++) {
		for(int i = 1; i <= m; i++) {
			while(f[j] < r[j] && K(j - 1, que[j][f[j]], que[j][f[j] + 1]) < (double)t[i]) f[j]++;
			int p = que[j][f[j]];
			dp[j][i] = dp[j - 1][p] + (i - p) * t[i] - s[i] + s[p];
			while(f[j] < r[j] && K(j - 1, que[j][r[j] - 1], que[j][r[j]]) > K(j - 1, que[j][r[j] - 1], i)) r[j]--;
			que[j][++r[j]] = i;
		}
	}
	printf("%lld\n", dp[p][m]);
}

signed main(void) {
	Init();
	Work();
	return 0;
}

