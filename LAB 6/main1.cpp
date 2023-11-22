#include <bits/stdc++.h>
using namespace std;

//struct defining input of process data
struct process {
    int pid;
    int at;
    int bt;
    int prt;
};

//struct defining result of each algorithm
struct ScheduleResult {
    float avgWt;
    vector<int> ProcessOrder;
    string S_type;
};

//comparator for fcfs
bool FCFScomparator(const vector<int>&a,vector<int>&b)
{
    if(a[1]!=b[1])
    {
        return a[1]<b[1];
    }
    else
    {
        return a[0]<b[0];
    }
}

//comparator for priority(both preemptive and non preemptive)
class ComparePQ
{
public:
    bool operator()(vector<int> below, vector<int> above)
    {
        if (below[3] > above[3])
        {
            return true;
        }
        else if (below[3] == above[3] && below[1] > above[1])
        {
            return true;
        }

        return false;
    }
};

//comparator for SJF(both preemptive and non preemptive)
class comparatorSJF
{
	public:
		bool operator()(vector<int>child,vector<int>parent)
		{
			if(child[1]!=parent[1])
			{
				return child[1]>parent[1];
			}
			else if(child[2]!=parent[2])
			{
				return child[2]>parent[2];
			}
			else
			{
				return child[0]>parent[0];
			}	
		}
};

//comparator for results of different algorithms
bool CompareScheduleResult (ScheduleResult below, ScheduleResult above) {
    return below.avgWt < above.avgWt;
}

//FCFS Scheduling Algorithm
ScheduleResult  FCFS (vector<process> Processes) {
    ScheduleResult answer;
    answer.S_type = "FCFS";
    int time=0;
    int n = Processes.size();
    vector<vector<int>>mp;
    for(int i=0;i<n;i++)
    {
        vector<int>j(3);
        j[0] = Processes[i].pid;
        j[1] = Processes[i].at;
        j[2] = Processes[i].bt;
        mp.push_back(j);
    }

    sort(mp.begin(),mp.end(),FCFScomparator);
    float wt=0;
    time=mp[0][1];
    vector<int>ans;
    for(int i=0;i<n;i++)
    {
        wt+=time-mp[i][1];
        time+=mp[i][2];
        ans.push_back(mp[i][0]);
    }
    answer.avgWt = wt*1.0/n;
    answer.ProcessOrder = ans;

    return answer;

}

//Round Robin Scheduling Algorithm with TQ = 2
ScheduleResult RoundRobin (vector<process> Processes) {
    ScheduleResult answer;
    answer.S_type = "Round Robin";
    int time = 0;
    int n = Processes.size();
    int tq = 2;

    vector<vector<int>> mp;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        vector<int> j(3);
        j[0] = Processes[i].pid;
        j[1] = Processes[i].at;
        j[2] = Processes[i].bt;
        sum += j[2];
        mp.push_back(j);
    }
    queue<vector<int>> pq;
    float tat = 0;
    float wt = tat - sum;
    vector<int> ans;
    for (int i = 0; i < n; i++)
    {
        if (time == mp[i][1])
        {
            pq.push(mp[i]);
        }
    }
    while (1)
    {
        bool a = 1;
        if (ans.size() == n)
            break;
        if (!pq.empty())
        {
            vector<int> t = pq.front();
            pq.pop();
            if (t[2] >= tq)
            {
                t[2] -= tq;
                for (int j = 0; j < tq; j++)
                {
                    time++;
                    for (int i = 0; i < n; i++)
                    {
                        if (time == mp[i][1])
                        {
                            pq.push(mp[i]);
                        }
                    }
                }
            }
            else
            {
                for (int j = 0; j < t[2]; j++)
                {
                    time++;
                    for (int i = 0; i < n; i++)
                    {
                        if (time == mp[i][1])
                        {
                            pq.push(mp[i]);
                        }
                    }
                }
                t[2] -= t[2];
            }
            if (t[2] > 0)
                pq.push(t);
            else
            {
                ans.push_back(t[0]);
                tat += time - t[1];
            }
        }
        else
        {
            time++;
            for (int i = 0; i < n; i++)
            {
                if (time == mp[i][1])
                {
                    pq.push(mp[i]);
                }
            }
        }
    }
    wt += tat;
    answer.avgWt = wt*1.0/n;
    answer.ProcessOrder = ans;

    return answer;

}

