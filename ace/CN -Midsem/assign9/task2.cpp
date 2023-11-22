#include<bits/stdc++.h>
using namespace std;

int main(){
int t;
cin>>t;
while(t--){
	int cap;cin>>cap;
	int q;cin>>q;
	
	int recent=-1;
	map<int,int>m;
	vector<int>ans;
	for(int i=0;i<q;i++){
		char c;
		cin>>c;
		if(c=='S'){
			int x,y;
			cin>>x>>y;
			if(m.count(x)!=0)m[x]=y;
			else{
				if(m.size()==cap){
					m.erase(recent);
				}
				m[x]=y;
			}
			recent=x;
		}
		else{
			int x;cin>>x;
			if(m.count(x)==0) ans.push_back(-1);
			else{
				ans.push_back(m[x]);
				recent=x;
			}
		
		}
	}
	for(auto ele : ans){
		cout<<ele<<endl;
	}
}
return 0;
}
