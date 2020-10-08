//solution
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

const int maxn = 30 + 3;
const int maxm = 30 + 3;
const int maxk = 50 + 3;
const int N = 30, M = 30;

int T, n, m, k;
int dp[maxn][maxm][maxk];

void Init(void) {
	read(T);
}

void Preprocess(void) {
	memset(dp, 0x3f, sizeof(dp));
	for(int i = 0; i <= N; i++) {
		for(int j = 0; j <= M; j++) {
			dp[i][j][0] = 0;
			if(i * j <= 50) dp[i][j][i * j] = 0;
		}
	}
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= M; j++) {
			int K = min(i * j, 50);
			for(int p = 1; p <= K; p++) {
				for(int q = 1; q <= i / 2; q++) {
					int ed = min(q * j, p);
					for(int r = 0; r <= ed; r++) {
						dp[i][j][p] = min(dp[i][j][p], dp[q][j][r] + dp[i - q][j][p - r] + j * j);
					}
				}
				for(int q = 1; q <= j / 2; q++) {
					int ed = min(q * i, p);
					for(int r = 0; r <= ed; r++) {
						dp[i][j][p] = min(dp[i][j][p], dp[i][q][r] + dp[i][j - q][p - r] + i * i);
					}
				}
			}
		}
	}
}

void Work(void) {
	Preprocess();
	while(T--) {
		read(n); read(m); read(k);
		printf("%d\n", dp[n][m][k]);
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}

