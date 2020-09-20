
/// Codeforces : D. Beautiful Graph.
/// Category : bipartite Graph + counting.

#include<bits/stdc++.h>


using namespace std;

const int mx=300001;

typedef long long ll;

vector<int>adj[mx];
int color[mx];
bool flag;

ll tot;
ll even;
ll ans;

const ll mod=998244353;

inline void bipartite(int u,int odd_or_even)
{
    if(!flag) return;
    tot++;
    /// this means that this node must be colored with even 2
    if(odd_or_even) color[u]=2,even++;
    /// this means that this node must be colored with odd (1 or 3)
    else color[u]=1;

    int sz=adj[u].size();

    for(int i=0;i<sz;i++)
    {
        int v=adj[u][i];
        /// it is not possible to make this bi-coloring graph
        /// for every edge one side (1 or 3) another side (2)
        if(color[v]==color[u])
        {
            flag=false;
            return;
        }
        /// if visited no need to iterate
        if(color[v]) continue;
        else
        {
            /// flip odd_or_even for next time
                bipartite(v,odd_or_even^1);
        }
    }
}

inline ll po(ll a,ll b)
{
    ll ans=1ll;
    while(b)
    {
        if(b&1ll) ans=(ans*a)%mod;
        a=(a*a)%mod;
        b=b>>1ll;
    }
    return ans;
}


int main()

{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int tc;
    cin>>tc;

    while(tc--)
    {
        int n,m,u,v;
        cin>>n>>m;
        flag=true;
        ans=1ll;
        for(int i=1;i<=n;i++) color[i]=0,adj[i].clear();
        while(m--)
        {
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for(int i=1;i<=n;i++)
        {
            if(!color[i])
            {
                  tot=0ll,even=0ll;
                  bipartite(i,0);
                  ll odd=tot-even;
                  /// 1 or 3 can be on the odd position by 2^odd.
                  /// 1 or 3 can be on the even position by 2^even.
                  ans=ans*((po(2ll,odd)+po(2ll,even))%mod);
                  if(ans>=mod) ans=ans%mod;
            }
        }
        if(flag)
        cout<<ans<<"\n";
        else cout<<"0\n";
    }

    return 0;
}
