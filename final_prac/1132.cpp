#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define Tie std::cin.sync_with_stdio(0),std::cin.tie(0);
#define maxn 100005
#define w 0
#define g 1
#define b 2
int n,m;
struct Vertex{
    Vertex():s(0),f(0),visit(0),color(w){}
    int s,f;
    int visit;
    int color;
};
Vertex v[maxn];
vector<int> edges[maxn];
vector<int> edgesT[maxn];
vector<int> finishV;
priority_queue<int> qsize;
int t = 0;

void dfsvisit1(int i){
    t++;
    v[i].s=t;
    v[i].color=g;
    for(int j = 0 ; j < edges[i].size() ; j++){
        int neighbor = edges[i][j];
        if(v[neighbor].color==w)
            dfsvisit1(neighbor);
    }
    t++;
    v[i].f=t;
    finishV.push_back(i);
    v[i].color=b;
}
void dfs1(){
    for(int i = 0 ; i < n ; i++){
        if(v[i].color==w){
            dfsvisit1(i);
        }
    }
}
int cnt = 0;
void dfsvisit2(int vertex){
    cnt++;
    v[vertex].visit=1;
    for(int i = 0 ; i < edgesT[vertex].size(); i++){
        int neighbor = edgesT[vertex][i];
        if(v[neighbor].visit==0){
            dfsvisit2(neighbor);
        }
    }
}
void dfs2(){
    for(int i = finishV.size()-1; i>=0 ; i--){
        if(v[finishV[i]].visit==0){
            cnt=0;
            dfsvisit2(finishV[i]);
            qsize.push(cnt);
        }
    }
}
int main(){Tie
    cin >> n >> m;
    for(int i = 0 ; i < m ; i++){
        int u,v;
        cin >> u >> v;
        edges[u].push_back(v);
        edgesT[v].push_back(u);
    }
    dfs1();
    dfs2();
    qsize.pop();
    if(qsize.empty()) printf("0\n");
    else{
        printf("%d\n",qsize.top());
    }
}