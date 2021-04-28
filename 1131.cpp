#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <utility>
using namespace std;
#define ll long long
#define pii pair<ll,ll>
#define f first
#define s second
vector<vector<int>> V;
vector<vector<pii>> adjList;
const ll INF = ~(1<<31);
bool visit[3][10000]={0};
void dijkstra(){
    for(int k = 0 ; k < 3 ; k++){
        priority_queue<pii,vector<pii>,greater<pii>> Q;
        for(int i = 0 ; i < V[k].size() ; i++) Q.push({V[k][i],i});
        
        while(!Q.empty()){
            pii current = Q.top();
            Q.pop();
            if(visit[k][current.s]==1) continue; //current.s is index
            visit[k][current.s]=1;
            //relax
            for(int i = 0 ; i < adjList[current.s].size(); i++){
                ll v = adjList[current.s][i].f; //adjacent node
                ll w = adjList[current.s][i].s; //weight
                if(V[k][current.s]+w < V[k][v]){
                    V[k][v] = V[k][current.s] + w;
                    Q.push({V[k][v],v});
                }
            }
        }
    }
}

int main(){
    int n,m,u,v,w;
    cin >> n >> m >> u >> v >> w;
    V.resize(3,vector<int>(n,INF));
    adjList.resize(n);
    for(int i = 0 ; i < m ; i++){
        int a,b,w;
        cin >> a >> b >> w;
        adjList[a].push_back({b,w});
    }
    V[0][u] = 0;
    V[1][v] = 0;
    V[2][w] = 0;
    dijkstra();

    ll first = V[0][v] + V[1][w] + V[2][u];
    if(V[0][v]==INF||V[1][w]==INF||V[2][u]==INF) first = -1;
    ll second = V[0][w] + V[2][v] + V[1][u];
    if(V[0][w]==INF||V[2][v]==INF||V[1][u]==INF) second = -1;
    if(first==-1&&second==-1){
        printf("-1\n");
    }
    else{
        if(first==-1) printf("%lld\n",second);
        else if(second==-1) printf("%lld\n",first);
        else if(first<second) printf("%lld\n",first);
        else printf("%lld\n",second);
    }
}