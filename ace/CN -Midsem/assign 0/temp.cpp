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

signed main(){
	char x[20],y[20];
	for(int i=0;i<20;i++){
		x[i]='\0';
		y[i]='\0';
	}
	cin>>x>>y;
	int lenx=len(x);
	int leny=len(y);
	cout<<strcomp(x,y,lenx,leny)<<endl;
}
