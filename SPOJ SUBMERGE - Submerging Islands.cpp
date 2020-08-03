#include<bits/stdc++.h>


using namespace std;

const int mx=10001;

vector<int>adj[mx];/// adjacency matrix
bool apu[mx];
bool visited[mx];/// visited or not ??
int disc[mx]={0};/// dfs time finding,dfs number of a node
int low[mx]={0};/// low dfs time for purpose to find a cycle
int parent[mx]={-1};/// -1 holds for Null
///vector< pair<int,int> >bridges; /// push back the bridges into a vector
///int is_bridge_edge[mx][mx];/// checking is_bridge
///map<int, map<int, int> >is_bridge_edge;
//int counts[mx];
//vector<int>leaf;

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

        if(parent[u]==-1&&(child>1)) {apu[u]=true;}/// root
        if(parent[u]!=-1&&low[v]>=disc[u]) {apu[u]=true;}

        }
/// this means that, visited[v] is true i.e. already v is visited
/// if u's parent is not v,then this is a back edge , u-v .so we will take low[] time from disc[] time of v
        else if(v!=parent[u])
        {
            low[u]=min(low[u],disc[v]);
        }
    }
}


int main()
{
    int V,E,u,v;
    while(cin>>V>>E&&(V!=0&&E!=0))
    {

        for(int i=1;i<=V;i++)
        {
            visited[i]=false;
            parent[i]=-1;
            adj[i].clear();
            apu[i]=false;
        }

        while(E--)
        {
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        for(int i=1;i<=V;i++)
        {
            if(!visited[i]) {apu_finding(i);}
        }

        int counts=0;
         for(int i=1;i<=V;i++)
        {
            if(apu[i]) {counts++;}
        }
       cout<<counts<<endl;
    }

    return 0;
}

