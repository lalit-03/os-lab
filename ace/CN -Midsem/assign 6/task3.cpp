#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin>>n;
	int burst[n],arrival[n];
	for(int i=0;i<n;i++) cin>>burst[i];
	for(int i=0;i<n;i++) cin>>arrival[i];
	int time=0;
	
	pair<int,int>v[n];
	for(int i=0;i<n;i++)v[i]={arrival[i],i};
	sort(v,v+n);
	
	int j=0;
	int wt[n],turn[n];
	multiset<pair<int,int>>s;
	int prev=-1;
	int curr=-1;
	int i=0;
	while(i<n){
		while(j<n && v[j].first<=time){
			s.insert({burst[v[j].second],v[j].second});
			j++;
		}
		
		if(s.empty()){
			time++;
			continue;
		}
		int curr=s.begin()->second;
		int t=s.begin()->first;
		if(prev==-1){
			cout<<"Process "<<curr+1<<" starts"<<endl;
		}
		else if(prev!=curr){
			cout<<"process shifts from "<<prev+1<<" to "<<curr+1<<endl;
		}
		prev=curr;
		s.erase(s.begin());
		t--;
		if(t!=0) s.insert({t,curr});
		else{
			turn[i]=time-arrival[curr]+1;
			wt[i]=turn[i]-burst[curr];
			i++;		
		}
		time++;
	}
	
	double avg_wait=0.0;
	double avg_turn=0.0;
	for(int i=0;i<n;i++){
		avg_wait+=wt[i];
		avg_turn+=turn[i];
	}
	cout<<endl;
	
	cout<<"Average waiting time : "<<avg_wait/(n*1.0)<<endl;
	cout<<"Average turnaround time : "<<avg_turn/(n*1.0)<<endl;
	
}
