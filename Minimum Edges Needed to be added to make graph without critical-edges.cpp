
/// The main idea of ​​the topic- give you a picture and ask how many edges should be added at least to turn this picture into an edge bi-connected block
/// Problem-solving idea- first find out all the edges are double connected, and then shrink the points.
/// The bridge is the connecting point,so that a tree can be formed, and the number of edges that need to be added is (the number of leaf nodes + 1)/2

/*
       1
    /  |  \
   2   3   4

   Now ,if I ask you at least how many edge should be connected to make sure that
   there will be two paths from any node to other node .So, we have to add edge between 2 and 4, the another edge could be either through
   2-3 or 3-4 .
   So at least we have to add 2 extra edges to this tree ,to make it bi-connected block. So exactly there is a simple formula is to make a tree
   bi-connected block ,we had to add extra at least (leaf+1)/2 edges,leaf is the number of leaf nodes.

   So we have to form a cycle as a single node by path compression. then easily we can make this graph as tree (only bridges will be available which implies that it is a tree). Then we will count leaf nodes.

*/


/// Time- 0.495s
/// Classical One ,Nice one 

#include<bits/stdc++.h>

#define inf INT_MAX

using namespace std;

const int mx=10009;

vector<int>adj[mx];/// adjacency matrix
bool visited[mx];/// visited or not ??
int disc[mx]={0};/// dfs time finding,dfs number of a node
int low[mx]={0};/// low dfs time for purpose to find a cycle
int parent[mx]={-1};/// -1 holds for Null
vector< pair<int,int> >bridges; /// push back the bridges into a vector
///int is_bridge_edge[mx][mx];/// checking is_bridge
map<int, map<int, int> >is_bridge_edge;
int counts[mx];

void apu_finding(int u)
{
    ///this parameter will be used for counting discovery time of a node
    static int time=0;
    ///for finding different subtree of a node where the subtree are not connected by back edge or cross edge
    int child=0;
    ///for marking a node
    visited[u]=true;
    ///keeping dfs(discovery) time and low discovery time
    disc[u]=low[u]=time++;
    vector<int>::iterator it;
    ///iterator to iterate adjacency matrix of graph
    for(it=adj[u].begin();it!=adj[u].end();it++)
    {
    ///neighbour's node of v from u, u->v
        int v=(*it);
    ///if not visited ,then proceed apu_finding for new node(v)
        if(!visited[v])
        {
            child++;
            parent[v]=u;
            apu_finding(v);
    ///this is for finding low dfs number of a node
        low[u]=min(low[u],low[v]);
  /// when low[v]>disc[u] , this u-v is the critical edges
        if(low[v]>disc[u])
        {
            is_bridge_edge[u][v]=is_bridge_edge[v][u]=1;
            bridges.push_back(make_pair(u,v));
        }

        }
/// this means that, visited[v] is true i.e. already v is visited
/// if u's parent is not v,then this is a back edge , u-v .so we will take low[] time from disc[] time of v
        else if(v!=parent[u])
        {
            low[u]=min(low[u],disc[v]);
        }
    }

}

int Find(int u)
{
    if(u == parent[u]) return u;
    else return parent[u] = Find(parent[u]);
}

int main()
{
    int tc,V,E;
    cin>>tc;
    for(int t=1;t<=tc;t++)
    {
        int u,v;
        cin>>V>>E;
        is_bridge_edge.clear();
        bridges.clear();
        for(int i=0;i<mx;i++)
        {
            visited[i]=false;
            counts[i]=0;
            parent[i]=-1;
            adj[i].clear();
        }

        while(E--)
        {
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        for(int i=0;i<V;i++)
        {
            if(!visited[i]) {apu_finding(i);}
        }
        /// we will assign new parent for path compression
        for(int i=0;i<V;i++) {parent[i]=i;}

         for(int i=0;i<V;i++)
        {
            for(int j=0;j<(int)(adj[i].size());j++)
            {
                 u=i;
                 v = adj[u][j];
                if(is_bridge_edge[u][v] != 1)
                {
                    u = Find(u);
                    v = Find(v);
                    if(u!=v)
                    {
                        parent[u] = v;
                    }
                }
            }
        }

        /// now the main game is on

        for(int j=0;j<(int)bridges.size();j++)
        {
            u=bridges[j].first;
            v=bridges[j].second;

            u = Find(u);
            v = Find(v);

            counts[u]++;
            counts[v]++;
        }
         int leaves=0;
        for(int i=0;i<V;i++)
        {
            if(counts[i]==1) {leaves++;}
        }

         if (leaves% 2 ) leaves = leaves/ 2 + 1 ;
         else        leaves = leaves/ 2 ;

        printf("Case %d: %d\n", t,leaves);
    }
    return 0;
}

