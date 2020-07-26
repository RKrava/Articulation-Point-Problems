
const int mx=1e5;

vector<int>adj[mx];/// adjacency matrix 
bool visited[mx]={false};/// visited or not ??
int disc[mx]={0};/// dfs time finding,dfs number of a node 
int low[mx]={0};/// low dfs time for purpose to find a cycle 
int parent[mx]={-1};/// -1 holds for Null
bool apu[mx]={false};/// is the node articular point ?
vector< pair<int,int> >bridges; /// push back the bridges into a vector
int articupoints=0;/// the number of articulation points 

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
    ///this is for finding the different subtree of root node,if each subtree of a root node is not connected by cross edge,then it is assumed as different subtree
    ///which implies that,if root node has been removed ,then those two subtrees will be detached from each other . 
        if(parent[u]==-1 && child>1)
        {
            articupoints++;
            apu[u]=true;///finding root with different independent subtree
        }
    ///u->v,usually low discovery time of v should be greater or equal than u 
    ///that means ,there is no way to reach v without covereing u.
        if(parent[u]!=-1 && low[v]>=disc[u])
        {
            articupoints++;
            apu[u]=true;
        }
  /// when low[v]>disc[u] , this u-v is the critical edges 
        if(low[v]>disc[u])
        {
            bridges.push_back(make_pair(min(v,u),max(v,u)));// storing bridges pair
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

