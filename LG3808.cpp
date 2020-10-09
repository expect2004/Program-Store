#include<bits/stdc++.h>
using namespace std;


template <typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh;
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-') {
		ch=getchar();fh=-1;
	}
	else fh=1;
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	x*=fh;
}

int tot,ch[1000007][26];
int ed[1000007],root;
string s;
int fail[1000007];

int n;

int chk(char s){
	return s-'a';
}

void insert(){
	int siz=s.size(),p=root;
	for(int i=0;i<siz;i++){
		if(!ch[p][chk(s[i])]) ch[p][chk(s[i])]=++tot;
		p=ch[p][chk(s[i])];
	}
	ed[p]++;
}

void pre(){
	queue<int>q;
	for(int i=0;i<26;i++){
		if(!ch[root][i]) continue;
		fail[ch[root][i]]=0;q.push(ch[root][i]);
	}
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=0;i<26;i++){
			if(ch[x][i]) fail[ch[x][i]]=ch[fail[x]][i],q.push(ch[x][i]);
			else ch[x][i]=ch[fail[x]][i];
		}
	}
}

void query(){
	int siz=s.size(),ans=0,p=root;
	for(int i=0;i<siz;i++){
		p=ch[p][chk(s[i])];
		for(int j=p;j&&ed[j]!=-1;j=fail[j]){
			ans+=ed[j];ed[j]=-1;
		}
	}
	printf("%d\n",ans);
}

int main(){
	read(n);
	for(register int i=1;i<=n;i++){
		cin>>s;insert();
	}
	pre();cin>>s;
	query();
	return 0;
}
