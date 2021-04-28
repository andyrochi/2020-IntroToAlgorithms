#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define pb push_back
using namespace std;
const int INF = ~(1<<31);
struct edge{
    int to,cap,flow,rev;
};
vector<edge> V[1005];
int sSize;
vector<int> path;

bool BFS(int s,int t){
    //printf("BFS!\n");
    path.clear();
    queue<int> q;
    q.push(s);
    vector<int> parent(sSize,-1);
    parent[s] = -2;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(int i = 0 ; i < V[cur].size(); i++){
            int next = V[cur][i].to;
            //i-th edge
            int cf = V[cur][i].cap - V[cur][i].flow;
            //printf("[%d][%d] cf is: %d\n",cur,next,cf);
            if(cf>0&&parent[next]==-1){
                parent[next] = cur;
                if(next==t) break;
                q.push(next);
            }
        }
        if(parent[t]!=-1) break;
    }
    //printf("hiparent\n");
    if(parent[t]==-1) return false;
    //printf("hi\n");
    //get path
    int cur = t;
    while(true){
        path.push_back(cur);
        if(cur==s) break;
        cur = parent[cur]; 
    }
    reverse(path.begin(),path.end());
    return true;
}

void maxFlow(int s, int t){
    while(BFS(s,t)){
        int min=INF;
        vector<int> nextIndex;
        for(int i = 0 ; i < path.size()-1 ; i++){
            int u = path[i];
            int v = path[i+1];
            //find v's index
            int next;
            for(int i = 0 ; i < V[u].size() ; i++){
                if(V[u][i].to==v){
                    next = i; break;
                }
            }
            nextIndex.push_back(next);
            int cf = V[u][next].cap - V[u][next].flow;
            if(cf<min) min = cf;
        }
        for(int i = 0 ; i < path.size()-1 ; i++){
            int u = path[i];
            int v = path[i+1];
            int next = nextIndex[i];
            V[u][next].flow += min;
            V[v][V[u][next].rev].flow = -V[u][next].flow;
        }
    }
}

int main(){
    int n,m,k;
    cin >> n >> m >> k;
    //create graph
    sSize = n+m+2;
    int s = n+m;
    int t = n+m+1;
    int total_income = 0;
    for(int i = 0 ; i < n ; i++){
        int cost;
        cin >> cost;
        V[s].pb({i,cost,0,(int) V[i].size()});
        V[i].pb({s,0,0,(int) V[s].size()-1});
    }
    for(int j = 0 ; j < m ; j++){
        int income;
        cin >> income;
        V[n+j].pb({t,income,0,(int) V[t].size()});
        V[t].pb({n+j,0,0,(int) V[n+j].size()-1});
        total_income += income;
    }
    for(int j = 0 ; j < k ; j++){
        int u,v;
        cin >> u >> v;
        V[u].pb({n+v,INF,0,(int) V[n+v].size()});
        V[n+v].pb({u,0,0,(int) V[u].size()-1});
    }
    //finish graph

    maxFlow(s,t);
    int sumf = 0;
    for(int i = 0 ; i < V[s].size() ; i++ ){
        sumf+=V[s][i].flow;
    }

    cout << total_income-sumf << '\n';
}