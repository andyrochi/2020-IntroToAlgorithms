#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define pii pair<int,int>
#define f first
#define s second
using namespace std;
const int MAXN = 1005;
int parent[MAXN];
int setsize[MAXN];
void make_set(){
    for(int i = 0 ; i < MAXN ; i++){
        parent[i] = i;
        setsize[i] = 1;
    }
}

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

int main(){
    int n,m;
    cin >> n >> m;
    vector<pair<int,pii>> edges(m);
    for(int i = 0 ; i < m ; i++){
        int u,v,w;
        cin >> u >> v >> w;
        edges[i]={w,{u,v}};
    }
    sort(edges.begin(),edges.end());
    make_set();
    int minCost = 0;
    int edgeCount = 0;
    for(int i = 0 ; i < m ; i++){
        int w = edges[i].f;
        int u = edges[i].s.f;
        int v = edges[i].s.s;
        if(find_set(u)!=find_set(v)){
            union_set(u,v);
            edgeCount++;
            minCost += w;
            if(edgeCount==n-1) break;   
        }
    }
    printf("%d\n", minCost);
    
}