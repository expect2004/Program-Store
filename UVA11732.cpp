#include<bits/stdc++.h>
#define maxn 4000010
#define size 63
using namespace std;
 
int ch[maxn][size];
int val[maxn],sz;
int fa[maxn];

void init(){
    memset(ch[0],0,sizeof(ch[0]));
    val[0]=0;
    sz=1;
}

int idx(char c){
    if(!c) return c;
    else if('a'<=c&&c<='z') return c-'a'+1;
    else if('A'<=c&&c<='Z') return c-'A'+27;
    else return c-'0'+53;
}

void insert(char* s){
    int u=0;
    for(int i=0;;i++){
        val[u]++;
        if(s[i]==-1) break;
        int id=idx(s[i]);
        if(!ch[u][id]){
            memset(ch[sz],0,sizeof(ch[sz]));
            val[sz]=0;
            ch[u][id]=sz++;
        }
        fa[ch[u][id]]=u;
        u=ch[u][id];
    }
}
 
int N;
char str[1010];
int kase;
long long ans;
 
void dfs(int u){
    if(u){
        ans+=1ll*(val[fa[u]]-val[u])*val[u];
        ans+=2ll*val[u]*(val[u]-1);
    }
    for(int i=0;i<size;i++)
        if(ch[u][i]) dfs(ch[u][i]);
}
 
int main(){
    while(scanf("%d",&N)==1&&N){
        init();
        while(N--){
            scanf("%s",str);
            int l=strlen(str);
            str[l+1]=-1;
            insert(str);
        }
        printf("Case %d: ",++kase);
        ans=0; dfs(0);
        printf("%lld\n",ans/2);
    }
    return 0;
}//
