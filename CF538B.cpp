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

int n;
int a[10], cnt;
int ans[10];
inline void Init(void) {
	read(n);
}

inline void Work(void) {
	int t = n;
	while(t) {
		a[++cnt] = t % 10;
		t /= 10;
	}
	int r = 0;
	for(int i = 1; i <= cnt; i++) {
		r = max(a[i], r);
	}
	printf("%d\n", r);
	for(int i = cnt; i >= 1; i--) {
		for(int j = 1; j <= r; j++) ans[j] = ans[j] * 10;
		for(int j = 1; j <= a[i]; j++) {
			ans[j] = ans[j] + 1;
		}
	}
	for(int i = 1; i <= r; i++) {
		printf("%d%c", ans[i], " \n"[i == r]);
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}

