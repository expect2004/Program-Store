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

int T;
map < string, int > mp;

void Init(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
}

void Work(void) {
	while(T--) {
		string s;
		cin >> s;
		if(mp[s] == 1) cout << "YES\n";
		else {
			cout << "NO\n";
			mp[s] = 1;
		}
	}
}

signed main(void) {
	Init();
	Work();
	return 0;
}

