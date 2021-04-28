#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
using namespace std;
#define w 1
#define g 2
#define b 3
long long t = 0;

class Vertex{
public:
    Vertex(){
        color=w;
        d=0;
        f=0;
        visit=0;
        parent=-1;
    }
    int color,visit;
    int parent;
    long long d,f;
};

class Graph{
public:
    Graph(int size){
        this->size = size;
        adjList.resize(size);
        adjListT.resize(size);
        V.resize(size);
    }
    vector<list<int> > adjList;
    vector<list<int> > adjListT;
    vector<Vertex> V;
    int size;
};
Graph * A;

void dfsvisit1(Graph& G, int i){
    t++;
    G.V[i].d = t;
    G.V[i].color = g;
    for(int v: G.adjList[i]){
        if(G.V[v].color ==w){
            //G.V[v].parent = i;
            dfsvisit1(G,v);
        }
    }
    G.V[i].color = b; //visit done
    t++;
    G.V[i].f = t;
}

void dfs1(Graph& G){
    for(int i = 0 ; i < G.size ; i++){
        if(G.V[i].color == w){
            dfsvisit1(G,i);
        }
    }
}

bool comp(int num1, int num2){
    return A->V[num1].f < A->V[num2].f;
}

int cnt = 0;

void dfsvisit2(Graph& G, int i){
    G.V[i].visit = 1;
    cnt++;
    for(int v: G.adjListT[i]){
        if(G.V[v].visit==0){
            dfsvisit2(G,v);
        }
    }
}

int dfs2(Graph& G){
    //sort
    vector<int> order(G.size);
    for(int i = 0 ; i < G.size ; i++) order[i]=i;
    sort(order.begin(),order.end(),comp);
    priority_queue<int> size;
    for(int i = order.size()-1 ; i >= 0 ; i--){
        //printf("debug V[%d]:%lld\n",order[i],G.V[order[i]].f);
        if(G.V[order[i]].visit == 0){
            //printf("debug, V[%d].f = %lld",i,G.V[i].f);
            cnt=0;
            dfsvisit2(G,order[i]);
            size.push(cnt);
        }
    }
    size.pop();
    if(size.empty()) return 0;
    return size.top();
}

int main(){
    int n,m;
    cin >> n >> m;
    Graph G(n);
    A = &G;
    for(int i = 0 ; i < m ; i++){
        int u,v;
        cin >> u >> v;
        G.adjList[u].push_back(v);
        G.adjListT[v].push_back(u);
    }
    dfs1(G);
    /*
    for(int i = 0 ; i < n ; i++){
        printf("%d: d=%d, f=%d\n", i, G.V[i].d,G.V[i].f);
    }
    */
    printf("%d\n", dfs2(G));
}