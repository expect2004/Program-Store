#include<bits/stdc++.h>
using namespace std;

template <typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh;
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-'){
		fh=-1;ch=getchar();
	}
	else fh=1;
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	x*=fh;
}

string s,t;
int n,opt[301000],m;

int ch[400003][26],tot,root=1;
int ed[400003];

const int mod=20071027;

int chk(char s){
	return s-'a'+1;
}

void insert(){
	int len=t.size(),p=root;
	for(int i=0;i<len;i++){
		int k=chk(t[i]);
		if(!ch[p][k]) ch[p][k]=++tot;
		p=ch[p][k];
	}
	++ed[p];
}

void query(int x){
	int p=root,y=x+1,cnt=0;
	while(p){
		if(ed[p]){
			opt[x+cnt]=(opt[x]+opt[x+cnt])%mod;
		}
		int k=chk(s[x+cnt]);
		++cnt;p=ch[p][k];
	}
}

int testcase;

void solve(){
	memset(opt,0,sizeof(opt));opt[0]=1;
	memset(ch,0,sizeof(ch));tot=1;memset(ed,0,sizeof(ed));
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>t;
		insert();
	}
	for(int i=0;i<s.size();i++){
		query(i);
	}
	cout<<"Case "<<testcase<<": "<<opt[s.size()]<<endl;
}

int main(){
	ios::sync_with_stdio(false);
	while(1){
		s="";cin>>s;++testcase;
		if(!s.size()) break;
		solve();
	}
	return 0;
}
