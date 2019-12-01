// C++ program to represent undirected and weighted graph
// using STL. The program basically prints adjacency list
// representation of graph
#include <bits/stdc++.h>

using namespace std;
#define V 5
# define INF 99999
typedef struct envelope {
  int env_loc;
  int del_loc;
};

int dist[V][V];
int del_dist[3];
int env_dist[3];
int flag =1;
int func(int driv_loc, envelope env[], int del_dist[],int env_dist[]) {
if(flag==1)
{
    for(int i = 0; i < 3; i++) {
      env_dist[i] = dist[driv_loc][env[i].env_loc];

    }
}
flag=0;

        int i;
      int temp = INF;
      int temp2 = -1;
      int temp3 = -1;
      for (int i = 0; i < 3; i++) {
        if(temp >=  env_dist[i])
          {
            temp =  env_dist[i];
              temp2 = i;

          }


        }
        for (i = 0; i < 3; i++) {
          if(temp >= del_dist[i]) {

            temp = del_dist[i];
                temp3 = i;
        }


      }

      if(temp == INF) {
      return 0;

      }
      if(temp3 != -1)
        {
        cout <<temp3+1<< " passage will be delivered" << endl;
         del_dist[temp3] = INF;
         driv_loc = temp3;
         for(i=0;i<3;i++)
        {
        if(env_dist[i]!=INF)
        {
        env_dist[i]=dist[driv_loc][env[i].env_loc];
        }
        }

         }
      else {
        cout << temp2 +1 << "envelope will be collected" << endl;
        driv_loc = temp2;
        env_dist[temp2]=INF;
        for(i=0;i<3;i++)
        {
        if(env_dist[i]!=INF)
        {
        env_dist[i]=dist[driv_loc][env[i].env_loc];
        }
        }
        del_dist[temp2] = dist[driv_loc][env[temp2].del_loc];
      }

    func( driv_loc, env, del_dist, env_dist);


      }
// To add an edge
void addEdge(vector < pair < int, int > > adj[], int u,
  int v, int wt) {
  adj[u].push_back(make_pair(v, wt));
  adj[v].push_back(make_pair(u, wt));
}

// Driver code

// A function to print the solution matrix
void printSolution();

// Solves the all-pairs shortest path
// problem using Floyd Warshall algorithm
void floydWarshall(int graph[][V]) {
  /* dist[][] will be the output matrix
  that will finally have the shortest
  distances between every pair of vertices */
  int i, j, k;

  /* Initialize the solution matrix same
  as input graph matrix. Or we can say
  the initial values of shortest distances
  are based on shortest paths considering
  no intermediate vertex. */
  for (i = 0; i < V; i++)
    for (j = 0; j < V; j++)
      dist[i][j] = graph[i][j];

  /* Add all vertices one by one to
  the set of intermediate vertices.
  ---> Before start of an iteration,
  we have shortest distances between all
  pairs of vertices such that the
  shortest distances consider only the
  vertices in set {0, 1, 2, .. k-1} as
  intermediate vertices.
  ----> After the end of an iteration,
  vertex no. k is added to the set of
  intermediate vertices and the set becomes {0, 1, 2, .. k} */
  for (k = 0; k < V; k++) {
    // Pick all vertices as source one by one
    for (i = 0; i < V; i++) {
      // Pick all vertices as destination for the
      // above picked source
      for (j = 0; j < V; j++) {
        // If vertex k is on the shortest path from
        // i to j, then update the value of dist[i][j]
        if (dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j];
      }
    }
  }

  // Print the shortest distance matrix
  printSolution();
}

/* A utility function to print solution */
void printSolution() {
  cout << "The following matrix shows the shortest distances"
  " between every pair of vertices \n";
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      if (dist[i][j] == INF)
        cout << "INF" << "     ";
      else
        cout << dist[i][j] << "     ";
    }
    cout << endl;
  }
}

int main() {

    int a = 5;
    int input[a][a];
    for (int i = 0; i < a; i++) {
      for (int j = 0; j < a; j++) {
        if (i == j) {
          input[i][j] = 0;
        } else {
          input[i][j] = INF;
        }

      }
    }

    vector < pair < int, int > > adj[a];
    addEdge(adj, 0, 1, 10);
    addEdge(adj, 0, 4, 20);
    addEdge(adj, 1, 2, 30);
    addEdge(adj, 1, 3, 40);
    addEdge(adj, 1, 4, 50);
    addEdge(adj, 2, 3, 60);
    addEdge(adj, 3, 4, 70);

    int v, w;
    for (int u = 0; u < a; u++) {
      //cout << "Node " << u << " makes an edge with \n";
      for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
        v = it -> first;
        w = it -> second;
        for (int i = 0; i < a; i++)

          input[u][v] = w;
        //cout << "\tNode " << v << " with edge weight ="
        //<< w << "\n";
      }

    }

    cout << "matrix is" << endl;
    for (int i = 0; i < a; i++) {
      for (int j = 0; j < a; j++) {
        if (input[i][j] == INF) {

          cout << "INF" << " ";
        } else {
          cout << input[i][j] << "  ";
        }
        if (j == 4) {
          cout << endl;
        }
      }
    }

    int graph[V][V];

    for (int i = 0; i < V; i++) {
      for (int j = 0; j < V; j++) {
        graph[i][j] = input[i][j];
      }
    }

    floydWarshall(graph);

    int dri_loc, tot_env;

    cout << "enter the vertex where driver is located. Choose from 0,1,2,3,4" << endl;
    cin >> dri_loc;
    cout << "enter no. of envelope" << endl;
    cin >> tot_env;
    envelope env[3];
    for (int i = 0; i < tot_env; i++) {
      cout << "enter the envelope location of " << i + 1 << "envelope" << endl;
      cin >> env[i].env_loc;
      cout << "enter the delivery location of " << i + 1 << "envelope" << endl;
      cin >> env[i].del_loc;
    }

    for(int i = 0; i < 3; i++) {
      del_dist[i] = INF;
    }

   func( dri_loc, env, del_dist, env_dist);
return 0;
    }
