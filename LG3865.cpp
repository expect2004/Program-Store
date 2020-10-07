/*
Offical Template
ST Table for RMQ
Date : 2020 - 10 - 7
Author : expect2004
Problem id : Luogu3865
*/
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

const int maxn = 100000 + 7;
const double lg2 = log(2.0);

int st[maxn][20], a[maxn], n, T;

void Init(void) {
	read(n); read(T);
	for(int i = 1; i <= n; ++i) {
		read(a[i]); st[i][0] = a[i];
	}
}

void Preprocess(void) {
	for(int i = 1; i <= 18; i++) {
		for(int j = 1; j + (1 << (i - 1)) <= n; j++) {
			st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
		}
	}
}

void Work(void) {
	Preprocess();
	while(T--) {
		int l, r;
		read(l); read(r);
		int k = (int)(log((double)(r - l + 1)) / lg2);
		int ans = max(st[l][k], st[r - (1 << k) + 1][k]);
		printf("%d\n", ans);
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}

