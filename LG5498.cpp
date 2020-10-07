// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
#define mod 100000007
#define maxn 1000003
int n,m,l,r;
long long x,fm,ans;
long long s[maxn],inv[maxn];
long long ss[maxn],invs[maxn],sinvs[maxn];
template<typename Tp>
void read(Tp &x){
	x=0;int fh;char ch=1;
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-'){
		ch=getchar();fh=-1;
	}
	else fh=1;
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	x*=fh;
}

long long ksm(long long x,int p){
	long long re=1;
	while(p){
		if(p&1) re=re*x%mod;p>>=1;
		x=x*x%mod;
	}
	return re;
}

int main(){
	read(n);read(m);inv[0]=1;s[0]=1;
	for(register int i=1;i<=n;i++){
		read(x);
		s[i]=s[i-1]*x%mod;
		inv[i]=ksm(s[i],mod-2);
	}
	for(register int i=1;i<=n;i++){
		ss[i]=(ss[i-1]+s[i])%mod;
		invs[i]=(invs[i-1]+inv[i-1])%mod;
	}
	for(register int i=1;i<=n;i++){
		sinvs[i]=(sinvs[i-1]+ss[i-1]*inv[i-1]%mod)%mod;
	}
	while(m--){
		ans=0;
		read(l);read(r);fm=(long long)(r-l+1)*(r-l+2)/2;
		ans=ss[r]*(invs[r]-invs[l-1])%mod;
		ans=((ans-sinvs[r]+sinvs[l-1])%mod+mod)%mod;
		ans=ans*ksm(fm,mod-2)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}

