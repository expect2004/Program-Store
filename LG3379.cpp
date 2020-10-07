/*
Offical Template
heavy-light chain for LCA
Date : 2020 - 10 - 7
Author : expect2004
Problem id : Luogu3379
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

const int maxn = 500000 + 7;
const int maxm = 1000000 + 7;

int n, T, R;
int Head[maxn], Next[maxm], to[maxm], tot;
void addedge(int x, int y) {
	to[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void add(int x, int y) {
	addedge(x, y); addedge(y, x);
}

int siz[maxn], son[maxn], fa[maxn], dep[maxn];

void dfs1(int x, int f) {
	siz[x] = 1, fa[x] = f; int mx = -1;
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == f) continue;
		dep[y] = dep[x] + 1;
		dfs1(y, x); siz[x] += siz[y];
		if(mx < siz[y]) son[x] = y, mx = siz[y];
	}
}

int top[maxn];

void dfs2(int x, int tp) {
	top[x] = tp;
	if(son[x] == 0) return ;
	dfs2(son[x], tp);
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == fa[x] || y == son[x]) continue;
		dfs2(y, y);
	}
}

int LCA(int x, int y) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	if(dep[x] < dep[y]) return x;
	return y;
}

void Init(void) {
	read(n); read(T); read(R);
	for(int i = 1, x, y; i < n; ++i) {
		read(x); read(y);
		add(x, y);
	}
}

void Work(void) {
	dfs1(R, 0);
	dfs2(R, R);
	while(T--) {
		int x, y;
		read(x); read(y);
		printf("%d\n", LCA(x, y));
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}

