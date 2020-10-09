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
const int maxn = 300000 + 7;

int n, k, mn = 1000000000;
int a[maxn];

void Init(void) {
	read(n); read(k);
	for(int i = 1; i <= n; i++) {
		read(a[i]);
		mn = min(mn, a[i]);
	}
}

void Work(void) {
	for(int i = mn; true; ) {
		bool succ = true;
		for(int j = 1; j <= n; j++) {
//			int p = a[j] % i;
			while(a[j] % i > k) {
				succ = false; i--;
			}
		}
		if(succ) {
			printf("%d\n", i); return ;
		}
	}
	puts("0");
}

signed main(void) {
	Init();
	Work();
	return 0;
}
