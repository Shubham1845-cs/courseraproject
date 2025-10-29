#include <iostream>
using namespace std;
#include <vector>
#include <queue>
class Edge
{
public:
    int s, d;
    Edge(int s1, int d1)
    {
        s = s1;
        d = d1;
    }
};
void Creategraph(vector<vector<Edge>> &graph)
{
    for (int i = 0; i < graph.size(); i++)
    {
        graph[i] = vector<Edge>();
    }

    graph[0].push_back(Edge(0, 1));
    graph[0].push_back(Edge(0, 2));

    graph[1].push_back(Edge(1, 0));
    graph[1].push_back(Edge(1, 3));

    graph[2].push_back(Edge(2, 0));
    graph[2].push_back(Edge(2, 4));

    graph[3].push_back(Edge(3, 1));
    graph[3].push_back(Edge(3, 4));
    graph[3].push_back(Edge(3, 5));

    graph[4].push_back(Edge(4, 2));
    graph[4].push_back(Edge(4, 3));
    graph[4].push_back(Edge(4, 5));

    graph[5].push_back(Edge(5, 3));
    graph[5].push_back(Edge(5, 4));
    graph[5].push_back(Edge(5, 6));

    graph[6].push_back(Edge(6, 5));
}
void BFS(vector<vector<Edge>> graph,int v, vector<bool>&arr,int start)
{
       queue<int>q;
       q.push(start);
       while(!q.empty())
       {
         int val= q.front();
         q.pop();


          if(arr[val]==false)
          { 
             cout<<val<<" ";
             arr[val]=true;
             for(int i=0;i<graph[val].size();i++)
             {
                 Edge e=graph[val][i];
                 q.push(e.d);
             }
          }
       }
       
}
int main()
{
    int v=7;
    vector<vector<Edge>> graph(v);
    Creategraph(graph);
    vector<bool>arr(v,false);
    for(int i=0;i<v;i++)
    {
        if(arr[i]==false)
        {
            BFS(graph,v,arr,i);    
        }
          
    }
   
    return 0;
}
