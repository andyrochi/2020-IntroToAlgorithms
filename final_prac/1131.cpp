#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#define Tie std::cin.sync_with_stdio(0),cin.tie(0);
#define pll pair<ll,ll>
#define ll long long
#define f first
#define s second
using namespace std;
const ll INF = ~(1<<31);
const int MAXN = 10005;
vector<vector<ll>> V(3,vector<ll>(MAXN,INF));
vector<pll>edges[MAXN];
int start[3];
int n,m;

void dijkstra(){
    //initialize
    for(int i = 0 ; i < 3 ; i++){
        vector<int> popped(n,0);
        priority_queue<pll,vector<pll>,greater<pll>> q;
        V[i][start[i]] = 0;
        for(int j = 0 ; j < n ; j++){
            q.push({V[i][j],j});
        }
        //relax
        while(!q.empty()){
            pll top = q.top();
            q.pop();
            int index = top.s;
            if(popped[index]==1) continue;
            popped[index]=1;
            for(int j = 0 ; j < edges[index].size() ; j++){
                int v = edges[index][j].f;
                int w = edges[index][j].s;
                //relax
                if(V[i][index]+w < V[i][v]){
                    V[i][v]=V[i][index] + w;
                    q.push({V[i][v],v});
                }
            }
        }
    }
}
int main(){Tie
    cin >> n >> m >> start[0] >> start[1] >> start[2];
    for(int i = 0 ; i < m ;i++){
        int u,v,w;
        cin >> u >> v >> w;
        edges[u].push_back({v,w});
    }
    dijkstra();
    //0 1 2
    ll first = V[0][start[1]]+V[1][start[2]] + V[2][start[0]];
    ll second = V[0][start[2]] + V[2][start[1]] + V[1][start[0]];
    bool firstNotExist = V[0][start[1]]==INF||V[1][start[2]]==INF||V[2][start[0]]==INF;
    bool secondNotExist = V[0][start[2]]==INF||V[2][start[1]]==INF||V[1][start[0]]==INF;
    if(firstNotExist&&secondNotExist){
        printf("-1\n");
    }
    else{
        if(firstNotExist) printf("%lld\n",second);
        else if(secondNotExist) printf("%lld\n",first);
        else{
            printf("%lld\n", (first<second?first:second));
        }
    }
}