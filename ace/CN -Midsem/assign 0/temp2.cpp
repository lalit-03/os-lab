#include<bits/stdc++.h>
using namespace std;
#define int long long

int strcomp(char *x,char *y,int lenx,int leny){
	int i=0,j=0;
	while(i<lenx && j<leny && x[i]==y[j]){
		i++;j++;
	}
if(i==lenx && j==leny) return 0;
else if(i==lenx) return 1;
else if(j==leny) return -1;
else{
	if(x[i]<y[j])return 1;
	else return -1;	
}
}

int len(char *x){
	int i=0;
	while(x[i]!='\0')i++;
	return i;
}

void strsort(char a[][20],char **b,int n){
	for(int i=0;i<n;i++){
		for(int j=n-2;j>=i;j--){
				int x=strcomp(b[j],b[j+1],len(b[j]),len(b[j+1]));
				if(x==-1){
					char *temp=b[j];
					b[j]=b[j+1];
					b[j+1]=temp;
				}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<len(b[i]);j++){
			cout<<b[i][j];
		}
		cout<<endl;
	}
}

signed main(){
	int n;cin>>n;
	char c[n][20];
	char *b[n];
	for(int i=0;i<n;i++)
	{
		
		for(int j=0;j<20;j++) c[i][j]='\0';
		cin>>c[i];
		b[i]=c[i];
	}
	
	
	strsort(c,b,n);
	
	return 0;
}
