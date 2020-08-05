
/*
First ,exactly we have to count the nodes of a cycle where the amount of nodes of a particular cycle is odd.
So, first of all finding all bridge edges and remove them from the graph and store them in a set array called newGraph.
We could take array of vector ,but it will take O(n) time complexity to erase a value from a node's adjacency vector,
That's why I used array of set which will take O(logn) in average to erase any value from a set.
Then we use another dfs which will run over the cycle only ,as all critical edges are removed.
So, if we find cycle of odd length then we will count those nodes.
*/


/// Time-0.443s
/// Very Nice one 

#include<bits/stdc++.h>

using namespace std;

const int mx=10002;

vector<int>adj[mx];/// adjacency matrix
set<int>newGraph[mx];/// adjacentry matrix used for graph without all critical edges
bool visited[mx];/// visited or not ??
int disc[mx]={0};/// dfs time finding,dfs number of a node
int low[mx]={0};/// low dfs time for purpose to find a cycle
int parent[mx]={-1};/// -1 holds for Null
int dist[mx];
int nodes=0;
bool oddCycle;

void bcc(int u)
{
   ///this parameter will be used for counting discovery time of a node
    static int time=0;
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
            parent[v]=u;
            bcc(v);
    ///this is for finding low dfs number of a node
        low[u]=min(low[u],low[v]);
  /// when low[v]>disc[u] , this u-v is the critical edges,bridge (u-v)
        if(low[v]>disc[u])
        {
            newGraph[u].erase(v);
            newGraph[v].erase(u);
           /// removing bridges pairs
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

/// is Oddcycle ?
void cycle_dfs(int u,int p,int len)
{
    nodes++;
    dist[u] = len;
    visited[u] = true;

    set<int>::iterator it;
    for(it=newGraph[u].begin();it!=newGraph[u].end();it++)
    {
        int v=(*it);
        if(!visited[v])
            cycle_dfs(v,u,len+1);

        else if (visited[v] && (dist[v]-dist[u])%2==0) /** check the length of the loop defined by each back-edge **/
            oddCycle = true;
    }
}


    int main()

    {
        int tc;
        cin>>tc;
        for(int tst=1;tst<=tc;tst++)
        {
            for(int k=0;k<mx;k++)
            {
                adj[k].clear();
                newGraph[k].clear();
                visited[k]=false;
                disc[k]=0;
                low[k]=0;
                parent[k]=-1;
                dist[k]=0;
            }

        int V,E,u,v;
        cin>>V>>E;
        while(E--)
        {
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);

            newGraph[u].insert(v);
            newGraph[v].insert(u);
        }

        for(int i=0;i<V;i++)
        {
            ///this node is not visited yet
            ///the graph may be not connected
            ///iterate for every connected component
            if(!visited[i])
            {
               bcc(i);
            }
        }
        /// now again make visited array false to run over dfs
        for(int i=0;i<mx;i++) visited[i]=false;

         int res = 0;

        for(int i=0; i<V; i++)
        {
            nodes = 0;
            oddCycle = false;
            if(!visited[i])
                cycle_dfs(i,-1,0);

            if(oddCycle)
                res += nodes;
        }
        cout<<"Case "<<tst<<": ";
        cout<<res<<endl;
        }

        return 0;
    }
