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
const int INF = 0x3f3f3f3f;

int n, m;
int val[10000000], lfc[10000000], rgc[10000000], cnt;
int rt[maxn];

int New() {
	val[++cnt] = 0;
	lfc[cnt] = rgc[cnt] = 0;
	return cnt;
}

int query(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) return val[x];
	if(r < L || R < l) return -INF;
	int res = 0;
	int mid = (l + r) >> 1;
	if(lfc[x]) res = max(res, query(lfc[x], l, mid, L, R));
	if(rgc[x]) res = max(res, query(rgc[x], mid + 1, r, L, R));
	return res;
}

void modify(int x, int l, int r, int pos, int need) {
	if(l == r) {
		val[x] = need;
		return ;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) {
		if(!lfc[x]) lfc[x] = New();
		modify(lfc[x], l, mid, pos, need);
	}
	else {
		if(!rgc[x]) rgc[x] = New();
		modify(rgc[x], mid + 1, r, pos, need);
	}
	if(lfc[x]) val[x] = max(val[x], val[lfc[x]]);
	if(rgc[x]) val[x] = max(val[x], val[rgc[x]]);
}

void Init(void) {
	read(n); read(m);
	for(int i = 1; i <= n; i++) {
		rt[i] = New();
	}
	for(int i = 1, x, y, z; i <= m; i++) {
		read(x); read(y); read(z);
		int res;
		if(z >= 1) res = query(rt[x], 0, 100000, 0, z - 1);
		else res = 0;
		modify(rt[y], 0, 100000, z, res + 1);
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		ans = max(ans, query(rt[i], 0, 100000, 0, 100000));
	}
	printf("%d\n", ans);
}

void Work(void) {

}

signed main(void) {
	Init();
	Work();
	return 0;
}
