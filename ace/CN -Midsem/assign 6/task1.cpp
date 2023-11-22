#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin>>n;
	int burst[n],arrival[n];
	for(int i=0;i<n;i++) cin>>burst[i];
	for(int i=0;i<n;i++) cin>>arrival[i];
	
	pair<int,int>v[n];
	for(int i=0;i<n;i++) v[i]={arrival[i],i};
	sort(v,v+n);//sorting the processes acoording to arrival time
	int wt[n],turn[n];
	wt[0]=v[0].first;
	//waiting time= response time- arrival time;
	for(int i=1;i<n;i++){
		
		wt[i]=max(wt[i-1]+burst[v[i-1].second],v[i].first);
	}
	for(int i=0;i<n;i++) wt[i]-=v[i].first;
	//turn around time=waiting time + burst time;
	for(int i=0;i<n;i++) turn[i]=wt[i]+v[i].second;
	
	double avg_wait=0.0;
	double avg_turn=0.0;
	for(int i=0;i<n;i++){
		avg_wait+=wt[i];
		avg_turn+=turn[i];
	}
	
	cout<<"Average waiting time : "<<(avg_wait*1.0)/(n*1.0)<<endl;
	cout<<"Average turnaround time : "<<(avg_turn*1.0)/(n*1.0)<<endl;
}
