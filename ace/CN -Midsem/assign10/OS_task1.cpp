#include<bits/stdc++.h>
using namespace std;

int fifo(vector<int>&v,int slots){
    queue<int>q;
    set<int>s;
    int faults=0;
    int n=v.size();
    
    for(int i=0;i<n;i++){
        int page=v[i];
        if(s.empty() == true || s.find(page)==s.end()){
            if(q.size() == slots){
                int x = q.front();
                q.pop();
                s.erase(x);
            }
            q.push(page);
            s.insert(page);
            faults++;
        }
    }
    return faults;
}

int lru(vector<int>&v,int slots){
    set<pair<int,int>>s;
    map<int,int>m;
    int faults=0;
    for(int i=0;i<v.size();i++){
        int page=v[i];
        if(s.empty() == true || m.find(page) == m.end()){
            if(s.size()==slots){
                int x=s.begin()->second;
                s.erase(s.begin());
                m.erase(x);
            }
            s.insert({i,page});
            m[page]=i;
            faults++;
        }
        else{
            s.erase({m[page],page});
            m[page]=i;
            s.insert({i,page});
        }
    }
    return faults;
}

int  main(){
    srand(time(NULL));
    cout<<"enter number of pages : "<<endl;
    int n;cin>>n;
    cout<<"enter number of page frames : "<<endl;
    int x;
    cin>>x;

    vector<int>v;
    for(int i=0;i<n;i++){
        int val=rand()%10;
        v.push_back(val);
    }
    cout<<"Reference String : "<<endl;
    for(int i=0;i<n;i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    
    cout<<"FIFO page faults : "<<fifo(v,x)<<endl; 
    cout<<"LRU page faults : "<<lru(v,x)<<endl; 
}