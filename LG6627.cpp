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

const int maxn = 400000 + 7;
const int INFa = 1000000000;

int n, m;
int a[maxn], cnt, b[maxn];
int opt[maxn], l[maxn], r[maxn], w[maxn];
int s[maxn];

void Init(void) {
	a[++cnt] = -INFa - 1, a[++cnt] = INFa + 1, a[++cnt] = 0;
	read(n);
	for(int i = 1, op; i <= n; i++) {
		read(op); opt[i] = op;
		if(op == 1) {
			int L, R;
			read(L); read(R);
			l[i] = L, r[i] = R;
			a[++cnt] = L, a[++cnt] = R, a[++cnt] = R + 1, a[++cnt] = L - 1;
		}
		else {
			read(l[i]); a[++cnt] = l[i]; a[++cnt] = l[i] - 1, a[++cnt] = l[i] + 1;
		}
		read(w[i]);
	}
}

int zer;

void Preprocess(void) {
	memcpy(b, a, sizeof(a));
	sort(a + 1, a + cnt + 1);
	sort(b + 1, b + cnt + 1);
	m = unique(a + 1, a + cnt + 1) - a - 1;
	for(int i = 1; i <= n; i++) {
		if(opt[i] == 1) {
			l[i] = lower_bound(a + 1, a + m + 1, l[i]) - a;
			r[i] = lower_bound(a + 1, a + m + 1, r[i]) - a;
		}
		else l[i] = lower_bound(a + 1, a + m + 1, l[i]) - a;
	}
	zer = lower_bound(a + 1, a + n + 1, 0) - a;
}

void Work(void) {
	Preprocess();
	for(int i = 1; i <= n; i++) {
		if(opt[i] == 1) {
			s[l[i]] ^= w[i];
			s[r[i] + 1] ^=w[i];
		}
		else if(opt[i] == 2) {
			s[l[i]] ^= w[i]; s[l[i] + 1] ^= w[i];
		}
		else s[1] ^= w[i], s[l[i]] ^= w[i], s[l[i] + 1] ^= w[i], s[m] ^= w[i];
	}
	int ans = -1, curr = 0/*, posl = 1, posr = 1*/, ppos= INFa, ansp;
//	vector <int> vl, vr;
	for(int i = 1; i <= m; i++) {
		curr ^= s[i];
		if(curr > ans) {
//			vl.push_back(posl); vr.push_back(posr);
			ans = curr;
			ansp = a[i], ppos = abs(a[i]);
			// posl = posr = i;
//			ansp = a[i]
		}
		if(curr == ans) {
			int opq = abs(a[i]);
			if(opq <= ppos) ansp = a[i], ppos = opq;
		}
//		if(s[i] == 0) ++posr;
	}
//	int ppp = 0, pp = INFa;
//	vl.push_back(posl); vr.push_back(posr);
	printf("%lld %lld\n", ans, ansp);
//	for(int i = 0; i < (int)vl.size(); i++) {
//		int L = vl[i], R = vr[i];
//		L = a[L], R = a[R];
//		if(R <= 0) {
//			if(-R < pp) {
//				pp = -R, ppp = R;
//			}
//		}
//		else if(L >= 0) {
//			if(L < pp) {
//				pp = ppp = L;
//			}
//		}
//		else {
//			if(R > -L) {
//				if(-L < pp) pp = -L, ppp = L;
//			}
//			else if(R < pp) pp = R, ppp = R;
//		}
//	}
//	printf("%lld\n", ppp);
}

signed main(void) {
	Init();
	Work();
	return 0;
}

