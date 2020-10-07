/*
Offical Template
Bellman_Ford for minus-circled
Date : 2020 - 10 - 6
Author : expect2004
Problem id : Luogu3385
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

const int maxn = 2000 + 7;
const int maxm = 6000 + 7;

int T, n, m;
int Head[maxn], to[maxm], Next[maxm], w[maxm], tot;
int cnt[maxn], dis[maxn];

void Reset(void) {
	tot = 0;
	memset(Next, 0, sizeof(Next));
	memset(Head, 0, sizeof(Head));
	memset(cnt, 0, sizeof(cnt));
}

void add(int x, int y, int z) {
	to[++tot] = y, Next[tot] = Head[x], Head[x] = tot, w[tot] = z;
}

void Init(void) {
	read(n); read(m);
	for(int i = 1, x, y, z; i <= m; ++i) {
		read(x); read(y); read(z);
		if(z >= 0) {
			add(x, y, z); add(y, x, z);
		}
		else add(x, y, z);
	}
}

bool inq[maxn];

bool Bellman_Ford(void) {
	queue <int> q; memset(dis, 0x3f, sizeof(dis)); memset(inq, false, sizeof(inq));
	q.push(1); inq[1] = true; cnt[1] = 1; dis[1] = 0;
	while(!q.empty()) {
		int x = q.front(); q.pop(); inq[x] = false;
		for(int i = Head[x]; i; i = Next[i]) {
			int y = to[i];
			if(dis[y] > dis[x] + w[i]) {
				dis[y] = dis[x] + w[i];
				if(inq[y] == false) {
					q.push(y);
					inq[y] = true, ++cnt[y];
					if(cnt[y] > n) return false;
				}
			}
		}
	}
	return true;
}

void Work(void) {
	bool succ = Bellman_Ford();
	if(succ) puts("NO");
	else puts("YES");
}

signed main(void) {
	read(T);
	while(T--) {
		Reset();
		Init();
		Work();
	}
	return 0;
}
