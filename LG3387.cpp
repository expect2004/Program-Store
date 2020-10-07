/*
Offical Template
Tarjan
Date : 2020 - 10 - 6
Author : expect2004
Problem id : Luogu3387
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

const int maxn = 10000 + 7;
const int maxm = 100000 + 7;

int n, m;
int Head[maxn], Next[maxm], to[maxm], tot, fr[maxm];
int a[maxn];

void add(int x, int y) {
	to[++tot] = y, Next[tot] = Head[x], Head[x] = tot, fr[tot] = x;
}

void Init(void) {
	read(n); read(m);
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 1, x, y; i <= m; i++) {
		read(x); read(y);
		add(x, y);
	}
}

int dfn[maxn], low[maxn], ind;
bool ins[maxn];
int sta[maxn], top;
int bel[maxn], cnt;

int val[maxn];

void Tarjan(int x) {
	dfn[x] = low[x] = ++ind, ins[x] = true, sta[++top] = x;
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(!dfn[y]) {
			Tarjan(y); low[x] = min(low[x], low[y]);
		}
		else {
			if(ins[y]) low[x] = min(low[x], dfn[y]);
//			else low[x] = min(low[x], dfn[y]);
		}
	}
	if(low[x] == dfn[x]) {
		++cnt;
		while(sta[top] != x) {
			bel[sta[top]] = cnt, ins[sta[top]] = false;
			val[cnt] += a[sta[top]];
			--top;
		}
		--top;
		bel[x] = cnt, ins[x] = false;
		val[cnt] += a[x];
	}
}

#define pii(x, y) make_pair(x, y)

vector <int> v[maxn];
set < pair < int, int> > st;
int deg[maxn];

void DAG(void) {
	for(int i = 1; i <= tot; ++i) {
		int x = fr[i], y = to[i];
		x = bel[x], y = bel[y];
		if(x == y) continue;
		if(st.find(pii(x, y)) != st.end()) continue;
		st.insert(pii(x, y)); v[x].push_back(y);
		deg[y]++;
	}
}

#undef pii(x, y)

void debug(void) {
	printf("cnt : %d\n", cnt);
	for(int i = 1; i <= cnt; i++) {
		printf("%d : ", i);
		for(auto x : v[i]) {
			printf("%d ", x);
		}
		puts("");
	}
}

int opt[maxn];

void Dynamic_Programming(void) {
	queue <int> q;
	for(int i = 1; i <= cnt; i++) {
		if(deg[i] == 0) {
			opt[i] = val[i]; q.push(i);
		}
	}
	while(q.size()) {
		int x = q.front(); q.pop();
		for(auto y : v[x]){
			if((--deg[y]) == 0) q.push(y);
			opt[y] = max(opt[y], opt[x] + val[y]);
		}
	}
}

void Work(void) {
	for(int i = 1; i <= n; ++i) {
		if(!dfn[i]) Tarjan(i);
	}
	DAG(); //debug();
	Dynamic_Programming();
	int ans = -1;
	for(int i = 1; i <= cnt; i++) ans = max(ans, opt[i]);
	printf("%d\n", ans);
}

signed main(void) {
	Init();
	Work();
	return 0;
}
