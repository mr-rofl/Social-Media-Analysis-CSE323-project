#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

int main(){
	int n,m;
	cin>>n>>m;

	ofstream myfile("graph.txt"); //open file to edit
	string s;
	
	if (n>100) // 1st algorithm
	{
		vector<vector<bool>> adj_mat(n, vector<bool> (n,false)) ;
		vector<int> centrality(n,0); //contains centrality for each node
		int from,to,dum;
		
		for (int i = 0; i < m; i++)
		{
			cin>>from>>to>>dum;
			s=to_string(from)+" "+to_string(to)+" "+to_string(dum)+"\n";
			myfile<<s; //append to text file
			adj_mat[from][to]=true; //set the matrix
			centrality[from]++;
			centrality[to]++;
		}
		myfile.close();
		for (int i = 0; i < n; i++)
		{
			cout<<centrality[i]<<endl;
		}
		return 0;
	}
	else //2nd or 3rd
	{
		vector<vector<int>> adj_mat(n, vector<int> (n,0)) ;
		int from,to,dum;
		for (int i = 0; i < m; i++)
		{
			cin>>from>>to>>dum;
			adj_mat[from][to]=dum;
			s=to_string(from)+" "+to_string(to)+" "+to_string(dum)+"\n";
			myfile<<s; //append to text file
		}
		myfile.close();
	}

	return 0;
}