//SJF Preemptive Scheduling Algorithm
ScheduleResult SJFP (vector<process> Processes) {
    ScheduleResult answer;
    answer.S_type = "SJF(Pre-emptive)";
    priority_queue<vector<int>,vector<vector<int>>,comparatorSJF> q;
	int n = Processes.size();
	vector<vector<int>>v(n,vector<int>(3));
	for(int i=0;i<n;i++)
	{
		v[i][0] = Processes[i].pid;
        v[i][2] = Processes[i].at;
        v[i][1] = Processes[i].bt;
	}
	int time=0,fin=0;
	int mem=-1;
	vector<vector<int>>ans(n,vector<int>(4));
	while(fin<n)
	{
		for(int i=0;i<n;i++)
        	{
                	if(time==v[i][2])
			{
				q.push(v[i]);
			}
		}
		vector<int>temp=q.top();
		q.pop();
		temp[1]--;
		if(mem!=temp[0])
		{
			mem=temp[0];
		}
		if(temp[1])
		{
			q.push(temp);
		}
		else
		{
            answer.ProcessOrder.push_back(temp[0]);
			ans[temp[0] - 1][3]=time-v[temp[0] - 1][1]-temp[2]+1;
			fin++;	
		}
		time++;
	}
	float wt=0;
	for(int i=0;i<n;i++)
	{
		wt+=ans[i][3];
	}
	answer.avgWt = wt * 1.0 /n;
    return answer;

}

//SJF Non-preemptive Scheduling Algorithm
ScheduleResult SJFNP (vector<process> Processes) {
    ScheduleResult answer;
    answer.S_type = "SJF(Non Pre-emptive)";
    int time = 0;
    int n = Processes.size();
    vector<vector<int>> mp;
    for (int i = 0; i < n; i++)
    {
        vector<int> j(4);
        j[0] = Processes[i].pid;
        j[1] = Processes[i].at;
        j[2] = Processes[i].bt;
        j[3] = Processes[i].prt;
        mp.push_back(j);
    }
    priority_queue<vector<int>, vector<vector<int>>, comparatorSJF> pq;
    float wt = 0;
    float tat = 0;
    vector<int> ans;
    bool a[n]={0};
    while (1)
    {
        if(ans.size()==n)
            break;
        for(int i=0;i<n;i++)
        {
            if(time>=mp[i][1] && a[i]==0)
            {
                pq.push(mp[i]);
                a[i]=1;
            }
        }
        if(!pq.empty())
        {
            vector<int>t=pq.top();
            wt+=time-t[1];
            time+=t[2];
            ans.push_back(t[0]);
            tat+=time-t[1];
            pq.pop();
        }
        else 
            time++;
    }
    answer.avgWt = wt*1.0/n;
    answer.ProcessOrder = ans;
    return answer;
}

