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

const int maxn = 100 + 3;
const int mod = 2017;

struct Matrix{ 
	int n, mat[maxn][maxn];
	Matrix(){memset(mat, 0, sizeof(mat));}
}bas;

int n, m, T;

Matrix mul(Matrix a, Matrix b) {
	Matrix c; c.n = a.n;
	for(int i = 1; i <= c.n; i++) {
		for(int j = 1; j <= c.n; j++) {
			for(int k = 1; k <= c.n; k++) {
				c.mat[i][j] = (c.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % mod;
			}
		}
	}
	return c;
}

Matrix fpow(Matrix x, int p) {
	Matrix res; res.n = x.n;
	for(int i = 1; i <= n + 1; i++) res.mat[i][i] = 1;
	while(p) {
		if(p & 1) res = mul(res, x); p >>= 1;
		x = mul(x, x);
	}
	return res;
}

inline void Init(void) {
	read(n); read(m);
	bas.n = n + 1;
	for(int i = 1; i <= n + 1; i++) bas.mat[i][i] = bas.mat[i][n + 1] = 1;
	for(int i = 1, x, y; i <= m; i++) {
		read(x); read(y);
		bas.mat[x][y] = bas.mat[y][x] = 1;
	}
	read(T);
	Matrix ans = fpow(bas, T);
	int cnt(0);
	for(int i = 1; i <= n + 1; i++) cnt = (cnt + ans.mat[1][i]) % mod;
	printf("%d\n", cnt);
}

signed main(void) {
	Init();
	return 0;
}
