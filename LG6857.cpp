#include<bits/stdc++.h>
using namespace std;

template < typename Tp >
inline void read(Tp &x) {
	x = 0; int fh = 1; char ch = 1;
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') fh = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= fh;
}

int T;
long long n;

int main(void) {
    read(T);
    while(T--) {
        read(n);
        // scanf("%lld", &n);
        if(n & 1) printf("%lld\n", n * (n - 1) >> 1);
        else printf("%lld\n", (n * (n - 2) >> 1) + 1);
    }
    return 0;
}
