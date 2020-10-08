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

const int maxn = 100 + 7;
const int maxd = 2000 + 7;

int n;
struct items {
	int t, d, p, id;
}a[maxn];

int dp[maxd];
int mx;

vector <int> v[maxd];

void Init(void) {
	read(n);
	for(int i = 1; i <= n; i++) {
		read(a[i].t); read(a[i].d); read(a[i].p);
		mx = max(mx, a[i].d); a[i].id = i;
	}
}

bool comp(items a, items b) {
	return a.d == b.d ? a.t < b.t : a.d < b.d;
}

void Work(void) {
	sort(a + 1, a + n + 1, comp);
	for(int i = 1; i <= n; i++) {
		for(int j = a[i].d - 1; j >= a[i].t; j--) {
			if(dp[j - a[i].t] + a[i].p > dp[j]) {
				dp[j] = dp[j - a[i].t] + a[i].p;
				v[j] = v[j - a[i].t];
				v[j].push_back(a[i].id);
			}
		}
	}
	int ans = -1, pos;
	for(int i = 0; i <= mx; i++) {
		if(dp[i] > ans) ans = dp[i], pos = i;
	}
	if(ans == -1) {
		printf("0\n0\n\n");
		return ;
	}
	printf("%d\n%d\n", ans, (int)v[pos].size());
	for(auto x : v[pos]) printf("%d%c", x, " \n"[x == v[pos][(int)v[pos].size() - 1]]);
}

signed main(void) {
	Init();
	Work();
	return 0;
}
