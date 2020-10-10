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

int n, T, ans[maxn];
int Head[maxn], to[maxm], Next[maxm], tot;
char a[maxn];

struct Question {
	int id, dp;
};
vector < Question > q[maxn];
void addedge(int x, int y) {
	to[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void add(int x, int y) {
	addedge(x, y); addedge(y, x);
}

void Init(void) {
	read(n); read(T);
	for(int i = 2, x; i <= n; i++) {
		read(x);
		add(x, i);
	}
	scanf("%s", a + 1);
	for(int i = 1, x, y; i <= T; i++) {
		read(x); read(y);
		q[x].push_back((Question){i, y});
	}
}

int size[maxn], son[maxn], dfn[maxn], ind, Pre[maxn];
int dep[maxn];
void dfs1(int x, int f, int dp) {
	size[x] = 1, dep[x] = dp; int mx = -1; dfn[x] = ++ind;
	Pre[ind] = x;
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == f) continue;
		dfs1(y, x, dp + 1); size[x] += size[y];
		if(size[y] > mx) mx = size[y], son[x] = y;
	}
}

int cnt[26][maxn];

void Add(int x, int opt) {
	int L1 = dfn[x], R2 = dfn[x] + size[x] - 1;
	int L2, R1;
	if(!son[x] || opt == -1) R1 = R2, R2 = 0, L2 = 1;
	else R1 = dfn[son[x]] - 1, L2 = dfn[son[x]] + size[son[x]];
	for(int i = L1; i <= R1; i++) {
		cnt[a[Pre[i]] - 'a'][dep[Pre[i]]] += opt;
	}
	for(int i = L2; i <= R2; i++) {
		cnt[a[Pre[i]] - 'a'][dep[Pre[i]]] += opt;
	}
}

void dfs2(int x, int f, bool op) {
	for(int i = Head[x] ; i; i = Next[i]) {
		int y = to[i];
		if(y == f || y == son[x]) continue;
		dfs2(y, x, false);
	}
	if(son[x]) dfs2(son[x], x, true);
	Add(x, 1);
	for(auto p : q[x]) {
		int id = p.id, dp = p.dp;
		int curr = 0;
		for(int i = 0; i < 26; i++) {
			if(cnt[i][dp] & 1) ++curr;
		}
		if(curr > 1) ans[id] = 1;
		else ans[id] = 2;
	}
	if(op == false) Add(x, -1);
}

void Work(void) {
	dfs1(1, 0, 1);
	dfs2(1, 0, true);
	for(int i = 1; i <= T; i++) {
		puts(ans[i] == 1 ? "No" : "Yes");
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}

