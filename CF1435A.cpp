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

const int maxn = 107;

int n;
int a[maxn];

inline void Init(void) {
	read(n); int  x = 1, s = 0;
	for(int i = 1; i <= n; i++) {
		read(a[i]);
	}
	for(int i = 1; i <= n; i++) {
		if(i & 1) printf("%d ", -a[i + 1]);
		else printf("%d ", a[i - 1]);
	}
	puts("");
//	s -= a[n];
//	x = s * a[n];
//	int p = __gcd(s, a[n]);
//	a[n] /= p, s /= p;
//	for(int i = 1; i < n; i++) {
//		printf("%d ", -a[n]);
//	}
//	printf("%d\n", s);
//	for(int i = 1; i <= n; i++) {
//		printf("%d%c", x / a[i], " \n"[i == n]);
//	}
}

inline void Work(void) {

}

signed main(void) {
	int T;
	read(T);
	while(T--) {
		Init();
	Work();
	}
	return 0;
}

