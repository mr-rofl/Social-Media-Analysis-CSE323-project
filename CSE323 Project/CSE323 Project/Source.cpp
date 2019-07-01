#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int n,m;

int* betweeness_count;
using namespace std;



    
//degree of centrality//////////

void degree_centrality(){
	string s;
	ofstream myfile("C:/Users/ROFL/Documents/GitHub/Social-Media-Analysis-CSE323-project/graph.txt");
	vector<int> centrality(n,0); //contains centrality for each node
	int from,to,dum;
		
	for (int i = 0; i < m; i++)
	{
		cin>>from>>to>>dum;
		s=to_string(from)+" "+to_string(to)+" "+to_string(dum)+"\n";
		myfile<<s; //append to text file
			
		centrality[from]++;
		centrality[to]++;
	}
	myfile.close();


	for (int i = 0; i < n; i++)
	{
		cout<<centrality[i];
		cout<<"\n";
	}
}

//end of degree of centrality////////////////

////////////////////////////////////////////////////////////////////////////////////

int minDistance(vector<int> dist, vector<bool> sptSet) /// USED FOR 2 & 3
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

///CLOSENESS CENTRALITY//////////
void printCloseness(vector<int> dist)
{
    float sum = 0;

    for (int i = 0; i < n ; i++)
        sum += dist[i];

    printf("%.7f\n", (n-1)/sum);

}

void dijkstra(vector<vector <int>> graph, int src)
{
    vector<int> dist(n);     // The output array.  dist[i] will hold the shortest
    // distance from src to i

    vector<bool> sptSet(n); // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < n-1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < n; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u]+graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    printCloseness(dist);
}

void closeness_centrality(){
	string s;
	ofstream myfile("C:/Users/ROFL/Documents/GitHub/Social-Media-Analysis-CSE323-project/graph.txt");
	vector<vector<int>> adj_mat(n, vector<int> (n,0)) ;
	int from,to,dum;
	for (int i = 0; i < m; i++)
	{
		cin>>from>>to>>dum;
		adj_mat[from][to]=dum;
        adj_mat[to][from]=dum;
		s=to_string(from)+" "+to_string(to)+" "+to_string(dum)+"\n";
		myfile<<s; //append to text file
	}
	myfile.close();
    for (int i = 0; i < n; i++)
    {
        dijkstra(adj_mat, i);            
    }
}
///END OF CLOSENESS CENTRALITY///////////

////////////////////////////////////////////////////////////////////////////////



///BETWEENESS CENTRALITY///////

void printPath(vector<int> parent, int j) 
{ 
      
    // Base Case : If j is source 
    if (parent[j] == - 1) 
        return; 
  
    printPath(parent, parent[j]); 
  
    printf("%d ", j); 
	betweeness_count[j]++; /// di eli ana zawedtaha 3ashan ne3ed fiha
}
void printSolution(vector<int> dist, int n,  vector<int> parent,int s) 
{ 
    int src = s; 
    for (int i = 1; i < n; i++) 
    { 
        printf("\n%d -> %d \t\t %d\t\t%d ", 
                      src, i, dist[i], src); 
        printPath(parent, i); 
    } 
}

bool is_child(vector<int> parent,int t){
	
	if (parent[t]==-1)
	{
		return false;
	}
	for (int i = 0; i < n; i++)
	{
		if (parent[i]==t)
		{
			return true;
		}
	}
	return false;
}

void dijkstra1(vector<vector<int>> graph, int src)
{

    // The output array. dist[i]
    // will hold the shortest
    // distance from src to i
    vector<int> dist(n);

    // sptSet[i] will true if vertex
    // i is included / in shortest
    // path tree or shortest distance
    // from src to i is finalized
    vector<bool> sptSet(n);

    // Parent array to store
    // shortest path tree
    vector<int> parent(n);

    // Initialize all distances as
    // INFINITE and stpSet[] as false
    for (int i = 0; i < n; i++)
    {
        parent[src] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex
    // from itself is always 0
    for (int i = 0; i < src + 1; i++)
    {
        parent[i] = -1;
        dist[i] = 0;
    }

    // Find shortest path
    // for all vertices
    for (int count = 0; count < n - 1; count++)
    {
        // Pick the minimum distance
        // vertex from the set of
        // vertices not yet processed.
        // u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex
        // as processed
        sptSet[u] = true;

        // Update dist value of the
        // adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < n; v++)
        {
            // Update dist[v] only if is
            // not in sptSet, there is
            // an edge from u to v, and
            // total weight of path from
            // src to v through u is smaller
            // than current value of
            // dist[v]

            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] <= dist[v])
            {

                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
                if (u != src && is_child(parent, u))
                {
                    betweeness_count[u]++;
                    cout << "from: " << src << " to: " << u << endl;
                    int x = u;
                    while (parent[x] != -1)
                    {
                        x = parent[x];
                        if (x != src && is_child(parent, u))
                        {
                            betweeness_count[x]++;
                            cout << "from: " << src << " to: " << u << " node: " << x << endl;
                        }
                    }
                }
            }
        }
    }

    // print the constructed
    // distance array
    printSolution(dist, n, parent, src);
}

void betweeness_centrality(){
	string s;
	ofstream myfile("C:/Users/ROFL/Documents/GitHub/Social-Media-Analysis-CSE323-project/graph.txt");
	vector<vector<int>> adj_mat(n, vector<int> (n,0)) ;
	int from,to,dum;
	for (int i = 0; i < m; i++)
	{
		cin>>from>>to>>dum;
		adj_mat[from][to]=dum;
        adj_mat[to][from]=dum;
		s=to_string(from)+" "+to_string(to)+" "+to_string(dum)+"\n";
		myfile<<s; //append to text file
	}
	myfile.close();
	/*for (int i = 0; i < n; i++)
	{
		dijkstra1(adj_mat,i);
	}*/
	dijkstra1(adj_mat,0); /// hatedrab ma3ak law tani argument ay 7aga 8eir 0 
}

///END OF BETWEENESS CENTRALITY//////////

int main(){
	char c;
	cin>>c;
	cin>>n>>m;

	
	betweeness_count = new int[n];
	for (int i = 0; i < n; i++)
	{
		betweeness_count[i]=0;
	}

	switch (c)
	{
	case 'a':{degree_centrality();break;}
	case 'b':{closeness_centrality();break;}
	case 'c':{betweeness_centrality();break;}
	default:
		break;
	}
	
	
	

	system("python C:/Users/ROFL/Documents/GitHub/Social-Media-Analysis-CSE323-project/visualize_graph.py\n");


	return 0;
}