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
	for(int i=0;i<n;i++)v[i]={arrival[i],burst[i]};
	sort(v,v+n);
	
	int wt[n],turn[n];
	int i=0;
	multiset<pair<int,int>>s;
	int j=0;
	while(i!=n){
		while(j<n && v[j].first<=time){
			s.insert({v[j].second,v[j].first});
			j++;
		}
		if(s.empty()){
			time=v[j].first;
			continue;
		}
		wt[i]=time-s.begin()->second;
		time+=s.begin()->first;
		turn[i]=wt[i]+s.begin()->first;
		s.erase(s.begin());
		i++;
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
