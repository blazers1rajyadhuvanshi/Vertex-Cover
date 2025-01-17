//Implementation of SD algoirthm for vertex covering in finding the optimal clique set

#include<iostream>
#include<vector>

using namespace std;

vector<vector<int> > complement_graph(vector<vector<int> > G);
vector<int> complement_array(vector<int> arr,int n);
vector<int> alom_algorithm(vector<vector<int> > Graph, int degree[], int n);
vector<int> preprocess(vector<vector<int> > Graph, int degree[], int n);
vector<int> SD_algorithm(vector<vector<int> > Graph, int degree[], int n);

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n; // number of vertices
	int m; // number of edges
	cin >> n >> m; // inputs number of vertices and number of edges
	
	vector<vector<int> > Graph(n); // graph containing n vertices
	
	int* degree = new int[n]; // stores the degree of the vertices
	for(int i = 0; i < n; i++)//initializes degree to 0
		degree[i] = 0;
		
	int u, v; // edge from u to v
	for(int i = 0; i < m; i++) // inputs m edges, vertex numbering starts from 0
	{
		cin >> u >> v;
		Graph[u].push_back(v); // adds edge 
		Graph[v].push_back(u); // adds edge
		 //degree[u] += 1; degree[v] += 1; // for each edge increments the degree of the vertices by 1
	}
    Graph = complement_graph(Graph);
    for(int i = 0; i < n; i++){
        degree[i] = Graph[i].size();
    }

	vector<int> vertexCover = SD_algorithm(Graph, degree, n);
    vector<int> clique = complement_array(vertexCover,n);
		 
	cout << endl;	 
	//for(int i = 0; i < vertexCover.size(); i++)
	//	cout << vertexCover[i] << " ";
	//cout << "\nSize of Vertex Cover: " << vertexCover.size();
    for(int i = 0; i < clique.size(); i++)
        cout<< clique[i]<<" ";
    cout<< "\nSize of Clque: " << clique.size();
}

vector<int> alom_algorithm(vector<vector<int> > Graph, int degree[], int n)
{
	vector<int> vertexCover;
	int maxDegreeVertex;
	while(true)
	{
		int maxDegree = 0; 
		for(int i = 0; i < n; i++) // finds the vertex with the maximum degree
		{
			if(degree[i] > maxDegree && degree[i] >= 0)
			{
				maxDegree = degree[i];
				maxDegreeVertex = i;
			}
		}
		if(maxDegree == 0) //if all the vertices have degree equal to zero then breaks
			break;
		vertexCover.push_back(maxDegreeVertex); // adds the vertex with the maximum degree to the solution 
		for(int i = 0; i < Graph[maxDegreeVertex].size(); i++) // decrements the degree of all the adjacent vertices of the added vertices by one
			degree[Graph[maxDegreeVertex][i]] -= 1;
		degree[maxDegreeVertex] = 0;
	}
	return vertexCover;
}

vector<int> preprocess(vector<vector<int> > Graph, int degree[], int n)
{
	vector<int> vertexCover;
	vector<int> pendantVertex;
	for(int i = 0; i < n; i++) // finds all the pendant vertices
	{
		if(degree[i] == 1)
			pendantVertex.push_back(i);
	}
	int adj;
	for(int i = 0; i < pendantVertex.size(); i++)
	{
		adj = Graph[pendantVertex[i]][0]; 
		if(degree[adj] != 0) //multiple pendant vertices might have the same adjacent vertex, this condition ensures that no vertex is added more than once
		{
			vertexCover.push_back(adj); // adds the vertex adjacent to the pendant vertex to the solution
			degree[adj] = 0; 
			for(int j = 0; j < Graph[adj].size(); j++)
				degree[Graph[adj][j]] -= 1;
 		}
	}
 	return vertexCover;
}

vector<int> SD_algorithm(vector<vector<int> > Graph, int degree[], int n)
{
	vector<int> vertexCover1 = preprocess(Graph, degree, n); // preprocessses
	vector<int> vertexCover2 = alom_algorithm(Graph, degree, n); // alom_algorithm
	vector<int> vertexCover; // contains the vertices found by preprocess and alom alogirthm
	vertexCover.reserve(vertexCover1.size() + vertexCover2.size());
	vertexCover.insert(vertexCover.end(), vertexCover1.begin(), vertexCover1.end());
	vertexCover.insert(vertexCover.end(), vertexCover2.begin(), vertexCover2.end());
	return vertexCover;
}
vector<vector<int> > complement_graph(vector<vector<int> >G)
{
    int n=G.size();
    vector<vector<int>> mat(n,vector<int>(n));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            mat[i][j]=1;
    }
    for(int i=0;i<n;i++)
    {
        int m=G[i].size();
        for(int j=0;j<m;j++)
        {
            mat[i][G[i][j]]=0;
        }
    }
    vector<vector<int> >G1(n);
    for(int i=0;i<n;i++)
    {
      for(int j=0;j<n;j++)
      {
          if(mat[i][j]&&i!=j){
            G1[i].push_back(j);
              
          }
      }
    }
    return G1;
}
vector<int> complement_array(vector<int> arr,int n){
   bool used[n] = {0};
   for(int i = 0; i < arr.size(); i++){
       used[arr[i]] = 1;
   }
   vector<int> ans;
   for(int i = 0; i < n; i++){
       if(!used[i]) ans.push_back(i); 
   }
   return ans;
}
