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

int n, S;
struct node{
	int a, b;
}r[maxn];
int c[maxn];

void Init(void) {
	read(n);
	for(int i = 1; i <= n; i++) {
		read(r[i].a); S += r[i].a;
	}
	for(int i = 1; i <= n; i++) {
		read(r[i].b); c[i] = r[i].b;
	}
}

int ppos, ans;
int dp[103][10003];

bool comp(node a, node b) {
	return a.b > b.b;
}

void Work(void) {
	int s = 0;
	sort(c + 1, c + n + 1, greater<int>());
	for(int i = 1; i <= n; i++) {
		s += c[i]; if(s >= S) {
			ans = i; break;
		}
	}
	sort(r + 1, r + n + 1, comp);
	printf("%d ", ans);
	memset(dp, 255, sizeof(dp));
	dp[0][0] = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = s; j >= r[i].b; j--) {
			for(int k = 1; k <= ans; k++){
				if(dp[k - 1][j - r[i].b] >= 0) dp[k][j] = max(dp[k][j], dp[k - 1][j - r[i].b] + r[i].a);
			}
		}
	}
	int cost = 0;
	for(int i = S; i <= s; i++) {
		cost = max(cost, dp[ans][i]);
	}
	printf("%d\n", S - cost);
}

signed main(void) {
	Init();
	Work();
	return 0;
}

