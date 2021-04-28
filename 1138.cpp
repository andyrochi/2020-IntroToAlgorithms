#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int INF = ~(1<<31);
int c[1005][1005]; //capacity
int f[1005][1005]; //flow
int sSize;
vector<int> path;

bool BFS(int s,int t){
    path.clear();
    queue<int> q;
    q.push(s);
    vector<int> parent(sSize,-1);
    parent[s] = -2;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(int i = 0 ; i < sSize ; i++){
            int cf = c[cur][i] - f[cur][i];
            if(cf>0&&parent[i]==-1){
                parent[i] = cur;
                if(i==t) break;
                q.push(i);
            }
        }
        if(parent[t]!=-1) break;
    }
    if(parent[t]==-1) return false;
    
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
        for(int i = 0 ; i < path.size()-1 ; i++){
            int u = path[i];
            int v = path[i+1];
            int cf = c[u][v] - f[u][v];
            if(cf<min) min = cf;
        }
        for(int i = 0 ; i < path.size()-1 ; i++){
            int u = path[i];
            int v = path[i+1];
            f[u][v] = f[u][v] + min;
            f[v][u] = -f[u][v];
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
    int i = 0;
    int total_income = 0;
    for(; i < n ; i++){
        int cost;
        cin >> cost;
        c[s][i] = cost;
    }
    for(int j = 0 ; j < m ; j++){
        int income;
        cin >> income;
        c[i++][t] = income;
        total_income += income;
    }
    for(int j = 0 ; j < k ; j++){
        int u,v;
        cin >> u >> v;
        c[u][n+v] = INF;
    }
    //finish graph

    maxFlow(s,t);
    int sumf = 0;
    for(int i = 0 ; i < sSize-2 ; i++ ){
        sumf+=f[s][i];
    }
    cout << total_income-sumf << '\n';
}