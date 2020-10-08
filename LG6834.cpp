#include<bits/stdc++.h>
using namespace std;

#define int long long

template < typename Tp >
void read(Tp &x) {
	x = 0; int fh = 1; char ch = 1;
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= fh;
}

const int mod = 998244353;
const int maxn = 1000000 + 7;

int n, k;
int a[maxn], b[maxn];
int s[maxn]; 

int lowbit(int x) {
	return x & (-x);
}

struct BIT { 
	int c[maxn], N;
	void build(int x) {N = x;}
	void add(int pos, int k) {
		for(int i = pos; i <= N; i += lowbit(i)) c[i] = ((c[i] + k) % mod + mod) % mod;
	}
	int query(int x) {
		int res = 0;
		while(x) {
			res = (res + c[x]) % mod;
			x -= lowbit(x);
		}
		return res;
	}
}T, T1;

void Init(void) {
	read(n); read(k);
	for(int i = 1; i <= n; i++) {
		read(a[i]);
		s[i] = s[i - 1] + a[i];
	}
}

int fpow(int x, int p){
	int res = 1;
	while(p) {
		if(p & 1) res = res * x % mod;
		x = x * x % mod; p >>= 1;
	}
	return res;
}

void Work(void) {
	int ans = 0;
	for(int i = 1; i <= n; i++) b[i] = a[i];
	sort(b + 1, b + n + 1);
	int M; M = unique(b + 1, b + n + 1) - b - 1;
	T.build(M), T1.build(M);
	for(int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + M + 1, a[i]) - b;
	for(int i = 1; i <= n; i++) {
		T.add(a[i], b[a[i]]); T1.add(a[i], 1);
//		printf("%lld : IN\n", i);
		int st;
		if(i - k - 1 >= 1) {
			T.add(a[i - k - 1], -b[a[i - k - 1]]);
			T1.add(a[i - k - 1], -1);
//			printf("%lld : OUT\n", i-k-1);
		}
		st=max(1ll, i - k);
		int p = i - st;
		int sum = T.query(a[i]), sour = T1.query(a[i]);
		sum = ((-sum + sour * b[a[i]] % mod) % mod + mod) % mod;
		sum = sum * fpow(p, mod - 2) % mod;
		ans = (ans + sum) % mod;
//		for(int j = st; j < i; j++) {
//			ans = (ans + (max(0ll, a[i] - a[j]) * fpow(p, mod - 2) % mod) % mod) % mod;
//		}
	}
	ans = (ans + b[a[1]]) % mod;
	printf("%lld\n", ans);
}

signed main(void) {
	Init();
	Work();
	return 0;
}
