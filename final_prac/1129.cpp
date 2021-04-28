#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#define pii pair<int,int>
#define swap(x,y) {x=x+y;y=x-y;x=x-y;}
#define Tie std::cin.sync_with_stdio(0),cin.tie(0);
#define f first
#define s second
using namespace std;
const int MAXN = 5005;
int parent[MAXN] = {0};
int edges[MAXN][MAXN] = {0};
int setsize[MAXN] = {0};
int output[500005] = {0};
void make_set(){
    for(int i = 0 ; i < MAXN ; i++){
        parent[i] = i;
        setsize[i] = 1;
    }
}

//path compression
int find_set(int a){
    if(parent[a]==a) return a;
    return parent[a] = find_set(parent[a]);
}

void union_set(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if(a==b) return;
    if(setsize[a]<setsize[b]) swap(a,b);
    setsize[a] += setsize[b];
    parent[b] = parent[a];
}

int main(){Tie
    int n, m, q;
    cin >> n >> m >> q;
    for(int i = 0 ; i < m ; i++){
        int u,v;
        cin >> u >> v;
        edges[u][v]++;
        edges[v][u]++;
    }
    vector<pii> input;
    for(int i = 0 ; i < q ; i++){
        int u,v;
        cin >> u >> v;
        if(u==-1){
            input.push_back({u,v});
        }
        else{
            if(edges[u][v]>0){
                edges[u][v]--;
                edges[v][u]--;
                input.push_back({u,v});
            }
        }
    }
    make_set();
    for(int i = 0 ; i < n ; i++){
        for(int j = i + 1 ; j < n ; j++){
            if(edges[i][j]>0) union_set(i,j);
        }
    }
    
    vector<int> output;
    for(int i = input.size()-1 ; i >=0 ; i--){
        int u = input[i].f;
        int v = input[i].s;
        if(u!=-1){
            //edges[u][v]++;
            //edges[v][u]++;
            union_set(u,v);
        }
        else{
            output.push_back(setsize[find_set(v)]);
        }
    }
    
    for(int i = output.size()-1 ; i >= 0 ; i--){
        printf("%d\n", output[i]);
    }
    
}