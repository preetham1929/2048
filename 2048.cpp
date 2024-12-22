#include<bits/stdc++.h>
using namespace std;
#define pb push_back

void slide(vector<int>&v){
	vector<int>a;
	for(auto &x:v)if(x)a.pb(x);
	int n = a.size();
	if(n==1){
		v[3]=a[0];
		for(int i=0;i<3;i++)v[i]=0;
	}
	else if(n==2){
		if(a[0]==a[1]){
			for(int i=0;i<3;i++)v[i]=0;
			v[3]=2*a[0];
		}
		else{
			for(int i=0;i<2;i++)v[i]=0;
			v[3]=a[1];
			v[2]=a[0];
		}
	}
	else if(n==3){
		if(a[1]==a[2]){
			for(int i=0;i<2;i++)v[i]=0;
			v[3]=2*a[1];
			v[2]=a[0];
		}
		else{
			if(a[0]==a[1]){
				v[3]=a[2];
				v[2]=2*a[0];
				for(int i=0;i<2;i++)v[i]=0;
			}
			else{
				v[0]=0;
				v[1]=a[0];
				v[2]=a[1];
				v[3]=a[2];
			}
		}
	}
	else if(n==4){
		if(a[2]==a[3]){
			if(a[0]==a[1]){
				v[3]=2*a[3];
				v[2]=2*a[1];
				v[1]=0;
				v[0]=0;
			}
			else{
				v[3]=2*a[3];
				v[2]=a[1];
				v[1]=a[0];
				v[0]=0;
			}
		}
		else{
			v[3]=a[3];
			if(v[1]==v[2]){
				v[2]*=2;
				v[1]=v[0];
				v[0]=0;
			}
			else if(v[0]==v[1]){
				v[1]*=2;
				v[0]=0;
			}

		}
	}

}

void helper(vector<vector<int>>&grid , char x){
	bool f = ((x=='a') || (x=='w'));
	if((x=='d') || (x=='a')){
		for(int i=0;i<4 && f;i++)reverse(grid[i].begin(),grid[i].end());
		for(int i=0;i<4;i++)slide(grid[i]);
		for(int i=0;i<4 && f;i++)reverse(grid[i].begin(),grid[i].end());
	}
	else {
		for(int i=0;i<4;i++){
			vector<int>v;
			for(int j=0;j<4;j++)v.pb(grid[j][i]);
			if(f)reverse(v.begin(),v.end());
			slide(v);
			if(f)reverse(v.begin(),v.end());
			for(int j=0;j<4;j++){
				grid[j][i]=v[j];
			}
		}
	}
}



bool populate_random(vector<vector<int>>&grid){
	vector<pair<int,int>>empty;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(grid[i][j]==0)empty.push_back({i,j});
		}
	}
	if(empty.size()==0)return 0;
	int n = empty.size();
	int ind = rand()%n;
	int i = empty[ind].first, j = empty[ind].second;
	grid[i][j]=2;
	return 1;
}
void printBoard(vector<vector<int>>&grid){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(!grid[i][j])cout<<"* ";
			else cout<<grid[i][j]<<" ";
		}
		cout<<endl;
	}
}
bool  isValidkey(char c){
	// cout<<"validkey\n";
	return !(c!='w' && c!='d' && c!='a' &&  c!='s');
}
bool isPlayable(vector<vector<int>>&grid){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(!grid[i][j])return 1;
			if(j<3 && grid[i][j]==grid[i][j+1])return 1;
			if(j>0 && grid[i][j-1]==grid[i][j])return 1;
			if(i>0 && grid[i][j]==grid[i-1][j])return 1;
			if(i<3 && grid[i][j]==grid[i+1][j])return 1;
		}
	}
	return 0;
}

bool check(vector<vector<int>>&a , vector<vector<int>>&b){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++)if(a[i][j]!=b[i][j])return 1;
	}
	return 0;
}

void playGame(){
	vector<vector<int>>grid(4,vector<int>(4,0));
	while(populate_random(grid)){
		printBoard(grid);
		if(!isPlayable(grid)){
			cout<<"GameOver\n";
			break;
			//Implement restart 
		}
		cout<<"Press up(w) , bottom(s) , left(a) , right(d) key \n ";
		bool f=1;
		char c;
		cin>>c;
		while((isValidkey(c)) && f){
			f=0;
			vector<vector<int>>newGrid = grid;
			helper(newGrid,c);
			// printBoard(newGrid);
			if(!check(newGrid,grid)){
				cout<<"Try Again\n";
				cout<<"Press up(w) , bottom(s) , left(a) , right(d) key \n ";
				printBoard(grid);
				cin>>c;
				f=1;
			}
			else grid=newGrid;
		}
	}
}



int main(){

	playGame();
}