//Priority Preemptive Scheduling Algorithm
ScheduleResult PriorityP (vector<process> Processes) {
    ScheduleResult answer;
    answer.S_type = "Priority(Pre-emptive)";
    priority_queue<vector<int>,vector<vector<int>>, ComparePQ> q;
	int n = Processes.size();
	vector<vector<int>>v(n,vector<int>(4));
	for(int i=0;i<n;i++)
	{
		v[i][0] = Processes[i].pid;
        v[i][2] = Processes[i].at;
        v[i][1] = Processes[i].bt;
        v[i][3] = Processes[i].prt;
	}
	int time=0,fin=0;
	int mem=-1;
	vector<vector<int>>ans(n,vector<int>(4));
	while(fin<n)
	{
		for(int i=0;i<n;i++)
        	{
                	if(time==v[i][2])
			{
				q.push(v[i]);
			}
		}
		vector<int>temp=q.top();
		q.pop();
		temp[1]--;
		if(mem!=temp[0])
		{
			mem=temp[0];
		}
		if(temp[1])
		{
			q.push(temp);
		}
		else
		{
            answer.ProcessOrder.push_back(temp[0]);
			ans[temp[0] - 1][3]=time-v[temp[0] - 1][1]-temp[2]+1;
			fin++;	
		}
		time++;
	}
	float wt=0;
	for(int i=0;i<n;i++)
	{
		wt+=ans[i][3];
	}
	answer.avgWt = wt * 1.0/n;

    return answer;


}

//Priority Non-Preemptive Scheduling Algorithm
ScheduleResult PriorityNP (vector<process> Processes) {
    ScheduleResult answer;
    answer.S_type = "Priority(Non Pre-emptive)";
    int time = 0;
    int n = Processes.size();
    vector<vector<int>> mp;
    for (int i = 0; i < n; i++)
    {
        vector<int> j(4);
        j[0] = Processes[i].pid;
        j[1] = Processes[i].at;
        j[2] = Processes[i].bt;
        j[3] = Processes[i].prt;
        mp.push_back(j);
    }
    priority_queue<vector<int>, vector<vector<int>>, ComparePQ> pq;
    float wt = 0;
    float tat = 0;
    vector<int> ans;
    bool a[n]={0};
    while (1)
    {
        if(ans.size()==n)
            break;
        for(int i=0;i<n;i++)
        {
            if(time>=mp[i][1] && a[i]==0)
            {
                pq.push(mp[i]);
                a[i]=1;
            }
        }
        if(!pq.empty())
        {
            vector<int>t=pq.top();
            wt+=time-t[1];
            time+=t[2];
            ans.push_back(t[0]);
            tat+=time-t[1];
            pq.pop();
        }
        else 
            time++;
    }
    answer.avgWt = wt*1.0/n;
    answer.ProcessOrder = ans;

    return answer;
}

//The Main Function
int main() {
    int n;
    cout<<"Enter input:\n";
    cin>>n;
    vector<process> Processes(n);
    for (int i = 0; i < n; i++) {
        cin>>Processes[i].pid;
        cin>>Processes[i].at;
        cin>>Processes[i].bt;
        cin>>Processes[i].prt;
    }

    vector<ScheduleResult> Result(6);
    Result[0] = FCFS(Processes);
    Result[1] = RoundRobin(Processes);
    Result[2] = SJFP(Processes);
    Result[3] = SJFNP(Processes);
    Result[4] = PriorityP(Processes);
    Result[5] = PriorityNP(Processes);

    sort(Result.begin(), Result.end(), CompareScheduleResult);

    //Output
    cout<<"Best: "<<Result[0].S_type<<"     Worst: "<<Result[5].S_type<<endl;
    cout<<"Avg WT(Best) = "<<Result[0].avgWt<<"     Avg WT(Worst) = "<<Result[5].avgWt<<endl;
    vector<int> BestP = Result[0].ProcessOrder;
    vector<int> WorstP = Result[5].ProcessOrder;
    cout<<"Best: ";
    for(int i = 0; i < BestP.size(); i++) {
        if(i != BestP.size() - 1) {
            cout<<"P"<<BestP[i]<<" - ";
        }
        else {
            cout<<"P"<<BestP[i]<<endl;
        }
        
    } 
    cout<<"Worst: ";
    for(int i = 0; i < WorstP.size(); i++) {
        if(i != WorstP.size() - 1) {
            cout<<"P"<<WorstP[i]<<" - ";
        }
        else {
            cout<<"P"<<WorstP[i]<<endl;
        }
        
    } 

    return 0;

}