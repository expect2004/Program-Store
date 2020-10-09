#include <bits/stdc++.h>
    
using namespace std;
    
int max(int a,int b,int c){
 	long long testa = 1LL * a * c;
  	long long testb = 1LL * b * c;
  	if(testa > testb)
   		return a;
   	return b;
}
     
int main(){
    
  	ios_base::sync_with_stdio(0);
   	cin.tie(0);
    
   	int p,q,r,n;
   	cin  >> n >> p >> q >> r;
    
   	std::vector<int> v(n);
   	for(int i = 0;i < n;i++){
   		cin >> v[i];
   	}
    
   	if(n == 1){
   		cout << 1LL * (0LL + p + q + r) * v[0] << '\n';
   		return 0;
   	}
    
   	std::vector<int> MaxR(n);
   	MaxR.back() = v.back();
   	for(int i = n - 2;i >= 0;i--){
   		MaxR[i] = max(MaxR[i + 1],v[i],r);
   		// cerr << MaxR[i] << ' ';
   	}
   	// cerr << '\n';
    
   	int MaxI = v[0];
   	long long sol = -5e18;
   	for(int i = 0;i < n;i++){
   		MaxI = max(MaxI,v[i],p);
   		sol = max(sol,1LL * p * MaxI + 1LL * v[i] * q + 1LL * MaxR[i] * r);
   	}
    
   	cout << sol << '\n';
    
   	return 0;
}
