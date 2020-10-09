#include<bits/stdc++.h>
using namespace std;
map <string,bool> mp;
int ans,n;
string a;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		if(!mp.count(a))
		{
			ans++;
			mp[a]=1;
		}
	}
	printf("%d\n",ans);
	return 0;
}
