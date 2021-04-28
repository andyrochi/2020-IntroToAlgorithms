#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define pb push_back
using namespace std;
struct edge{
    int to,cap,flow,rev;
};
vector<edge> V[2005];
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
int total = 0;
void maxFlow(int s, int t){
    while(BFS(s,t)){
        total++;
        int min=100;
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
            V[u][next].flow += 1;
            V[v][V[u][next].rev].flow = -V[u][next].flow;
        }
        break;
    }
}

int main(){
    int n,m,k;
    scanf("%d%d%d", &n, &m, &k);
    //create graph
    sSize = n+m+2;
    int s = n+m;
    int t = n+m+1;
    
    for(int i = 0; i < n ; i++){
        V[s].pb({i,1,0,(int) V[i].size()});
        V[i].pb({s,0,0,(int) V[s].size()-1});
    }
    for(int i = 0; i < m ; i++){
        V[n+i].pb({t,1,0,(int) V[t].size()});
        V[t].pb({n+i,0,0,(int) V[n+i].size()-1});
    }
    
    for(int i = 0 ; i < k ;i++){
        int u,v;
        scanf("%d%d", &u, &v);
        v+=n;
        V[u].pb({v,1,0,(int) V[v].size()});
        V[v].pb({u,0,0,(int) V[u].size()-1});
        maxFlow(s,t);
        printf("%d\n",total);
    }
}