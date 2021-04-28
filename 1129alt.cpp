#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
#define MAX 5000
int adj[MAX][MAX] = {0};
int visit[MAX] = {0};
int n,m,q;
int component[MAX] = {0};
int componentSize[MAX] = {0};
int c = 0;

void resetVisit(){
    for(int i = 0 ; i < n ; i++ ) visit[i] = 0;
}

int main(){
    cin >> n >> m >> q;
    for(int i = 0 ; i < m ; i++ ){
        int u,v;
        cin >> u >> v;
        adj[u][v]++;
        adj[v][u]++;
    }
    
    for(int i = 0 ; i < n ; i++){
        if(visit[i]==1){
            continue;
        }
        queue<int> q;
        q.push(i);
        visit[i] = 1;
        component[i] = c;
        int count = 1;
        while(!q.empty()){
            int cur = q.front();
            visit[cur] = 1;
            q.pop();
            for(int i = 0 ; i < n ; i++){
                if(adj[cur][i]>0 && visit[i]!=1){
                    q.push(i);
                    visit[i] = 1;
                    component[i] = c;
                    count++;
                }
            }
        }
        componentSize[c] = count;
        c++;
    }
    
    for(int k = 0 ; k < q ; k++){
        int i,j;
        cin >> i >> j;
        if(i<0){
            printf("%d\n", componentSize[component[j]]);
        }
        else{
            if(adj[i][j]==0){
                continue;
            }
            adj[i][j]--;
            adj[j][i]--;
            if(adj[i][j]>0||(i==j)){
                continue;
            }
            //only dfs on i
            resetVisit();
            queue<int> q;
            q.push(i);
            vector<int> visited;
            visit[i] = 1;
            visited.push_back(i);
            int count = 1;
            while(!q.empty()){
                int cur = q.front();
                visit[cur] = 1;
                q.pop();
                for(int i = 0 ; i < n ; i++){
                    if(adj[cur][i]>0 && visit[i]!=1){
                        q.push(i);
                        visit[i] = 1;
                        visited.push_back(i);
                        count++;
                    }
                }
            }
            if(count==componentSize[component[j]]) continue;
            componentSize[c] = count;
            componentSize[component[j]] -= count;
            for(int s = 0 ; s < visited.size() ; s++){
                component[visited[s]] = c;
            }
            c++;
        }
    }
    
}
