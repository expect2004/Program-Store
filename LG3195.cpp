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

template < typename Tp >
void biread(Tp &x) {
	x = 0; int fh = 1; char ch = 1;
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 2 + ch - '0', ch = getchar();
	x *= fh;
}

const int maxn = 50000 + 7;
int n, L, c[maxn];
double s[maxn];
double dp[maxn];
int que[maxn], f, r;

inline double a(int i) {return i + s[i];}
inline double b(int i) {return i + s[i] + L + 1;}
inline double Y(int i) {return dp[i] + b(i) * b(i);}
inline double X(int i) {return b(i);}
inline double K(int x, int y) {return (double)(Y(y) - Y(x)) / (double)((X(y) - X(x)));}

void Init(void) {
	read(n); read(L);
	for(int i = 1; i <= n; i++) {
		read(c[i]); s[i] = s[i - 1] + c[i];
	}
}

void Work(void) {
	f = r = 1;
	for(int i = 1; i <= n; i++) {
		while(f < r && K(que[f], que[f + 1]) < 2 * a(i)) f++;
		int j = que[f];
		dp[i] = dp[j] + (a(i) - b(j)) * (a(i) - b(j));
		while(f < r && K(que[r - 1], que[r]) > K(que[r - 1], i)) r--;
		que[++r] = i;
	}
	printf("%lld\n", (int)dp[n]);
}

signed main(void) {
	Init();
	Work();
	return 0;
}

