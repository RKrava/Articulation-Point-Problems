/// problem link - https://www.hackerearth.com/practice/algorithms/graphs/biconnected-components/tutorial/

#include<bits/stdc++.h>

using namespace std;

const int mx=10009;

stack< pair<int,int> >st;
vector<int>adj[mx];/// adjacency matrix
bool visited[mx];/// visited or not ??
int disc[mx]={0};/// dfs time finding,dfs number of a node
int low[mx]={0};/// low dfs time for purpose to find a cycle
int parent[mx]={-1};/// -1 holds for Null
int odd_counts,even_counts;
set<int>components_nodes;

void bcc(int u)
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
            st.push(make_pair(u,v));
            bcc(v);
    ///this is for finding low dfs number of a node
        low[u]=min(low[u],low[v]);
    ///this is for finding the different subtree of root node,if each subtree of a root node is not connected by cross edge,then it is assumed as different subtree
    ///which implies that,if root node has been removed ,then those two subtrees will be detached from each other .
    ///articulation point so,now the time to print the edges
        if((parent[u]==-1 && child>1)||(parent[u]!=-1 && low[v]>=disc[u]))
        {
             while (st.top().first != u || st.top().second != v) {
                    components_nodes.insert(st.top().first);
                    components_nodes.insert(st.top().second);
                    st.pop();
                }
                components_nodes.insert(st.top().first);
                components_nodes.insert(st.top().second);
                st.pop();
                if((int)components_nodes.size()%2==1) odd_counts++;
                else even_counts++;
                components_nodes.clear();
        }

        }
/// this means that, visited[v] is true i.e. already v is visited
/// if u's parent is not v,then this is a back edge , u-v .so we will take low[] time from disc[] time of v
/// if (low[u]>disc[v]) ,then this edge has not been yet pushed
        else if( v!=parent[u] && (low[u]>disc[v]) )
        {
            low[u]=min(low[u],disc[v]);
            st.push(make_pair(u,v));
        }
    }

}


    int main()

    {
        int V,E,u,v;
        cin>>V>>E;
        while(E--)
        {
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
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

        bool Empty = false;
        // If stack is not empty, pop all edges from stack
        while (st.size() > 0)
        {
            Empty = true;
            components_nodes.insert(st.top().first);
            components_nodes.insert(st.top().second);
            st.pop();
        }

        if (Empty==true)
        {
            if((int)components_nodes.size()%2==1) odd_counts++;
            else even_counts++;
                components_nodes.clear();
        }

        }
         cout<<odd_counts<<" "<<even_counts<<endl;

        return 0;
    }
