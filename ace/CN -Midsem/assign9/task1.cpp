#include<bits/stdc++.h>
using namespace std;


void func(vector<vector<int>>&ans,vector<int>&ds,vector<bool>&vis,vector<vector<int>>&need,vector<vector<int>>&alloc,vector<int>&avail,int n){
	if(ds.size()==n){
		ans.push_back(ds);
		return;
	}
	
	for(int i=0;i<n;i++){
		if(!vis[i]){
			int flag = 0;
			for (int j = 0; j < 3; j++) {
			  if (need[i][j] > avail[j]){
			    flag = 1;
			    break;
			  }
			}
			if(flag == 0){
				vis[i]=true;
				ds.push_back(i);
				for (int y = 0; y < 3; y++)
				    avail[y] += alloc[i][y];
				func(ans,ds,vis,need,alloc,avail,n);
				for (int y = 0; y < 3; y++)
				    avail[y] -= alloc[i][y];
				ds.pop_back();
				vis[i]=false;
			}
		}
	}
}

int main(){

int t;
cin>>t;
while(t--){
	int n;
	cin>>n;
	vector<int>avail(3,0);
	for(int i=0;i<3;i++){
		cin>>avail[i];
	}
	
	vector<vector<int>>alloc(n,vector<int>(3)),max(n,vector<int>(3)),need(n,vector<int>(3));
	
	for(int i=0;i<n;i++){
		for(int j=0;j<3;j++){
			cin>>alloc[i][j];		
		}
		for(int j=0;j<3;j++){
			cin>>max[i][j];		
		}	
	}
	  
	  for (int i = 0; i < n; i++) {
	    for (int j = 0; j < 3; j++)
	      need[i][j] = max[i][j] - alloc[i][j];
	  }
	  
	 vector<vector<int>>ans;
	 vector<int>ds;
	 vector<bool>vis(n,false);
	 func(ans,ds,vis,need,alloc,avail,n);
	 
	 if(ans.size()==0) cout<<-1<<endl;
	 
	 for(int i=0;i<ans.size();i++){
	 	for(int j=0;j<n;j++){
	 		cout<<ans[i][j]<<" ";
	 	}
	 	cout<<endl;
	 }
}
return 0;
}
