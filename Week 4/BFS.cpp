//Uses Array of Vectors for Adjacency List Reresentation of Graph
//Uses Queue(FIFO) for BFS
//Runs in O(V+E) with adjacency list representation.

#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;

int BFS(vector<int> arr[],int start,int vert){
    int node;
    bool visited[vert];
    for(int i=0;i<vert;i++) visited[i]=false;
    queue<int> nodes;
    nodes.push(start);
    while(!nodes.empty()){
      node=nodes.front();
      //cout<<node<<endl;
      //system("pause");
      nodes.pop();
      if(!visited[node]){
          cout<<"Visited : "<<node<<endl;
          visited[node]=true;
          for(int i=0;i<arr[node].size();i++) nodes.push(arr[node][i]);
      }
      //cout<<"Nodes: ";for(int i=0;i<nodes.size();i++) {cout<<nodes.front()<<" ";nodes.pop();}
      //cout<<endl;
      //system("pause");
    }
}
int main()
{
    int vertices,edges,a,b;
    cout<<"No of Vertices : ";cin>>vertices;
    cout<<"No of Edges : ";cin>>edges;
    vector<int> arr[vertices];
    cout<<"Enter Edges : "<<endl;
    for(int i=0;i<edges;i++){
            cin>>a>>b;
            arr[a].push_back(b);
            arr[b].push_back(a);
    }
    BFS(arr,0,vertices);
    system("pause");
    return 0;
}
/*e.g
0 1
0 2
1 3
2 3
2 5
3 4
3 5
4 5
*/
