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

int a, b, c, d, T;

inline void Init(void) {
	read(T);
	while(T--) {
		read(a); read(b); read(c); read(d);
		int k = c / d;
		int ans = k * b * d + (c - d * k) * b;
		int ass = a / (b * d); int qq = (ass + 1) * a;
		int zzk = (b * d) * (ass + 1) * ass / 2;
		if(a > ans) puts("-1");
		else printf("%lld\n", qq - zzk);
	}
}

inline void Work(void) {

}

signed main(void) {
	Init();
	Work();
	return 0;
}

