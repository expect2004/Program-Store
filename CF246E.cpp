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
const int maxm = 200000 + 7;
int Head[maxn], Next[maxm], to[maxm], tot, a[maxn], ind, ans[maxn];
void addedge(int x, int y) {
	to[++tot] = y, Next[tot] = Head[x], Head[x] = tot;
}
void add(int x, int y) {
	addedge(x, y); addedge(y, x);
}
map < string, int > mp;
int n, T;
//struct BIT {
//	#define lowbit(x) (x & (-x))
//	int c[maxn], n;
//	void classify(int x) {n = x;}
//	void add(int pos, int need) {
//		while(pos <= n) {
//			c[pos] += need, pos += lowbit(pos);
//		}
//	}
//	int query(int pos) {
//		int res = 0;
//		while(pos) {
//			res += c[pos], pos -= lowbit(pos);
//		}
//		return res;
//	}
//	#undef lowbit(x)
//}T;
struct Question {
	int id, dep;
};
vector < Question > v[maxn];

int size[maxn], dep[maxn], dfn[maxn], son[maxn], cnt, Pre[maxn];

void dfs1(int x, int f, int dp) {
	size[x] = 1, dep[x] = dp, dfn[x] = ++cnt, Pre[cnt] = x;
	int mx = -1;
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i]; if(y == f) continue;
		dfs1(y, x, dp + 1); size[x] += size[y];
		if(size[y] > mx) mx = size[y], son[x] = y;
	}
}

int curr[maxn];

map < pair < int, int >, int > has;

//map < int, int > H[maxn];

void Add(int x, int opt) {
	int L1 = dfn[x], R2 = dfn[x] + size[x] - 1;
	int L2, R1;
	if(!son[x] || opt == -1) R1 = R2, R2 = 0, L2 = 1;
	else R1 = dfn[son[x]] - 1, L2 = dfn[son[x]] + size[son[x]];
	for(int i = L1; i <= R1; i++) {
		has[make_pair(a[Pre[i]],dep[Pre[i]])] += opt;
		if((has[make_pair(a[Pre[i]],dep[Pre[i]])] == 1 && opt == 1) || (has[make_pair(a[Pre[i]],dep[Pre[i]])] == 0 && opt == -1)) {
			curr[dep[Pre[i]]] += opt;
		}
	}
	for(int i = L2; i <= R2; i++) {
		has[make_pair(a[Pre[i]],dep[Pre[i]])] += opt;
		if((has[make_pair(a[Pre[i]],dep[Pre[i]])] == 1 && opt == 1) || (has[make_pair(a[Pre[i]],dep[Pre[i]])] == 0 && opt == -1)) {
			curr[dep[Pre[i]]] += opt;
		}
	}
}

void dfs2(int x, int f, bool op) {
	for(int i = Head[x]; i; i = Next[i]) {
		int y = to[i];
		if(y == f || y == son[x]) continue;
		dfs2(y, x, false);
	}
	if(son[x]) dfs2(son[x], x, true);
	Add(x, 1);
	for(auto p : v[x]) {
		int id = p.id, dp = p.dep + dep[x];
		if(dp > n + 1) ans[id] = 0;
		else ans[id] = curr[dp];
	}
	if(op == false) Add(x, -1);
} 

vector < int > rt;

void Init(void) {
	ios::sync_with_stdio(false);
	cin.tie(0); cin >> n;
	string s;
	for(int i = 1, p; i <= n; i++) {
		cin >> s >> p;
		if(p) add(i, p);
		else rt.push_back(i);
		if(mp[s] == 0) mp[s] = ++ind;
		a[i] = mp[s];
	}
	for(auto x : rt) add(x, n + 1);
	cin >> T;
	for(int i = 1, x, y; i <= T; i++) {
		cin >> x >> y;
		v[x].push_back((Question){i, y});
	}
}

void Work(void) {
	dfs1(n + 1, 0, 1);
//	for(auto x : rt) {
		dfs2(n + 1, 0, true);
//		Add(x, -1);
//	}
	for(int i = 1; i <= T; i++) cout << ans[i] << endl;
}

signed main(void) {
	Init();
	Work();
	return 0;
}
