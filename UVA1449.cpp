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

int n;
string sb[157],s;
int tot,ch[170000][36];
int fail[170000],ed[170000];
int root;

int chk(char s){
	return s-'a';
}

struct node{
	int id,ans;
}fafa[157];

void insert(int q){
	int siz=s.size(),p=root;
	for(int i=0;i<siz;i++){
		if(!ch[p][chk(s[i])]) ch[p][chk(s[i])]=++tot;
		p=ch[p][chk(s[i])];
	}
	ed[p]=q;
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
		for(int j=p;j;j=fail[j]){
			fafa[ed[j]].ans++;//ed[j]=0;
			//fafa[j].ans++;ed[j]=-1;
		}
	}
}

void Reset(){
	memset(fafa,0,sizeof(fafa));
	memset(ch,0,sizeof(ch));
	memset(fail,0,sizeof(fail));
	memset(ed,0,sizeof(ed));
	tot=0;
}

bool comp(node a,node b){
	return a.ans==b.ans?a.id<b.id:a.ans>b.ans;
}

int main(){
	while(1){
		read(n);if(!n) return 0;
		Reset();
		for(register int i=1;i<=n;i++){
			cin>>s;sb[i]=s;insert(i);
			fafa[i].id=i;
		}
		pre();
		cin>>s;query();
		sort(fafa+1,fafa+n+1,comp);
		printf("%d\n",fafa[1].ans);
		cout<<sb[fafa[1].id]<<endl;
		for(register int i=2;i<=n;i++){
			if(fafa[i].ans==fafa[i-1].ans) cout<<sb[fafa[i].id]<<endl;
			else break;
		}
	}
	return 0;
}//
