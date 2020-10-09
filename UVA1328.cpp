#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int cas,len,Next[1000007];
char w[1000007];
void getNext()
{
	int k=0;
	for(int i=2;i<=len;i++)
	{
		while(k&&w[k+1]!=w[i]) k=Next[k];
		if(w[k+1]==w[i]) k++;
		Next[i]=k;
	}
}
int main()
{
	while(cin>>len&&len)
	{
		cas++;
		cin>>w+1;
		memset(Next,0,sizeof(Next));
		getNext();
		printf("Test case #%d\n",cas);
		for(register int i=1;i<=len;i++)
		{
			if(Next[i]&&i%(i-Next[i])==0)
			{
				printf("%d %d\n",i,i/(i-Next[i]));
			}
		}
		printf("\n");
	}
}
