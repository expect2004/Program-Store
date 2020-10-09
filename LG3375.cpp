#include<bits/stdc++.h>
using namespace std;

template <typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh;
	while(ch!='-'&&(ch>'9'||ch<'0')) ch=getchar();
	if(ch=='-') ch=getchar(),fh=-1;
	else fh=1;
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	x*=fh;
}

const int maxn=1000007;

char s[maxn],t[maxn];
int ls,lt;

int fail[maxn];

void Getfail(){
	for(int i=2,j=0;i<=lt;i++){
		while(j&&t[i]!=t[j+1]) j=fail[j];
		if(t[i]==t[j+1]) ++j;
		fail[i]=j;
	}
}

void Work(){
	for(int i=1,j=0;i<=ls;i++){
		while(j&&t[j+1]!=s[i]) j=fail[j];
		if(t[j+1]==s[i]) ++j;
		if(j==lt){
			printf("%d\n",i-lt+1);
			j=fail[j];
		}
	}
	for(int i=1;i<=lt;i++) printf("%d%c",fail[i]," \n"[i==lt]);
}

int main(){
	scanf("%s",s+1);scanf("%s",t+1);
	ls=strlen(s+1),lt=strlen(t+1);
	Getfail();Work();
	return 0;
}
