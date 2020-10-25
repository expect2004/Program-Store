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

int T, n, m;
int a[250007], b[250007];

inline void Init(void) {
	read(n); read(m);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			int x; read(x);
			a[x] = j;
		}
	}
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) {
			int x; read(x);
			b[x] = j;
		}
	}
}

int c[507][507];

inline void Work(void) {
	for(int i = 1; i <= n * m; i++) {
		c[b[i]][a[i]] = i;
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(j != m) printf("%d ", c[i][j]);
			else printf("%d\n", c[i][j]);
		}
	}
}

signed main(void) {
	read(T);
	while(T--) {
		Init();
		Work();
	}
	return 0;
}

